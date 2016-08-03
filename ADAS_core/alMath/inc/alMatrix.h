
#include "mtype.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
    *  \defgroup alMATRIX   alMatrix
    *  The module to do matrix operation.
    *  @{
    */

    /**
    \brief This function generate a unit matrix: I
    \param a_peMatrix [IN] Input a_lN x a_lN matrix
    \param a_lN [IN] Col count of the matrix
    */
    void alMATRIX_Unit(FLOAT64 * a_peMatrix, INT32 a_lN);

    /**
    \brief This function implemnet Matrix add operation
    \param a_peMatrix1 [IN] Input a_lM x a_lN matrix
    \param a_peMatrix2 [IN] Input a_lM x a_lN matrix
    \param a_lM [IN] Row count of the matrix
    \param a_lN [IN] Col count of the matrix
    \param a_peMatrix3 [IN] Output the a_lM x a_lN matrix - a_peMatrix1 + a_peMatrix1
    */
    void alMATRIX_Add(FLOAT64 * a_peMatrix1, FLOAT64 * a_peMatrix2, INT32 a_lM, INT32 a_lN, FLOAT64 * a_peMatrix3);

    /**
    \brief This function implemnet Matrix minus operation
    \param a_peMatrix1 [IN] Input a_lM x a_lN matrix
    \param a_peMatrix2 [IN] Input a_lM x a_lN matrix
    \param a_lM [IN] Row count of the matrix
    \param a_lN [IN] Col count of the matrix
    \param a_peMatrix3 [IN] Output the a_lM x a_lN matrix - a_peMatrix1 + a_peMatrix1
    */
    void alMATRIX_Minus(FLOAT64 * a_peMatrix1, FLOAT64 * a_peMatrix2, INT32 a_lM, INT32 a_lN, FLOAT64 * a_peMatrix3);

    /**
    \brief This function implemnet Matrix NxN matrix inverse
    \param a_peMatrix [IN/OUT] Input n x n matrix and output the inversed matrix.
    \param n [IN] dimension
    */
    INT32 alMATRIX_InverseNbyN(FLOAT64 * a_peMatrix, INT32 n);

    /**
    \brief This function implemnet Matrix NxN matrix inverse
    \param a_peMatrix [IN/OUT] Input n x n matrix and output the inversed matrix.
    \param a_lN [IN] Dimension of the matrix
    \param a_plTemp1 [IN] 1st temp buffer for calculation, should be a_lN x a_lN length.
    \param a_plTemp2 [IN] 2nd temp buffer for calculation, should be a_lN x a_lN length.
    */
    INT32 alMATRIX_Inverse2(FLOAT64 * a_peMatrix, INT32 a_lN, INT32 * a_plTemp1, INT32 * a_plTemp2);

    /**
    \brief This function implemnet Matrix Multiplication: a_peMatrixC = a_peMatrixA x a_peMatrixB
    \param a_peMatrixA [IN] m x n matrix
    \param a_peMatrixB [IN] n x k matrix
    \param m [IN] row dimension of the "a_peMatrix" matrix
    \param n [IN] column dimension of the "a_peMatrix" matrix and row dimension of the "b" matrix
    \param k [IN] column dimension of the "b" matrix
    \param a_peMatrixC [OUT] a_peMatrixA x a_peMatrixB matrix
    */
    void alMATRIX_Multiplaction(FLOAT64 * a_peMatrixA, FLOAT64 * a_peMatrixB, INT32 m, INT32 n, INT32 k, FLOAT64 * a_peMatrixC);

    /**
    \brief This function implemnet Matrix NxN matrix transpose
    \param a_peMatrixA [IN] m x n matrix
    \param m [IN] Row dimension of the "a_peMatrixA" matrix
    \param n [IN] Column dimension of the "a_peMatrixA" matrix
    \param a_peMatrixX [OUT] The transpose matrix of a_peMatrixA (n x m matrix)
    */
    void alMATRIX_Transpose(FLOAT64 * __restrict a_peMatrixA, INT32 m, INT32 n, FLOAT64 * __restrict a_peMatrixX);

    /**
    *   @}
    */

#ifdef __cplusplus
}
#endif

