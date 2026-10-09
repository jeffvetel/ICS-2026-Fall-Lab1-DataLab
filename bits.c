/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  /*将一个末位1移至最高位即可*/
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  /*注意到x ^ y = (x & ~y) | (~x & y)，然后将|重写为用~与&表示的形式*/
	return ~( (~(x & ~y)) & (~(~x & y)) );
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  /*先判断x的符号，得到isNegative=0xFFFFFFFF或0x00000000；在&作用下，非负数直接输出0，而负数将输出后面的-x*/
  int isNegative = x >> 31;
  return isNegative & (~x + 1);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  /*取出src对应的byte，然后清除x中dst对应原有byte，并使用或运算与src对应byte（移位后）合并*/
  int srcshift = src << 3;
  int dstshift = dst << 3;
  int srcbyte = (x >> srcshift) & 0xFF;
  return (x & ~(0xFF << dstshift)) | (srcbyte << dstshift);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  /*只需要解决负数算数右移的高位添1问题；利用高位添1构造一个前n位为0、其余为1的mask，与算术右移结果&合并即可*/
  int logicalmask = ~( ((1 << 31) >> n) << 1);
  return (x >> n) & logicalmask;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  /*构造mask=0x0F0F0F0F，一次性将x的每个byte的后四位取出并左移，然后取出全部前四位并右移，合并得到结果*/
  int mask_0 = 0x0F;
  int mask_1 = (mask_0 << 8) | mask_0;
  int mask = (mask_1 << 16) | mask_1;
  return ((x & mask) << 4) | ((x >> 4) & mask); /*x >> 4算术右移的添1会被mask抹去*/
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  /*初步想法：只需要得到最低含0位对应的mask即可，将x与这个mask作|运算之后再做一次就得到了所需的结果；
   *进一步,注意到x & (~x + 1)得到了x最低含1位对应的mask，故而~x & (x + 1)即得到这个mask*/
  int mask_1 = ~x & (x + 1);
  int x_1 = x | mask_1;
  int mask_2 = ~x_1 & (x_1 + 1);
  return mask_2;
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  /*记n(x)为x二进制表示下的1的个数，N(x)为此函数的输出，易知n(x) + n(y) = n(x ^ y) + 2n(x & y)，且后一项不影响奇偶性；
   *进一步，将x拆为前后两半A与B，有n(x) = n(A) + n(B)，故而有N(x) = N(A ^ B)，如此迭代至仅剩一位。
   *由于所有信息逐步集中于最后的“有效位”，故而高位出现算数右移也不影响结果;此外，从样例来看，应该在以上方法的输出中加入取反。*/
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  return !(x & 1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  /*若n<=31，则是将x（逻辑）右移n位并将最低n位左移(32-n)位至最高n位处、再将这两部分用|合并。故将n先模32取余，即可进行操作。*/
  int N = n & 31;
  int X_high = x << ( (32 + (~N +1)) & 31); //用& 31规避n=0时左移32位的问题
  int logicalmask = ~( ((1 << 31) >> N) << 1);
  int X_low = (x >> N) & logicalmask;
  return X_high | X_low;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  /*x % (2**n)即x的最低n位，而除去后n位后高位的数（记为q）就是所需2**n的倍数或该值-1；
   *除等距情况外，通过将x加上2**(n-1)或2**(n-1)，得到新的q均是所需的；对于等距情况，采用2**(n-1) + q（初始） & 1作为开关，故最终选择将此值作为整体的判据*/
  int q0 = x >> n;
  int q0_isOdd = q0 & 1;
  int adder = ((1 << n) >> 1) + ~0 + q0_isOdd;
  int q = (x + adder) >> n; //由题设x + adder不会溢出
  return q << n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  /*由x + y = 2*(x & y) + (x ^ y)，有[(x+y)/2] = (x & y) + [(x ^ y)/2] = (x & y) + (x ^ y) >> 1，其中[X]是floor(X)。
   *所以先求出(x & y) + ((x ^ y) >> 1)，然后对于x+y为奇数的情况向x修约，即在x-y>0时将所得值+1。*/
  int mid0 = (x & y) + ((x ^ y) >> 1);
  int oddsum = (x + y) & 1;
  int sgnx = (x >> 31) & 1;
  int sgny = (y >> 31) & 1;
  int diffsgn = sgnx ^ sgny;  //用于排除x-y溢出的情况
  int delta = x + (~y + 1);
  int sgndelta = delta >> 31; //即使有算数右移也会被消去
  int real_sgndelta = (diffsgn & !sgnx) | (!diffsgn & !sgndelta & !!delta);  //!!delta除去x=y的情况
  int mid = mid0 + (oddsum & real_sgndelta);
  return mid;
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  /*类似上题求delta的方法，只需要判断x-a和x-b是否异号即可*/
  int sgnx = (x >> 31) & 1;
  int sgna = (a >> 31) & 1;
  int sgnb = (b >> 31) & 1;

  int delta_x_a = x + (~a + 1);
  int delta_x_b = x + (~b + 1);
  int sgn_delta_x_a = (delta_x_a >> 31) & 1;
  int sgn_delta_x_b = (delta_x_b >> 31) & 1;
  int diffsgn_x_a = sgnx ^ sgna;  //用于排除x-a溢出的情况，下同
  int diffsgn_x_b = sgnx ^ sgnb;

  int x_over_a = (diffsgn_x_a & !sgnx) | (!diffsgn_x_a & !sgn_delta_x_a & !!delta_x_a);
  int x_over_b = (diffsgn_x_b & !sgnx) | (!diffsgn_x_b & !sgn_delta_x_b & !!delta_x_b);
  int isbetween = (x_over_a ^ x_over_b) | !delta_x_a | !delta_x_b;  //在此处再考虑区间端点情况
  return isbetween;
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  /*注意到5x = 4x + x = x << 2 + x，检查4x是否溢出直接看x从左开始第2、3位是否与符号位相同，即符号位右移2位后是否与x最高三位相同；
   *然后在4x未溢出前提下再检查5x是否溢出，只需判断符号位是否与x相同即可*/
  int sgnx = (x >> 31) & 1;
  int xhigh3 = (x >> 29) & 7;
  int exp_high3 = sgnx | (sgnx << 1) | (sgnx << 2);
  int x4_overflow = !!(exp_high3 + (~xhigh3 + 1));
  int x5 = (x << 2) + x;
  int sgnx5 = (x5 >> 31) & 1;
  int x5_overflow = x4_overflow | (sgnx ^ sgnx5);

  int min = 1 << 31;  //INT_MIN
  int overflowresult = min + ~(x >> 31);  //注意到INT_MAX = INT_MIN + ~0而INT_MIN = INT_MIN + ~0xFFFFFFFF
  int overflowmask = ~(x5_overflow + ~0); //若溢出则得0xFFFFFFFF，否则得0
  return (overflowmask & overflowresult) | (~overflowmask & x5);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  /*逐步判断x+y与(x+y)+z两步中是否溢出及溢出方向*/
  int sgn_x = x >> 31;
  int sgn_y = y >> 31;
  int sgn_z = z >> 31;

  int sum_xy = x + y;
  int sgn_sum_xy = sum_xy >> 31;
  int xy_overflow = ~(sgn_x ^ sgn_y) & (sgn_x ^ sgn_sum_xy);
  int overflowdir_xy = xy_overflow & ((sgn_x << 1) + 1);  //未溢出得0，溢出且x为正得1，溢出且x为负得-1

  int sum_xyz = sum_xy + z;
  int sgn_sum_xyz = sum_xyz >> 31;
  int xyz_overflow = ~(sgn_sum_xy ^ sgn_z) & (sgn_sum_xy ^ sgn_sum_xyz);
  int overflowdir_xyz = xyz_overflow & ((sgn_sum_xy << 1) + 1);
  return overflowdir_xy + overflowdir_xyz;  //不可能两次溢出同向，直接相加即可
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  /*分为NaN、非规格化数、规格化数三种情况，分别处理E和M*/
  unsigned sgn = uf & 0x80000000u;
  unsigned exp = (uf >> 23) & 0xFFu;
  unsigned frac = uf & 0x7FFFFFu;
  unsigned result;

  if (exp == 0xFFu) result = uf;  //NaN或无穷直接返回
    else if (exp == 0) {  //非规格化数
      unsigned prod0 = frac * 3;
      unsigned prod = prod0 >> 1;
      if ((prod0 & 1u) && (prod & 1u))  prod++; //round to nearest even
      if (prod >= 0x800000u) { //超出2^23即非规格化数的尾数上限，须转为规格化数
            exp = 1;
            frac = prod - 0x800000u;
        } else  frac = prod;
      result = sgn | (exp << 23) | frac;
    } else {  //规格化数
        unsigned real_frac = frac | 0x800000u;
        unsigned prod0 = real_frac * 3;
        unsigned prod;
        unsigned rem;

        if (prod0 >= 0x2000000u) {   //右移1位前超过2^25，超过了2*real_frac的上限，需要指数+1，改为右移2位
          prod = prod0 >> 2;
          rem = prod0 & 3u; 
          if (rem > 2u || (rem == 2u && (prod & 1u)) ) prod++;  //剩余部分>2或剩余部分=2时的round to nearest even
          exp++; 

          if (exp == 0xFFu)   result = sgn | 0x7F800000u;  //指数溢出到无穷
          else {
            frac = prod - 0x800000u;
             result = sgn | (exp << 23) | frac;
          }
        } else {
          prod = prod0 >> 1;
          if ((prod0 & 1u) && (prod & 1u))  prod++; //round to nearest even
          frac = prod - 0x800000u;
          result = sgn | (exp << 23) | frac;
          }
    }

  return result;
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  /*分为NaN、非规格化数、规格化数三种情况依次处理即可*/
  unsigned sgn = uf & 0x80000000u;
  unsigned exp = (uf >> 23) & 0xFFu;
  unsigned frac = uf & 0x7FFFFFu;
  unsigned result;

  if (exp == 0xFFu) result = uf;  //NaN或无穷直接返回
  else if (exp < 126u) result = sgn; // |uf|<0.5，直接舍入到0（保留符号）
  else if (exp == 126u) { //0.5<=|uf|<1
      if (frac == 0) result = sgn;  //|uf|=0.5, round to nearest even
      else result = sgn | 0x3F800000u; //|uf|>0.5，舍入到1
  } else if (exp >= 150u) result = uf;  //|uf|>=2^23，已经是整数
    else {  /* 127 ≤ exp ≤ 149，需要舍入小数部分 */
      unsigned shift = 150u - exp;
      unsigned real_frac = frac | 0x800000u;

      unsigned prod = real_frac >> shift;
      unsigned mask = (1u << shift) - 1u;
      unsigned rem = real_frac & mask;
      unsigned half = 1u << (shift - 1u);
      unsigned one;

      if (rem > half || (rem == half && (prod & 1u))) prod++; //round-to-nearest-even

      one = 1u << (23u - shift);
      if (prod == (one << 1)) {  //进位导致尾数溢出，故指数加1、尾数清零
        exp++;
        frac = 0;
      } else frac = (prod - one) << shift;

      result = sgn | (exp << 23) | frac;
    }

  return result;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  /*先找最高有效位以决定E，然后对齐有效数字、截取尾数，经round to even后变回浮点表示*/
  unsigned ux = x;
  unsigned sgn;
  int msb = 31;
  unsigned exp;
  unsigned mant;
  unsigned shift;
  unsigned result;
  unsigned rest;
  unsigned half;

    if (x == 0) result = 0;
    else {
      sgn = ux & 0x80000000u;
      if (x < 0) ux = ~ux + 1u;

      while ((ux & (1u << msb)) == 0) { //找到最高有效位
        msb--;
      }

      exp = msb + 127;

      if (msb <= 23) mant = ux << (23 - msb);
      else {
        shift = msb - 23;
        mant = ux >> shift;

        rest = ux & ((1u << shift) - 1u);
        half = 1u << (shift - 1u);

            /*  */
        if (rest > half || (rest == half && (mant & 1u))) { //round to nearest even
            mant++;
            if (mant == 0x1000000u) {
              exp++;
              mant = 0x800000u;
            }
        }
      }
      result = sgn | (exp << 23) | (mant & 0x7FFFFFu);
    }

  return result;
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  /*注意到，对于0b00~0b11，其两位数码和就等于其中1的计数，故而将x分为2bit的小段后作此加和，就将1的个数转为了字面值存储在这个新的数里；
   *接着将x依次切分为4bit、8bit并执行相邻加和，相当于将结果集中于最后一个字节，就可以得到结果（因为2^8-1>32）*/
  int mask_odd_bits = 0x55; //0b01010101
  int mask_2bits = 0x33;  //0b00110011
  int mask_4bits = 0x0F;  //0b00001111

  int resultmask = 0x3F;  //最终结果中取末6位，因为结果不大于32=2^5

  mask_odd_bits = mask_odd_bits | (mask_odd_bits << 8);
  mask_odd_bits = mask_odd_bits | (mask_odd_bits << 16);

  mask_2bits = mask_2bits | (mask_2bits << 8);
  mask_2bits = mask_2bits | (mask_2bits << 16);

  mask_4bits = mask_4bits | (mask_4bits << 8);
  mask_4bits = mask_4bits | (mask_4bits << 16);

  x = (x & mask_odd_bits) + ((x >> 1) & mask_odd_bits);
  x = (x & mask_2bits) + ((x >> 2) & mask_2bits);
  x = (x & mask_4bits) + ((x >> 4) & mask_4bits);

  x = x + (x >> 8);
  x = x + (x >> 16);
  return x & resultmask;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  /*可以将x依次切分成每2bit、4bit、8bit、16bit的分段，在每段内部执行前后两半的交换*/
  int mask_16bits = 0xFF | (0xFF << 8); //0x0000FFFF

  //GPT直接给出了以下更省操作数的mask定义法：（原方法类似上一题，能跑通但超出了规定最大操作数）
  int mask_8bits = mask_16bits ^ (mask_16bits << 8);  // 0x00FF00FF
  int mask_4bits = mask_8bits ^ (mask_8bits << 4);  // 0x0F0F0F0F
  int mask_2bits = mask_4bits ^ (mask_4bits << 2);  // 0x33333333
  int mask_1bit = mask_2bits ^ (mask_2bits << 1); // 0x55555555

  x = ((x & mask_1bit) << 1) | ((x >> 1) & mask_1bit);
  x = ((x & mask_2bits) << 2) | ((x >> 2) & mask_2bits);
  x = ((x & mask_4bits) << 4) | ((x >> 4) & mask_4bits);
  x = ((x & mask_8bits) << 8) | ((x >> 8) & mask_8bits);
  x = (x << 16) | ((x >> 16) & mask_16bits);
  return x;
}
