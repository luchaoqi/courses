## operators

| Level                   |      |      |      |      |
| ----------------------- | ---- | ---- | ---- | ---- |
| bit-level (0/1)         | &    | \|   | ^    | ~    |
| high-level (True/False) | &&   | \|\| |      | !    |

## two's represent of $w$ bit number

$T_{max} = 2^{w-1} - 1$

$T_{min} = -2^{w-1}$

$|T_{max}| = |T_{min}| - 1$

low-level programming language like $C$ would treat all values as unsigned when the expression contains both signed and unsigned int

* int is cast to unsigned

## sign extension and truncation

![](https://i.ibb.co/dKYWgwK/image.png)

$1111\_1111\_0123_2 = 1111\_0123_2$

![](https://i.ibb.co/HTbBLM1/image.png)

## bitwise calculation

Overflow: discard carry

Unsigned:  

$UAdd_w(u,v) = u+v \hspace{5mm} mod \hspace{5mm} 2^w$

$UMult_w(u,v) = u \cdot v \hspace{5mm} mod \hspace{5mm} 2^w$

$u << k = u*2^k$

$u >> k = u//2^k$











