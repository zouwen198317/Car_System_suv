
#include "VisionMeIntrinsic.h"

#ifdef WIN32

#if 0 // 直接從 C64xSimulator 取用 

__int64 g_read8Result;

/*Allows unaligned loads of 4 bytes from memory, 
  fixe me: 1.doesn't implement store; 2.does not figure the unalgin of input*/
int _mem4_const(const void *ptr)
{
    const char *add = (const char *)ptr;
    return (int)((int)add[0]&0xff|(int)(add[1]&0xff)<<8|(int)(add[2]&0xff)<<16|(int)(add[3]&0xff)<<24);
}

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
__int64 _memd8_const (const void *add)
{
	const char *ptr = (const char *)add;
//    __int64 test1 = ptr[0]&0xFF;
//    __int64 test2 = (__int64)(ptr[1]&0xFF)<<8;    
//    __int64 test3 = (__int64)(ptr[2]&0xFF)<<16;
//    __int64 test4 = (__int64)(ptr[3]&0xFF)<<24; 
//
//    __int64 test5 = (__int64)(ptr[4]&0xFF)<<32;
//    __int64 test6 = (__int64)(ptr[5]&0xFF)<<40;    
//    __int64 test7 = (__int64)(ptr[6]&0xFF)<<48;
//    __int64 test8 = (__int64)(ptr[7]&0xFF)<<56; 

    __int64 total = (__int64)(ptr[0]&0xFF|(__int64)(ptr[1]&0xFF)<<8|(__int64)(ptr[2]&0xFF)<<16|(__int64)(ptr[3]&0xFF)<<24|
		(__int64)(ptr[4]&0xFF)<<32|(__int64)(ptr[5]&0xFF)<<40|(__int64)(ptr[6]&0xFF)<<48|(__int64)(ptr[7]&0xFF)<<56);
    
    g_read8Result = total;
        
	return total;
}


/*For each pair of 8-bit values in src1 and src2, the 8-bit value from
src1 is multiplied with the 8-bit value from src2. The four products
are summed together.*/
int _dotpsu4 (int src1, int src2)
{
    char mask1, mask2, mask3, mask4; 
    int data1, data2, data3, data4 , sum; 
    
    mask1 = (src1&0xff);
    mask2 = ((src1>>8)&0xff);
    mask3 = ((src1>>16)&0xff);
    mask4 = ((src1>>24)&0xff);
    
    data1 = (src2&0xff)*mask1;
    data2 = ((src2>>8)&0xff) * mask2;
    data3 = ((src2>>16)&0xff) * mask3;
    data4 = ((src2>>24)&0xff)* mask4;
    
    sum = (data1+data2+data3+data4);   
    
    return sum;
}
/*Two signed 32-bit values are saturated to 16-bit values and packed
into the return value*/
int _spack2 (int src1, int src2)
{

    src1 = (src1 > 16384)?16384:src1;
    src2 = (src2 > 16384)?16384:src2;  
        
    return (int)((src2&0xFFFF) | ((src1<<16)&0xFFFF0000));     
}

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
unsigned _extu (unsigned src2, unsigned csta, unsigned cstb)
{
    unsigned int word = (unsigned int)(0x0 | src2);//zero-extended to 32 bits
    word <<= csta;
    word >>= cstb;
    return (unsigned)word;
}

/* Returns the low (even) register of a double register pair
    example:
    double r1_76543210;
    int r1_3210;
    r1_3210 = _lo(r1_76543210);
*/

unsigned _lo (__int64 src)
{
    unsigned int lo = (unsigned int)src;
    return (unsigned)lo;
}

/*  Returns the high (odd) register of a double register pair
    example:
    double r1_76543210;
    int r1_7654;
    r1_7654 = _hi(r1_76543210);
*/
unsigned _hi (__int64 src)
{
    unsigned int hi = (unsigned int)((__int64)src>>32);
    return (unsigned)hi;
}

/*The lower halfword of src1 is placed in the upper halfword the
return value. The upper halfword of src2 is placed in the lower
halfword the return value.
example:

unsigned r1_3210, r1_7654;
unsigned r1_5432;

r1_5432 = _packlh2(r1_7654, r1_3210); */

unsigned _packlh2 (unsigned src1, unsigned src2)
{
    return (((src1<<16)&0xFFFF0000) | ((src2>>16)&0xFFFF)); 
}
/*
Four signed 16-bit values are saturated to 8-bit values and packed
into the return value
example:

int sum32, sum10;
unsigned sum3210;

sum3210 = _spacku4(sum32, sum10);*/

unsigned _spacku4 (int src1 , int src2)
{
    int word0, word1, word2, word3;
	
	word0 = src2&0xFFFF;
	word0 = (word0 & 0x8000)?0:((word0 & 0x7f00)?255:word0);
	word1 = (src2&0xFFFF0000)>>16;
	word1 = (word1 & 0x8000)?0:((word1 & 0x7f00)?255:word1);

	word2 = src1&0xFFFF;
	word2 = (word2 & 0x8000)?0:((word2 & 0x7f00)?255:word2);
	word3 = (src1&0xFFFF0000)>>16;
	word3 = (word3 & 0x8000)?0:((word3 & 0x7f00)?255:word3);
    
    return (word0 | word1<<8 | word2<<16 | word3<<24);  
}

