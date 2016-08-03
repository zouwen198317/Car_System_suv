
#ifdef WIN32 // Only do AutoCalibration in PC mode

#include <stdio.h>
#include <stdlib.h>
#include "mtype.h"
#include "Core/PointsSearching.h"

/* ----------------ROI-----------------------

   (Start_X,Start_Y)
	       .__________________
		   |                  | ┐
		   |                  |	
		   |                  |	
		   |        .         |	
		   |(Input_X,Input_Y) |	ROI_height   *Scaling
		   |                  |	
		   |                  |	
           |__________________|	┘
            
			└  ROI_width   ┘        *Scaling
                                                            */
int Start_X,Start_Y;
#define ROI_width  50
#define ROI_height 30 // 30
FLOAT32 Scaling ;
//#define Scaling    1.2
/*----------------------Serching Size-----------------------------
PattenDis: The size of cross which attempted to mark.
{Size_1,Size_2,...,Size_NumOfSeachingSize}
={FirstSize + 1*IntervalOfSerarchingSize, 
  FirstSize + 2*IntervalOfSerarchingSize,
  ...
  FirstSize + NumOfSeachingSize * IntervalOfSerarchingSize}


      
      o: internal
	  x: outer
					  _________
					 |         |
			    x	 |    o    |    x
					 |         |
					 |         |
		    _________|         |_________
           |                             |
           |    o         o<------->o    |
           |               PattenDis     |
           |_________           _________|
                     |         |
                     |         |
                x    |    o    |    x
					 |         |
                     |_________|
																

																*/
#define NumOfSeachingSize 5
#define FirstSize 5
#define IntervalOfSerarchingSize 3
#define NumOfInter 5
#define NumOfOuter 4

//Variance of Internal gray level <500 (?)
//Variance of Outer gray level <500 (?)
//Difference of Outer and Internal gray level> 30 (?)
#define VarinaceOfInter_LowerBound_ 600// 500
#define VarinaceOfOuter_LowerBound_ 450 // 500
#define DifferenceOfMean_LowerBound_ 30 // 30

/*                 Further Searching 
    o:十字內點
					  _________
					 |         |
			    	 |    o    |    
					 |    o    |
					 |    o    |
		    _________|    o    |_________
           |              o              |
           |    ooooooooooooooooooooo    |
           |              o              |
           |_________     o     _________|
                     |    o    |
                     |    o    |
                     |    o    |    
					 |         |
                     |_________|
																
Calculate Varinace of (o)
																*/
#define VarianceOfFurtherSearchingPoints 300
//最低可行點數量,ex 低於兩個合理點 即宣告PointsGrouping fail
#define NumOfCandiate_LowerBound 2 

#define GrayInput 1




static double GetAverage(int* Nums,int Count);
static double GetVariance_(double* Nums,int Count);
static double GetVariance(int* Nums,int Count);
static int    GetMedian(int n, int* x);
static int    PointsGrouping(char* box,int buf_width, int buf_height,int* median_X,int* median_Y);
static void   MaskEvaluate(int x,int y,int d,unsigned char* src_buf,int buf_width, int buf_height,double* MeanIn,double* MeanOut,double* VarIn,double* VarOut);

static void   MaskEvaluateGray(int x, int y, int d, unsigned char* src_buf, int buf_width, int buf_height, double* MeanIn, double* MeanOut, double* VarIn, double* VarOut, double* a_peVar);



