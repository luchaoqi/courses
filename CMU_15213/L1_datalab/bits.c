/* -------------------------------------------------------------------------- */
/*       resources: https://graphics.stanford.edu/~seander/bithacks.html      */
/* -------------------------------------------------------------------------- */

/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 */

/* Instructions to Students:

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  long Funct(long arg1, long arg2, ...) {
      // brief description of how your implementation works
      long var1 = Expr1;
      ...
      long varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. (Long) integer constants 0 through 255 (0xFFL), inclusive. You are
      not allowed to use big constants such as 0xffffffffL.
  3. Function arguments and local variables (no global variables).
  4. Local variables of type int and long
  5. Unary integer operations ! ~
     - Their arguments can have types int or long
     - Note that ! always returns int, even if the argument is long
  6. Binary integer operations & ^ | + << >>
     - Their arguments can have types int or long
  7. Casting from int to long and from long to int

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting other than between int and long.
  7. Use any data type other than int or long.  This implies that you
     cannot use arrays, structs, or unions.

  You may assume that your machine:
  1. Uses 2s complement representations for int and long.
  2. Data type int is 32 bits, long is 64.
  3. Performs right shifts arithmetically.
  4. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31 (int) or 63 (long)

EXAMPLES OF ACCEPTABLE CODING STYLE:
  //
  // pow2plus1 - returns 2^x + 1, where 0 <= x <= 63
  //
  long pow2plus1(long x) {
     // exploit ability of shifts to compute powers of 2
     // Note that the 'L' indicates a long constant
     return (1L << x) + 1L;
  }

  //
  // pow2plus4 - returns 2^x + 4, where 0 <= x <= 63
  //
  long pow2plus4(long x) {
     // exploit ability of shifts to compute powers of 2
     long result = (1L << x);
     result += 4L;
     return result;
  }

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

CAUTION:
  Do not add an #include of <stdio.h> (or any other C library header)
  to this file.  C library headers almost always contain constructs
  that dlc does not understand.  For debugging, you can use printf,
  which is declared for you just below.  It is normally bad practice
  to declare C library functions by hand, but in this case it's less
  trouble than any alternative.

  dlc will consider each call to printf to be a violation of the
  coding style (function calls, after all, are not allowed) so you
  must remove all your debugging printf's again before submitting your
  code or testing it with dlc or the BDD checker.  */

extern int printf(const char *, ...);

/* Edit the functions below.  Good luck!  */
// 2
/*
 * copyLSB - set all bits of result to least significant bit of x
 *   Examples:
 *     copyLSB(5L) = 0xFFFFFFFFFFFFFFFFL,
 *     copyLSB(6L) = 0x0000000000000000L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
long copyLSB(long x) {
    // * sign extension and truncation for 64-bit
    return (x << 63) >> 63;
}
/*
 * dividePower2 - Compute x/(2^n), for 0 <= n <= 62
 *  Round toward zero
 *   Examples: dividePower2(15L,1L) = 7L, dividePower2(-33L,4L) = -2L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
long dividePower2(long x, long n) {
    long is_negative = !!(x >> 63);
    // add bias to x if x is negative
    long bias = (is_negative << n) + (~is_negative) + 1;
    x += bias;
    return x >> n;
}
/*
 * distinctNegation - returns 1 if x != -x.
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 5
 *   Rating: 2
 */
long distinctNegation(long x) {
    // ~x + 1 = -x
    long neg_x = ~x + 1;
    return !!(x ^ neg_x);
}
/*
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   where bits are numbered from 0 (least significant) to 63 (most significant)
 *   Examples anyEvenBit(0xAL) = 0L, anyEvenBit(0xEL) = 1L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 14
 *   Rating: 2
 */
long anyEvenBit(long x) {
    // long mask = 0x5555555555555555L;
    long mask = 0x55;
    mask |= mask << 8;
    mask |= mask << 16;
    mask |= mask << 32;
    // !! normalize variable: converts 0 to 0 and non-zero to 1
    return !!(x & mask);
}
// 3
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4L,5L) = 1L.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
long isLessOrEqual(long x, long y) {
    /*
     two cases to return 1:
        1. different sign: x is negative and y is positive
        2. same sign and difference is larger or equal than 0
        !! -x == (~x) + 1 only works when x is not TMIN
        but MSB doesn't change even when x is TMIN
        y + (~x) + 1 >= 0 should be used carefully because it may overflow
     * when x is TMIN and y is negative, y>=x is always TRUE.
     * And ~x+1 == TMIN, which makes b = 1 & !(MSB of (y + TMIN)) = 1 & 1 = 1.
     */
    long neg_x = ~x + 1;
    int signx = x >> 63;
    int signy = y >> 63;
    int sum_sign = (y + neg_x) >> 63;
    // x is negative and y is positive: (signx & !signy)
    // OR other cases (overflow) & (no overflow)
    return (signx & !signy) | ((!(signx ^ signy)) & !sum_sign);
}

