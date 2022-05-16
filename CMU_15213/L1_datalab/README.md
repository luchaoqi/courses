resources:
https://graphics.stanford.edu/~seander/bithacks.html
https://eclipse.umbc.edu/robucci/cmpeRSD/Lectures/Lecture16__Signed_Integers_and_Arithmetic/

```c
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
```
```c
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
```
```c
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
```
```c
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
```
```c
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
        -x == (~x) + 1 only works when x is not TMIN
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
```
```c
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
```
```c
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
```
```c
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
```
```c
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
```
```c
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
```
```c
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
```