BOOL AutoCalibration_Ancre(UINT8 ucCameraIndx, INT32 a_lPointIndex, alMANUALK_SPPvsBVPPCfg * SPPvsBVPParam, unsigned char *src_buf, int buf_width, int buf_height, int Input_X, int Input_Y, int* Output_X, int* Output_Y)
{
	char* box = NULL;
	int PattenDis[NumOfSeachingSize];

	//--------------Tempt Var--------------------
	int d, x = 0, y = 0, i, tco, lVerticalCnt = 0;
	double VarOut, VarIn, AveIn, AveOut, eVar = 0;
	double* coll = NULL;
	double eVerticalMean = 0;
	BOOL bResult;

	box = (char*)malloc(buf_width*buf_height);
	memset(box, 0x0, buf_width*buf_height);

	//--------------Scaling Factor---------------
	Scaling = SPPvsBVPParam[ucCameraIndx].fScaleFactor;
	coll = (double*)malloc((int)(ROI_width*Scaling*ROI_height*Scaling));

	//--------------Initial size----------------- 
	for (i = 0; i<NumOfSeachingSize; i++)
		PattenDis[i] = FirstSize + i*IntervalOfSerarchingSize;

	//------Searching ROI & boundary limitation--
	Start_X = min(buf_width - (int)(ROI_width*Scaling), max((Input_X - (int)(ROI_width*Scaling*0.5)), 0));
	Start_Y = min(buf_height - (int)(ROI_height*Scaling), max((Input_Y - (int)(ROI_height*Scaling*0.5)), 0));

#if 1
	if (ucCameraIndx == 0 && a_lPointIndex == 2)
	{
		x = x;
	}

	if (ucCameraIndx == 1 && a_lPointIndex == 2)
	{
		x = x;
	}
#endif

	for (y = max(Start_Y, 0); y< min(Start_Y + ROI_height*Scaling, buf_height); y++)
	{
		for (x = max(Start_X, 0); x< min(Start_X + ROI_width*Scaling, buf_width); x++)
		{
			for (d = 0; d<NumOfSeachingSize; d++)
			{
#if 1
				if (x == 513 && y == 328)
				{
					x = x;
				}
#endif
				//--------------Mask mathing--------------------
#if GrayInput == 0
				MaskEvaluate(x, y, PattenDis[d], src_buf, buf_width, buf_height, &AveIn, &AveOut, &VarIn, &VarOut);
#else
				MaskEvaluateGray(x, y, PattenDis[d], src_buf, buf_width, buf_height, &AveIn, &AveOut, &VarIn, &VarOut, &eVar);
#endif

				// if (VarIn<VarinaceOfInter_LowerBound_&&VarOut<VarinaceOfOuter_LowerBound_ && (AveOut - AveIn)>DifferenceOfMean_LowerBound_ && eVar > VarinaceOfOuter_LowerBound_)//&&InNum>=4)
				
				// if ((AveOut - AveIn)> 80 && ((AveOut > 170 && VarOut<800)) && eVar > VarinaceOfOuter_LowerBound_)//&&InNum>=4)
				if ((AveOut - AveIn)> 80 && ((AveOut > 170 && VarOut<800) || (AveOut > 130 && (VarOut<320 || AveIn < 35))) && eVar > VarinaceOfOuter_LowerBound_ && VarIn < 2000)//&&InNum>=4)
				{
					//------------------Further search----------------------
					tco = 0;
#if GrayInput == 0
					for (i = max(x - PattenDis[d], 0); i<min(x + PattenDis[d], buf_width); i++)
					{
						coll[tco] = (int)src_buf[i * 2 + y*buf_width * 2];
						tco++;
					}
					for (i = max(y - PattenDis[d], 0); i<min(y + PattenDis[d], buf_height); i++)
					{
						coll[tco] = (int)src_buf[x * 2 + i*buf_width * 2];
						tco++;
					}
#else
					for (i = max(x - PattenDis[d], 0); i<min(x + PattenDis[d], buf_width); i++)
					{
						coll[tco] = (int)src_buf[i + y*buf_width];
						tco++;
					}

					lVerticalCnt = 0;
					eVerticalMean = 0;
					if (ucCameraIndx > 1)
					{
						for (i = max(y - PattenDis[d], 0); i < min(y + PattenDis[d], buf_height); i++)
						{
							coll[tco] = (int)src_buf[x + i*buf_width];
							tco++;
						}
					}
					else if (ucCameraIndx == 0 && a_lPointIndex == 2)
					{
						for (i = max(y - PattenDis[d], 0); i < min(y + PattenDis[d], buf_height); i++)
						{
							coll[tco] = (int)src_buf[x + i*buf_width];
							tco++;
						}
					}
					else if (ucCameraIndx == 1 && a_lPointIndex == 0)
					{
						for (i = max(y - PattenDis[d], 0); i < min(y + PattenDis[d], buf_height); i++)
						{
							coll[tco] = (int)src_buf[x + i*buf_width];
							tco++;
						}
					}
					else
					{
						for (i = max(y - PattenDis[d], 0); i < min(y + PattenDis[d], buf_height); i++)
						{
							eVerticalMean += (int)src_buf[x + i*buf_width];
							lVerticalCnt++;
						}
						eVerticalMean /= lVerticalCnt;
					}
#endif
					// if (GetVariance_(coll, tco) < VarianceOfFurtherSearchingPoints)
					if (GetVariance_(coll, tco) < 800 && (eVerticalMean - AveIn < 10))
					{
						box[x + y*buf_width] = TRUE;

						if (y < 219)
						{
							y = y;
						}
					}

				}
			}
		}
	}
	if (PointsGrouping(box, buf_width, buf_height, Output_X, Output_Y) == TRUE)
	{
		bResult = TRUE;
	}
	else
	{
		*Output_X = Input_X;
		*Output_Y = Input_Y;
		bResult = FALSE;
	}

	if (box)
	{
		free(box);
	}

	free(coll);
	return bResult;
}


