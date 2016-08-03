
#include "alMatrix.h"
#include "basedef.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

/** \cond DOXYGEN_EXCLUDE */


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alMATRIX_Unit(FLOAT64 * a_peMatrix, INT32 a_lN)
{
    INT32 i;
    memset(a_peMatrix, 0, a_lN * a_lN * sizeof(FLOAT64));
    for (i = 0; i < a_lN; i++)
    {
        a_peMatrix[i * (a_lN + 1)] = 1.0;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alMATRIX_Add(FLOAT64 * a_peMatrix1, FLOAT64 * a_peMatrix2, INT32 a_lM, INT32 a_lN, FLOAT64 * a_peMatrix3)
{
    INT32 i, lElementCnt;
    lElementCnt = a_lM * a_lN;

    for (i = 0; i<lElementCnt; i++)
    {
        a_peMatrix3[i] = a_peMatrix1[i] + a_peMatrix2[i];
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alMATRIX_Minus(FLOAT64 * a_peMatrix1, FLOAT64 * a_peMatrix2, INT32 a_lM, INT32 a_lN, FLOAT64 * a_peMatrix3)
{
    INT32 i, lElementCnt;
    lElementCnt = a_lM * a_lN;

    for (i = 0; i<lElementCnt; i++)
    {
        a_peMatrix3[i] = a_peMatrix1[i] - a_peMatrix2[i];
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
INT32 alMATRIX_InverseNbyN(FLOAT64 * a_peMatrix, INT32 n)
{
    INT32 *is,*js,i,j,k,l,u,v;
    FLOAT64 d,p;
    
    is = malloc(sizeof(INT32) * n); //is=new INT32 [n];
    js = malloc(sizeof(INT32) * n); //js=new INT32 [n];
    for (k=0; k<=n-1; k++)
      { d=0.0;
        for (i=k; i<=n-1; i++)
        for (j=k; j<=n-1; j++)
          { l=i*n+j; p=fabs(a_peMatrix[l]);
            if (p>d) { d=p; is[k]=i; js[k]=j;}
          }
        if (d+1.0==1.0)
          { 
            free(is); free(js);
            return(0);
          }
        if (is[k]!=k)
          for (j=0; j<=n-1; j++)
            { u=k*n+j; v=is[k]*n+j;
              p=a_peMatrix[u]; a_peMatrix[u]=a_peMatrix[v]; a_peMatrix[v]=p;
            }
        if (js[k]!=k)
          for (i=0; i<=n-1; i++)
            { u=i*n+k; v=i*n+js[k];
              p=a_peMatrix[u]; a_peMatrix[u]=a_peMatrix[v]; a_peMatrix[v]=p;
            }
        l=k*n+k;
        a_peMatrix[l]=1.0f/a_peMatrix[l];
        for (j=0; j<=n-1; j++)
          if (j!=k)
            { u=k*n+j; a_peMatrix[u]=a_peMatrix[u]*a_peMatrix[l];}
        for (i=0; i<=n-1; i++)
          if (i!=k)
            for (j=0; j<=n-1; j++)
              if (j!=k)
                { u=i*n+j;
                  a_peMatrix[u]=a_peMatrix[u]-a_peMatrix[i*n+k]*a_peMatrix[k*n+j];
                }
        for (i=0; i<=n-1; i++)
          if (i!=k)
            { u=i*n+k; a_peMatrix[u]=-a_peMatrix[u]*a_peMatrix[l];}
      }
    for (k=n-1; k>=0; k--)
      { if (js[k]!=k)
          for (j=0; j<=n-1; j++)
            { u=k*n+j; v=js[k]*n+j;
              p=a_peMatrix[u]; a_peMatrix[u]=a_peMatrix[v]; a_peMatrix[v]=p;
            }
        if (is[k]!=k)
          for (i=0; i<=n-1; i++)
            { u=i*n+k; v=i*n+is[k];
              p=a_peMatrix[u]; a_peMatrix[u]=a_peMatrix[v]; a_peMatrix[v]=p;
            }
      }
    
    free(is); free(js);
    //delete [] is;
    //delete [] js;
    return (1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
INT32 alMATRIX_Inverse2(FLOAT64 * a_peMatrix, INT32 a_lN, INT32 * a_plTemp1, INT32 * a_plTemp2)
{
    INT32 i, j, k, l, u, v;
    FLOAT64 d, p;

    for (k = 0; k <= a_lN - 1; k++)
    {
        d = 0.0;
        for (i = k; i <= a_lN - 1; i++)
            for (j = k; j <= a_lN - 1; j++)
            {
                l = i*a_lN + j; p = fabs(a_peMatrix[l]);
                if (p>d) { d = p; a_plTemp1[k] = i; a_plTemp2[k] = j; }
            }
        if (d + 1.0 == 1.0)
        {
            return(0);
        }
        if (a_plTemp1[k] != k)
            for (j = 0; j <= a_lN - 1; j++)
            {
                u = k*a_lN + j; v = a_plTemp1[k] * a_lN + j;
                p = a_peMatrix[u]; a_peMatrix[u] = a_peMatrix[v]; a_peMatrix[v] = p;
            }
        if (a_plTemp2[k] != k)
            for (i = 0; i <= a_lN - 1; i++)
            {
                u = i*a_lN + k; v = i*a_lN + a_plTemp2[k];
                p = a_peMatrix[u]; a_peMatrix[u] = a_peMatrix[v]; a_peMatrix[v] = p;
            }
        l = k*a_lN + k;
        a_peMatrix[l] = 1.0f / a_peMatrix[l];
        for (j = 0; j <= a_lN - 1; j++)
            if (j != k)
            {
                u = k*a_lN + j; a_peMatrix[u] = a_peMatrix[u] * a_peMatrix[l];
            }
        for (i = 0; i <= a_lN - 1; i++)
            if (i != k)
                for (j = 0; j <= a_lN - 1; j++)
                    if (j != k)
                    {
                        u = i*a_lN + j;
                        a_peMatrix[u] = a_peMatrix[u] - a_peMatrix[i*a_lN + k] * a_peMatrix[k*a_lN + j];
                    }
        for (i = 0; i <= a_lN - 1; i++)
            if (i != k)
            {
                u = i*a_lN + k; a_peMatrix[u] = -a_peMatrix[u] * a_peMatrix[l];
            }
    }
    for (k = a_lN - 1; k >= 0; k--)
    {
        if (a_plTemp2[k] != k)
            for (j = 0; j <= a_lN - 1; j++)
            {
                u = k*a_lN + j; v = a_plTemp2[k] * a_lN + j;
                p = a_peMatrix[u]; a_peMatrix[u] = a_peMatrix[v]; a_peMatrix[v] = p;
            }
        if (a_plTemp1[k] != k)
            for (i = 0; i <= a_lN - 1; i++)
            {
                u = i*a_lN + k; v = i*a_lN + a_plTemp1[k];
                p = a_peMatrix[u]; a_peMatrix[u] = a_peMatrix[v]; a_peMatrix[v] = p;
            }
    }

    return (1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alMATRIX_Multiplaction(FLOAT64 * a_peMatrixA, FLOAT64 * a_peMatrixB, INT32 m, INT32 n, INT32 k, FLOAT64* a_peMatrixC)
{
    INT32 i,j,l,u;
    for (i=0; i<=m-1; i++)
    for (j=0; j<=k-1; j++)
      { 
      	u = i * k + j;
		a_peMatrixC[u]=0.0;
        for (l=0; l<=n-1; l++)
          a_peMatrixC[u] = a_peMatrixC[u] + a_peMatrixA[i*n+l]*a_peMatrixB[l*k+j];
      }
    return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alMATRIX_Transpose(FLOAT64 * __restrict a_peMatrixA, INT32 m, INT32 n, FLOAT64 * __restrict a_peMatrixX)
{
	INT32 i , j;

	for (i = 0 ; i < m ;i++)
	{
		for(j = 0; j< n ; j++)
			a_peMatrixX[j * m + i] = a_peMatrixA[i * n + j];
	}
}

/** \endcond DOXYGEN_EXCLUDE */
