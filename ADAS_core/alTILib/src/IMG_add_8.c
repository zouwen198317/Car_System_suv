
#include "alTILibDef.h"

#ifdef WIN32

void IMG_add_8_ucu
(
    unsigned char * restrict imgR1, /* Image 1 read pointer */
    char * restrict imgR2, /* Image 2 read pointer */
    unsigned char * restrict imgW, /* Output image pointer */
    int count /* Number of samples in image */
)
{
    int lIndex;
    int lSum = 0;

    for(lIndex = 0; lIndex < count; lIndex++, imgR1++, imgR2++, imgW++)
    {
        lSum = (*imgR1) + (*imgR2);

        lSum = (lSum > 255) ? 255 : lSum;
        (*imgW) = (lSum < 0) ? 0 : lSum;
    }
}

void IMG_add_8_ucu_YUYV
(
    unsigned char * restrict imgR1, /* Image 1 read pointer */
    char          * restrict imgR2, /* Image 2 read pointer */
    unsigned char * restrict imgW, /* Output image pointer with YUYV */
    int count /* Number of samples in image */
)
{
    int lIndex;
    int lSum = 0;

    for(lIndex = 0; lIndex < count; lIndex++, imgR1++, imgR2++, imgW+=2)
    {
        lSum = (*imgR1) + (*imgR2);

        lSum = (lSum > 255) ? 255 : lSum;
        (*imgW) = (lSum < 0) ? 0 : lSum;
    }
}

#else

void IMG_add_8
(
    char * restrict imgR1, /* Image 1 read pointer */
    char * restrict imgR2, /* Image 2 read pointer */
    char * restrict imgW, /* Output image pointer */
    int count /* Number of samples in image */
)
{
    int i;
    long long im1_p7_p6_p5_p4_p3_p2_p1_p0, im2_p7_p6_p5_p4_p3_p2_p1_p0;
    int im1_p7_p6_p5_p4, im1_p3_p2_p1_p0, im2_p7_p6_p5_p4, im2_p3_p2_p1_p0;
    int res_p7_p6_p5_p4, res_p3_p2_p1_p0;
    for (i = 0; i < count >> 4; i += 16) 
    {
        im1_p7_p6_p5_p4_p3_p2_p1_p0 = _amem8(imgR1);
        im2_p7_p6_p5_p4_p3_p2_p1_p0 = _amem8(imgR2);
        imgR1 += 8;
        imgR2 += 8;
        im1_p3_p2_p1_p0 = _loll (im1_p7_p6_p5_p4_p3_p2_p1_p0);
        im1_p7_p6_p5_p4 = _hill (im1_p7_p6_p5_p4_p3_p2_p1_p0);
        im2_p3_p2_p1_p0 = _loll (im2_p7_p6_p5_p4_p3_p2_p1_p0);
        im2_p7_p6_p5_p4 = _hill (im2_p7_p6_p5_p4_p3_p2_p1_p0);
        res_p3_p2_p1_p0 = _add4 (im1_p3_p2_p1_p0, im2_p3_p2_p1_p0);
        res_p7_p6_p5_p4 = _add4 (im1_p7_p6_p5_p4, im2_p7_p6_p5_p4);
        _amem8(imgW) = _itoll (res_p7_p6_p5_p4, res_p3_p2_p1_p0);
        imgW += 8;
        im1_p7_p6_p5_p4_p3_p2_p1_p0 = _amem8(imgR1);
        im2_p7_p6_p5_p4_p3_p2_p1_p0 = _amem8(imgR2);
        imgR1 += 8;
        imgR2 += 8;
        im1_p3_p2_p1_p0 = _loll (im1_p7_p6_p5_p4_p3_p2_p1_p0);
        im1_p7_p6_p5_p4 = _hill (im1_p7_p6_p5_p4_p3_p2_p1_p0);
        im2_p3_p2_p1_p0 = _loll (im2_p7_p6_p5_p4_p3_p2_p1_p0);
        im2_p7_p6_p5_p4 = _hill (im2_p7_p6_p5_p4_p3_p2_p1_p0);
        res_p3_p2_p1_p0 = _add4 (im1_p3_p2_p1_p0, im2_p3_p2_p1_p0);
        res_p7_p6_p5_p4 = _add4 (im1_p7_p6_p5_p4, im2_p7_p6_p5_p4);
        _amem8(imgW) = _itoll (res_p7_p6_p5_p4, res_p3_p2_p1_p0);
        imgW += 8;
    }
}

void IMG_add_8_ucu
(
    unsigned char * restrict imgR1, /* Image 1 read pointer */
    char * restrict imgR2, /* Image 2 read pointer */
    unsigned char * restrict imgW, /* Output image pointer */
    int count /* Number of samples in image */
)
{
    int lIndex;
    int lSum = 0;

    for(lIndex = 0; lIndex < count; lIndex++, imgR1++, imgR2++, imgW++)
    {
        lSum = (*imgR1) + (*imgR2);

        lSum = (lSum > 255) ? 255 : lSum;
        (*imgW) = (lSum < 0) ? 0 : lSum;
    }
}

void IMG_add_8_ucu_YUYV
(
    unsigned char * restrict imgR1, /* Image 1 read pointer */
    char          * restrict imgR2, /* Image 2 read pointer */
    unsigned char * restrict imgW, /* Output image pointer with YUYV */
    int count /* Number of samples in image */
)
{
    int lIndex;
    int lSum = 0;

    for(lIndex = 0; lIndex < count; lIndex++, imgR1++, imgR2++, imgW+=2)
    {
        lSum = (*imgR1) + (*imgR2);

        lSum = (lSum > 255) ? 255 : lSum;
        (*imgW) = (lSum < 0) ? 0 : lSum;
    }
}

#endif