BOOL AutoCalibration(UINT8 ucCameraIndx, alMANUALK_SPPvsBVPPCfg * SPPvsBVPParam, unsigned char *src_buf, int buf_width, int buf_height, int Input_X, int Input_Y, int* Output_X, int* Output_Y)
 {
	char* box = (char*)malloc(buf_width*buf_height);
    int PattenDis[NumOfSeachingSize];

    //--------------Tempt Var--------------------
    int d,x,y,i,tco;
    double VarOut,VarIn,AveIn,AveOut;
	double* coll ;
	BOOL bResult;
	memset(box,0x0,buf_width*buf_height);

	//--------------Scaling Factor---------------
	Scaling = SPPvsBVPParam[ucCameraIndx].fScaleFactor;
	coll = (double*)malloc(   (int)(ROI_width*Scaling*ROI_height*Scaling)    );

	//--------------Initial size----------------- 
	for(i = 0;i<NumOfSeachingSize;i++)
		PattenDis[i] = FirstSize + i*IntervalOfSerarchingSize;

	//------Searching ROI & boundary limitation--
	Start_X = min(buf_width  - (int)(ROI_width*Scaling) , max((Input_X - (int)(ROI_width*Scaling*0.5)),0));
    Start_Y = min(buf_height - (int)(ROI_height*Scaling), max((Input_Y - (int)(ROI_height*Scaling*0.5)),0));
    
	
    for( y = max(Start_Y,0); y< min(Start_Y+ROI_height*Scaling,buf_height) ;y++)
    {
        for( x = max(Start_X,0); x< min(Start_X+ROI_width*Scaling,buf_width) ;x++)
        {
#if 1

#endif
            for( d=0 ; d<NumOfSeachingSize ; d++)
            {
				//--------------Mask mathing--------------------
				MaskEvaluate(x,y,PattenDis[d],src_buf,buf_width,buf_height,&AveIn,&AveOut,&VarIn,&VarOut);


                if(VarIn<VarinaceOfInter_LowerBound_&&VarOut<VarinaceOfOuter_LowerBound_&&(AveOut-AveIn)>DifferenceOfMean_LowerBound_)//&&InNum>=4)
                {
                    //------------------Further search----------------------
                    tco=0;

                    for(i = max(x-PattenDis[d],0);i<min(x+PattenDis[d],buf_width);i++)
                    {
                        coll[tco] = (int)src_buf[i*2+y*buf_width*2];
                        tco++;
                    }
                    for(i = max(y-PattenDis[d],0);i<min(y+PattenDis[d],buf_height);i++)
                    {
                        coll[tco] = (int)src_buf[x*2+i*buf_width*2];
						tco++;
                    }	

                    if(GetVariance_(coll,tco)<VarianceOfFurtherSearchingPoints)		 	
                        box[x+ y*buf_width] = TRUE;
                    
                }
            }
        }
    }
    if(PointsGrouping(box, buf_width, buf_height, Output_X,Output_Y)==TRUE)
    {
        bResult = TRUE;
    }
    else
    {
        *Output_X = Input_X;
        *Output_Y = Input_Y;
        bResult = FALSE;
    }
    if(box)
        free(box);

	free(coll);
    return bResult;
}