/*aligned loads of 4 bytes from memory*/
unsigned _amem4_const (const void *ptr)
{
    const char *add = (const char *)ptr;
    return (int)((int)add[0]&0xff|(int)(add[1]&0xff)<<8|(int)(add[2]&0xff)<<16|(int)(add[3]&0xff)<<24);
}

/*
Adds the upper and lower halves of src1 to the upper and lower
halves of src2 and returns the result. Any overflow from the lower
half add does not affect the upper half add.
*/
int _add2 (int src1, int src2)
{
	return (( ((src1&0x0000ffff)+(src2&0x0000ffff)) &0x0000ffff) | ( ( ((src1&0xffff0000) >> 16)+
                   ((src2&0xffff0000) >> 16) ) << 16 ) );    
}


/*Calculates the absolute value for each 16-bit value*/
int _abs2 (int src)
{
    short hWord,lWord;
    
    lWord = (src&0x0000ffff);
    lWord = (lWord<0) ? - lWord : lWord;
    hWord = ((src&0xffff0000) >> 16);
    hWord = (hWord<0) ? - hWord : hWord;
    
	return (int)(lWord | hWord << 16);     
}


/*Exchanges pairs of bytes (an endian swap) within each 16-bit value*/

unsigned _swap4 (unsigned src)
{
    unsigned int add = (unsigned int)src;
    
    return ((add<<8)&0xFF00)|((add>>8)&0xFF)|((add<<8)&0xFF000000)|((add>>8)&0xFF0000);
}

/*Packs alternate low bytes bytes into return value.
example:
        r1_6420 = _packl4(r1_7654, r1_3210);
*/

unsigned _packl4 (unsigned src1, unsigned src2)
{
    
    return ((src1<<8)&0xFF000000)|((src1<<16)&0xFF0000) | ((src2>>8)&0xFF00)| ((src2)&0xFF); 
}

/*
For each 16-bit quantity in src1, the quantity is arithmetically or
unsigned shru2 (unsigned src1, unsigned src2); SHRU2 logically shifted right by src2 number of bits. src1 can contain signed
or unsigned values.
sum10 = _shr2(sum10, wShiftSharp); //do shift
*/
int _shr2 (int src1, unsigned src2)
{
    int out1 = ((src1>>16)&0xFFFF)>>src2;
    int out2 = (src1&0xFFFF)>>src2;
    return ((out1<<16)&0xFFFF0000)|(out2&0xFFFF);
}
/*
Places the smaller of each pair of values in the corresponding
position in the return value. Values can be 16-bit signed or 8-bit
unsigned.
*/
int _min2 (int src1, int src2)
{
    int src1_1, src1_2/*, src2_1, src2_2*/;

    src1_1 = ((src1>>16)&0xFFFF);
    src1_2 = (src1&0xFFFF);    
    if(src1_1 > ((src2>>16)&0xFFFF))
        src1_1 = ((src2>>16)&0xFFFF);
    if(src1_2 > (src2&0xFFFF))
        src1_2 = (src2&0xFFFF);
        
    return ((src1_1<<16)&0xFFFF0000)|(src1_2);             
}

/*
Places the larger of each pair of values in the corresponding
position in the return value. Values can be 16-bit signed or 8-bit
unsigned.
*/
int _max2 (int src1, int src2)
{
    int src1_1, src1_2/*, src2_1, src2_2*/;

    src1_1 = ((src1>>16)&0xFFFF);
    src1_2 = (src1&0xFFFF);    
    if(src1_1 < ((src2>>16)&0xFFFF))
        src1_1 = ((src2>>16)&0xFFFF);
    if(src1_2 < (src2&0xFFFF))
        src1_2 = (src2&0xFFFF);
        
    return ((src1_1<<16)&0xFFFF0000)|(src1_2);             
}

/*
Unpacks the two low unsigned 8-bit values into unsigned packed
16-bit values
example:

pixel_1_0 = _unpklu4 (pixel3210); 

*/
unsigned _unpklu4 (unsigned src)
{
    return ((src<<8)&0XFF0000)| (src&0xFF);
}

/*
Unpacks the two high unsigned 8-bit values into unsigned packed
16-bit values

example:

pixel_3_2 = _unpkhu4(pixel3210)

*/
unsigned _unpkhu4 (unsigned src)
{
    return ((src>>16)&0xFF)| ((src>>8)&0xFF0000);
}
//unsigned char TestTable[69]=
//{
//    0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20,
//    22, 24, 26, 28, 30, 32, 34, 36, 38, 40,
//    42, 44, 46, 48, 50, 52, 54, 56, 58, 60,
//    62, 64, 68, 73, 77, 82, 86, 91, 96, 100,
//    105, 109, 114, 118, 123, 128, 133, 139, 144, 150,
//    155, 161, 166, 172, 178, 183, 189, 194, 200, 205,
//    211, 217, 222, 228, 233, 239, 244, 250
//};
//
//
//int main(int argc, char **argv)
//{	
//    int mult1   = 0x01010101;
//	unsigned int i = 0, j = 0;
//	i = _mem4_const(TestTable);
//    j = _dotpsu4(mult1, i);
//
//    printf("i = 0x%x, j = %d\n", i , j);	
//
//}

#endif

#endif
