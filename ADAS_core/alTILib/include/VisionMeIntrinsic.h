
/****************************************************************************************

File Name: VisionMeIntrinsic.h
Description: This file defines used c model codes of intrinsic functions for TI's VisionMe platform.

*****************************************************************************************/

/**
  *  \addtogroup TILib
  *  @{
  */

#pragma once

#ifdef WIN32

#include "c6xsim/C6xSimulator_type_modifiers.h"
#include "c6xsim/C6xSimulator.h"

#if 0 // 直接從 C64xSimulator 取用 

/*Allows unaligned loads of 4 bytes from memory*/
int _mem4_const(const void *add);

/*For each pair of 8-bit values in src1 and src2, the 8-bit value from
src1 is multiplied with the 8-bit value from src2. The four products
are summed together.*/

int _dotpsu4 (int src1, int src2);

/*Two signed 32-bit values are saturated to 16-bit values and packed
into the return value*/

int _spack2 (int src1, int src2);

/*
Four signed 16-bit values are saturated to 8-bit values and packed
into the return value
example:

int sum32, sum10;
unsigned sum3210;

sum3210 = _spacku4(sum32, sum10);*/
unsigned _spacku4 (int src1 , int src2);

/*The lower halfword of src1 is placed in the upper halfword the
return value. The upper halfword of src2 is placed in the lower
halfword the return value.
example:

unsigned r1_3210, r1_7654;
unsigned r1_5432;

r1_5432 = _packlh2(r1_7654, r1_3210); */

unsigned _packlh2 (unsigned src1, unsigned src2);

/*  Returns the high (odd) register of a double register pair
    example:
    double r1_76543210;
    int r1_7654;
    r1_7654 = _hi(r1_76543210);
*/
unsigned _hi (__int64 src);

/* Returns the low (even) register of a double register pair
    example:
    double r1_76543210;
    int r1_3210;
    r1_3210 = _lo(r1_76543210);
*/

unsigned _lo (__int64 src);


/* LDNDW Allows unaligned loads of 8 bytes from memory
    
    example:	
	const char filter[9] = 
	{
	    1,2,1,
	    2,4,2,
	    1,2,1
	};
	_memd8_const(&filter[0]):0x201020402010201
*/
__int64 _memd8_const (const void *add);

/*
Extracts the specified field in src2, zero-extended to 32 bits. The
extract is performed by a shift left followed by a unsigned shift right;
csta : shift left amounts.
cstb : shift right amounts
example:
const char filter[4] = {1,2,1,2};
mask1_0 = _extu( _mem4_const(&filter[0]), 8, 8); 
output:
_mem4_const(&filter[0]):0x2010201
mask1_0              :0x10201
*/
unsigned _extu (unsigned src2, unsigned csta, unsigned cstb);

/*aligned loads of 4 bytes from memory*/
unsigned _amem4_const (const void *ptr);

/*
Adds the upper and lower halves of src1 to the upper and lower
halves of src2 and returns the result. Any overflow from the lower
half add does not affect the upper half add.
*/
int _add2 (int src1, int src2);

/*Calculates the absolute value for each 16-bit value*/
int _abs2 (int src);

/*Exchanges pairs of bytes (an endian swap) within each 16-bit value*/
unsigned _swap4 (unsigned src);


/*Packs alternate low bytes bytes into return value.*/
unsigned _packl4 (unsigned src1, unsigned src2);

/*
For each 16-bit quantity in src2, the quantity is arithmetically or
unsigned shru2 (unsigned src1, unsigned src2); SHRU2 logically shifted right by src1 number of bits. src2 can contain signed
or unsigned values
*/
int _shr2 (int src1, unsigned src2);


/*
Places the smaller of each pair of values in the corresponding
position in the return value. Values can be 16-bit signed or 8-bit
unsigned.
*/
int _min2 (int src1, int src2);

/*
Places the larger of each pair of values in the corresponding
position in the return value. Values can be 16-bit signed or 8-bit
unsigned.
*/
int _max2 (int src1, int src2);

/*
Unpacks the two low unsigned 8-bit values into unsigned packed
16-bit values
*/
unsigned _unpklu4 (unsigned src);

/*
Unpacks the two high unsigned 8-bit values into unsigned packed
16-bit values

*/
unsigned _unpkhu4 (unsigned src);
#endif

#endif

/**
  *  @}
  */