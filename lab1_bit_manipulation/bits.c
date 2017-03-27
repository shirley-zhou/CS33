/*
 * CS:APP Data Lab
 *
 *
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function.
     The max operator count is checked by dlc. Note that '=' is not
     counted; you may use as many of these as you want without penalty.
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
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  /*find log2(-x) + 1, then add another 1 because two's complement (as long as nonzero). Implement log with a sort of binary search */
  //if negative, convert to positive first
  int signedmask = (x >> 31); //00...0 or 11...1
  int x_copy = (signedmask & ~x) | (~signedmask & x);
  int nonzero = 0;

  int extract = x_copy;
  int count = 0; //keep count of log2 solution
  int found1 = !!(extract >> 16); //is there a 1 past 16th position? found1 = 0 or 1
  count +=found1 << 4; //add 0 or 16 to counter

  extract= (((~found1 + 1) & (extract >> 16)) + ((~(~found1+1) & extract))); //if 1 was found, ~found1+1 is mask 11...1 => set extracted part = top 16 bits; else extract = original x
  found1 = !!(extract >> 8); 
  count += found1 << 3;

  extract = (((~found1 + 1) & (extract >> 8)) + ((~(~found1+1)&extract)));
  found1 = !!(extract >> 4);
  count += found1 << 2;

  extract = (((~found1 + 1) & (extract >> 4)) + ((~(~found1+1)&extract)));
  found1 = !!(extract >> 2);
  count += found1 << 1;

  extract = (((~found1 + 1) & (extract >> 2)) + ((~(~found1+1)&extract)));
  found1 = !!(extract >> 1);
  count += found1 << 0;

  nonzero = !!(x_copy^0);//if x!=0, requires extra bit
  return count + 1 + nonzero;
}
/*
 * sm2tc - Convert from sign-magnitude to two's complement
 *   where the MSB is the sign bit
 *   Example: sm2tc(0x80000005) = -5.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int sm2tc(int x) {
  /*-x = ~(x)+1, so if signed byte == 1 then negate remaining 31 bits of x*/
  int signedbitmask = x >> 31; //create mask = 11...1 or 00...0
  int mask = 0xFF; //to mask 31 remaining bits of x
  mask |= mask << 8;
  mask |= mask << 15;
  x = x & mask; //31 lower bits of x
  return (~signedbitmask & x) | (signedbitmask & (~(x)+1)); //if signedbitmask == 0, return x; else if 11...1, return -x
}
/*
 * isNonNegative - return 1 if x >= 0, return 0 otherwise
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
  /*capture signed bit*/
  x = x >> 31;
  return !x; //if signedbit == 0, return 1; else return 0
}

/*
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3
 */
int rotateRight(int x, int n) {
  /*get rightmost n bits in its own bit string, add to leftshifted version of x using |*/
  int negn = ~n + 1;
  int neg1 = ~1+1;
  int rightbits = x << (32+negn);
  int shifted = x >> n;
  shifted = shifted & ~(neg1 << (32 + negn)); //mask in case arithmetic shift was used earlier, turns leftmost bits to 0
  return shifted | rightbits;
}
/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  /*right shift is division by 2^n, but add bias=(1<<n)+(-1) if x<0 according to textbook*/
  int signedbit = (x >> 31) & 1; //keep only signed bit = 0 or 1
  int bias = signedbit << n; //if signedbit ==1, bias = 1<<n; else if signedbit == 0, bias = 0 still
  int add = x >> 31; //= 0 or -1 depending on signed bit (arithmetic/logical shift)
  bias += add; //bias = (1<<n)+(-1)
  return (x+bias)>>n;
}
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  /*create 32-bit mask to select odd bits of x, then check equal mask*/
  int mask = 0x55; //0101 0101 (mask even bits initially, to avoid signed overflow on left shift)
  int odd = 0;
  mask |= mask<<8; //0101 0101 0101 0101
  mask |= mask <<16; //32-bit pattern
  mask = ~mask; //switch to a mask on odd bits
  odd = x & mask; //mask all odd bits
  return !(odd ^ mask); //xor for equality check;
}
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  /*XOR means x & ~y OR y & ~x*/
  int a = x & ~y;
  int b = y & ~x;
  int bitOr = ~(~a & ~b); //De Morgan's law
  return bitOr;
}
/*
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) {
  /*use properties of Tmin, since Tmin - 1 = Tmax, and Tmin+Tmax = -1*/
  int neg1 = ~1 + 1;
  int y = x + neg1; //will be 0111...1 if x is Tmin
  int z = x+y; //1111...1
  return (!(~z)) & !!x; //check special case x == 0
}
