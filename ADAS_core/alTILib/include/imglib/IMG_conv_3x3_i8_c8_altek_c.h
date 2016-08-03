
#pragma once

void IMG_conv_3x3_i8_c8_altek_cn (const unsigned char *restrict inptr,
                               unsigned char      *restrict outptr,
                               int                           width,
                               int                           pitch,
                               const char           *restrict mask,
                               int                           shift);
