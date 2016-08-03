
#include "alMANUALK/alMANUALK_Def.h"

#ifdef WIN32 // Only do AutoCalibration in PC mode

#ifdef __cplusplus
extern "C"
{
#endif

/**
Input:	
view        char   Camera Index
SPPvsBVPParam  CAMK_SPPvsBVPPParam*  Scalar Factors 

*src_buf	unsigned char*	src_width * src_height* 2	I Image buffer point to Front/Rear/Left/Right image
			Image Format= YUYV422 
			src_width= 720(default)
			src_height= 480(default)

buf_type   char		Buffer type:  0=left, 1=right 2=front, 3=rear,
buf_width  int      display width
buf_height int      display height

Input_X    input reference point x
Input_Y	   input reference point x			

Output:			
Output_X, Output_Y
**/
    BOOL AutoCalibration(UINT8 ucCameraIndx, alMANUALK_SPPvsBVPPCfg * SPPvsBVPParam, unsigned char *src_buf, int buf_width, int buf_height, int Input_X, int Input_Y, int* Output_X, int* Output_Y);

    BOOL AutoCalibration_Ancre(UINT8 ucCameraIndx, INT32 a_lPointIndex, alMANUALK_SPPvsBVPPCfg * SPPvsBVPParam, unsigned char *src_buf, int buf_width, int buf_height, int Input_X, int Input_Y, int* Output_X, int* Output_Y);


#ifdef __cplusplus
}
#endif

#endif // Only do AutoCalibration in PC mode