/*
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 7 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
long replaceByte(long x, long n, long c) {
    /*
    x           0001 0010 0011 0100 0101 0110 0111 1000
    shifted_c   0000 0000 0000 0000 1010 1011 0000 0000
    shifted_m   0000 0000 0000 0000 1111 1111 0000 0000
    1 byte is 8 bits, so n << 3 is the number of bits to shift
    */
    long mask = 0xFF;
    long c_shifted = c << (n << 3);
    long mask_shifted = mask << (n << 3);
    return (x & ~mask_shifted) | c_shifted;
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4L,5L) = 4L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
long conditional(long x, long y, long z) {
    // return y if x is 1, otherwise return z
    long condition = !!x;
    long mask = (condition << 63) >> 63; // 0000 or 1111
    return (y & mask) | (z & ~mask);
}
/*
 * bitMask - Generate a mask consisting of all 1's
 *   between lowbit and highbit
 *   Examples: bitMask(5L,3L) = 0x38L
 *   Assume 0 <= lowbit < 64, and 0 <= highbit < 64
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
long bitMask(long highbit, long lowbit) {
    // long mask = 0xFFFFFFFFFFFFFFFFL;
    long mask = ~1L + 1;
    long lowbit_shifted = mask << lowbit;
    long highbit_shifted = mask << highbit << 1;
    // (mask << lowbit) everything right of lowbit is 0
    return (lowbit_shifted ^ highbit_shifted) & (mask << lowbit);
}
// 4
/*
 * isPalindrome - Return 1 if bit pattern in x is equal to its mirror image
 *   Example: isPalindrome(0x6F0F0123c480F0F6L) = 1L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4
 */
long isPalindrome(long x) {
    // !! (only 0x0 - 0xff allowed)
    // transfer to 32 bits
    // int prefix = (x >> 32) & 0xffffffff;
    // int suffix = ((x << 32) >> 32) & 0xffffffff;
    long mask = ~((1L << 63) >> 31);
    long prefix = (x >> 32) & mask;
    long postfix = x & mask;
    /*
    https://graphics.stanford.edu/~seander/bithacks.html#ReverseByteWith32Bits
    to reverse bits, we need to swap the bits iteratively
    e.g. abcd efgh -> hgfe dcba
        1st step: abcd efgh -> badc fehg
        2nd step: badc fehg -> dcba hgfe
        3rd step: dcba hgfe -> hgfe dcba
    */
    // 0x0000ffff 0xffff0000
    long rev_mask = (0xff << 8) | 0xff;
    prefix = ((prefix & rev_mask) << 16) | ((prefix & (~rev_mask)) >> 16);
    // 0x00ff00ff 0xff00ff00
    rev_mask = (0xff << 16) | 0xff;
    prefix = ((prefix & rev_mask) << 8) | ((prefix & (~rev_mask)) >> 8);
    // 0x0f0f0f0f 0xf0f0f0f0
    rev_mask = (0xf << 8) | 0xf;
    rev_mask = (rev_mask << 16) | rev_mask;
    prefix = ((prefix & rev_mask) << 4) | ((prefix & (~rev_mask)) >> 4);
    // 0x33333333
    rev_mask = (0x33 << 8) | 0x33;
    rev_mask = (rev_mask << 16) | rev_mask;
    prefix = ((prefix & rev_mask) << 2) | ((prefix & (~rev_mask)) >> 2);
    // 0x55555555
    rev_mask = (0x55 << 8) | 0x55;
    rev_mask = (rev_mask << 16) | rev_mask;
    prefix = ((prefix & rev_mask) << 1) | ((prefix & (~rev_mask)) >> 1);
    return !(prefix ^ postfix);
}
/*
 * trueFiveEighths - multiplies by 5/8 rounding toward 0,
 *  avoiding errors due to overflow
 *  Examples:
 *    trueFiveEighths(11L) = 6L
 *    trueFiveEighths(-9L) = -5L
 *    trueFiveEighths(0x3000000000000000L) = 0x1E00000000000000L (no
 * overflow) Legal ops: ! ~ & ^ | + << >> Max ops: 20 Rating: 4
 */
long trueFiveEighths(long x) {
    // x * 5/8 = (x * (4 + 1)) / 8
    // = (x * 4 + x) / 8
    // = (x / 2) + (x / 8)
    // to round toward 0, we need to add bias for both
    // two biases may lead to overflow
    long is_negative = x >> 63;
    long e1 = (x & 1L) << 2;
    long e2 = (x & 7L);
    long frac = e1 + e2;
    long carry = frac >> 3;
    long round = (!!(frac & 7)) & is_negative;
    return (x >> 1) + (x >> 3) + carry + round;
}
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3L) = 0L, logicalNeg(0L) = 1L
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
long logicalNeg(long x) {
    // take MSB of x and -x
    int a = x >> 63;
    int b = (~x + 1) >> 63; // MSB doesn't change if x is TMIN
    int c = a | b;          // 0000 or 0001 (c is 0 or 1)
    int d = c + 1;          // 0001 or 0010 (return LSB of d)
    return d & 1;
}