//input box ::符合in5out4規則保留下來的點
static void   MaskEvaluate(int x,int y,int d,unsigned char* src_buf,int buf_width, int buf_height,double* MeanIn,double* MeanOut,double* VarIn,double* VarOut)
{
		int i,j,InNum=0, OutNum=0, AveIn[NumOfInter], AveOut[NumOfOuter];
		//Inter 5
		for(i = y-d;i<=y+d;i=i+d)
		{
		 if(i>=0&&i<buf_height&&x>=0&&x<buf_width)
		 {
		  AveIn[InNum]=  (int)src_buf[x*2+i*buf_width*2];
		  InNum++;
		 }
		}
		if((x-d)>=0&&(x-d)<buf_width)
		{
			AveIn[InNum]=  (int)src_buf[(x-d)*2+y*buf_width*2];//左內
			InNum++;
		}
		if((x+d)>=0&&(x+d)<buf_width)
		{
			AveIn[InNum]=  (int)src_buf[(x+d)*2+y*buf_width*2];//右內
			InNum++;
		}

		//Outer 4
		for( i = x-d;i<=x+d;i+=d*2)
		{
		 for(j = y-d;j<=y+d;j+=d*2)
		 {
		  if(i>=0&&i<buf_width&&j>=0&&j<buf_height)
		  { 
		   AveOut[OutNum]=  (int)src_buf[i*2+j*buf_width*2];
		   OutNum++;
		  }
		 }
		}
		//-------算平均值&變異數--------
		if(InNum!=FALSE&&OutNum!=FALSE)
		{
			*MeanIn  = GetAverage(AveIn,InNum);
			*MeanOut = GetAverage(AveOut,OutNum);
			*VarIn   = GetVariance(AveIn,InNum);
			*VarOut  = GetVariance(AveOut,OutNum);
		}
}

//input box ::符合in5out4規則保留下來的點
static void   MaskEvaluateGray(int x, int y, int d, unsigned char* src_buf, int buf_width, int buf_height, double* MeanIn, double* MeanOut, double* VarIn, double* VarOut, double* a_peVar)
{
	int i, j, InNum = 0, OutNum = 0, AveIn[NumOfInter], AveOut[NumOfOuter], Ave[1300] = { 0 }, lNum = 0;
	//Inter 5
	for (i = y - d; i <= y + d; i = i + d)
	{
		if (i >= 0 && i<buf_height&&x >= 0 && x<buf_width)
		{
			AveIn[InNum] = (int)src_buf[x + i*buf_width];
			InNum++;
		}
	}

	if ((x - d) >= 0 && (x - d)<buf_width)
	{
		AveIn[InNum] = (int)src_buf[(x - d) + y*buf_width];//左內
		InNum++;
	}
	if ((x + d) >= 0 && (x + d)<buf_width)
	{
		AveIn[InNum] = (int)src_buf[(x + d) + y*buf_width];//右內
		InNum++;
	}

	//Outer 4
	for (i = x - d; i <= x + d; i += d * 2)
	{
		for (j = y - d; j <= y + d; j += d * 2)
		{
			if (i >= 0 && i<buf_width&&j >= 0 && j<buf_height)
			{
				AveOut[OutNum] = (int)src_buf[i + j*buf_width];

				OutNum++;
			}
		}
	}

	for (i = x - d; i <= x + d; i++)
	{
		for (j = y - d; j <= y + d; j++)
		{
			if (i >= 0 && i<buf_width&&j >= 0 && j<buf_height)
			{
				Ave[lNum] = (int)src_buf[i + j*buf_width];
				lNum++;
			}
		}
	}

	if (lNum)
	{
		*a_peVar = GetAverage(Ave, lNum);
		*a_peVar = GetVariance(Ave, lNum);
	}

	//-------算平均值&變異數--------
	if (InNum != FALSE&&OutNum != FALSE)
	{
		*MeanIn = GetAverage(AveIn, InNum);
		*MeanOut = GetAverage(AveOut, OutNum);
		*VarIn = GetVariance(AveIn, InNum);
		*VarOut = GetVariance(AveOut, OutNum);
	}
}

static int PointsGrouping(char* box,int buf_width, int buf_height,int* median_X,int* median_Y)
{
	int RedNum = 0;
    int Xmean,Ymean,x,y;
    int* NumsX = (int*)malloc((int)(ROI_width*Scaling*ROI_height*Scaling));
    int* NumsY = (int*)malloc((int)(ROI_width*Scaling*ROI_height*Scaling));
    //掃ROI pixels
    for( y = Start_Y; y< Start_Y+ROI_height*Scaling ;y++)
    {
        for( x = Start_X; x< Start_X+ROI_width*Scaling ;x++)
        {
            if(x>=0 && x<buf_width && y>=0 && y<buf_height && box[x+y*buf_width]==TRUE)
            {
                NumsX[RedNum] = x;
                NumsY[RedNum] = y;
                RedNum++;
            }
        }
    }
     Xmean = GetMedian(RedNum,NumsX);
     Ymean = GetMedian(RedNum,NumsY);
    if(RedNum >= NumOfCandiate_LowerBound)
    {
       *median_X = Xmean;
       *median_Y = Ymean;
	   free(NumsX);
	   free(NumsY);
        return TRUE;
	}
	else
	{
		free(NumsX);
		free(NumsY);
	    return FALSE;
	}
    free(NumsX); 
    free(NumsY);
}

static double GetAverage(int* Nums,int Count)
{
	double sum = 0;
	int i;

	for( i = 0 ;i < Count;i++)
	{
	sum+=Nums[i];
	}

    return sum/(double)Count;
}

static double GetVariance_(double* Nums,int Count)
{
	double sum,mean;
	int i;
	sum = 0;
	for(i = 0 ;i < Count;i++)
	{
	    sum= sum+ Nums[i];
	}
	mean = sum/(double)Count;
	sum=0;
	for(i = 0 ;i < Count;i++)
	{
	    sum += (Nums[i]-mean)*(Nums[i]-mean);
	}

    return sum/(double)Count;
}
static double GetVariance(int* Nums,int Count)
{
	double sum ,mean;
	int i;

	sum = 0;
	for(i = 0 ;i < Count;i++)
	{
	    sum+=Nums[i];
	}
	
	mean = sum/(double)Count;
	sum = 0;
	for(i = 0 ;i < Count;i++)
	{
	    sum += (Nums[i]-mean)*(Nums[i]-mean);
	}

    return sum/(double)Count;
}


static int GetMedian(int n, int* x)
 {
    int temp;
    int i, j;
    // the following two loops sort the array x in ascending order
    for(i=0; i<n-1; i++) {
        for(j=i+1; j<n; j++) {
            if(x[j] < x[i]) {
                // swap elements
                temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }
    }
 
    if(n%2==0) 
	{
        // if there is an even number of elements, return mean of the two elements in the middle
        return(x[n/2 - 1]);
    } else {
        // else return the element in the middle
        return x[n/2];
    }
}

#endif // Only do AutoCalibration in PC mode

