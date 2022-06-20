### Resources

[CS107 Guide to x86-64](https://web.stanford.edu/class/archive/cs/cs107/cs107.1222/guide/x86-64.html)

[CS107 GDB and Debugging](https://web.stanford.edu/class/archive/cs/cs107/cs107.1222/resources/gdb.html)

[Nagle张木匠的个人空间_哔哩哔哩_bilibili](https://space.bilibili.com/250682464)

[Mark Higgins – Medium](https://mybagoftricks.medium.com/)

Q & A:

* [c - Display value found at given address gdb - Stack Overflow](https://stackoverflow.com/questions/14493707/display-value-found-at-given-address-gdb)

* [c++ - What's the difference between nexti and stepi in gdb? - Stack Overflow](https://stackoverflow.com/questions/52024529/whats-the-difference-between-nexti-and-stepi-in-gdb#:~:text=If%20you%20are%20on%20a,the%20instruction%20after%20the%20call)

* [x86 Assembly/GNU assembly syntax - Wikibooks, open books for an open world](https://en.wikibooks.org/wiki/X86_Assembly/GNU_assembly_syntax)

* [bit manipulation - The difference between logical shift right, arithmetic shift right, and rotate right - Stack Overflow](https://stackoverflow.com/questions/44694957/the-difference-between-logical-shift-right-arithmetic-shift-right-and-rotate-r#:~:text=Logical%20right%20shift%20means%20shifting,as%20in%20the%20original%20number)


### Phase 1

Similar to activity 3 in [recitation03-bomblab](https://www.cs.cmu.edu/afs/cs/academic/class/15213-s19/www/recitations/recitation03-bomblab.pdf)

```
break phase_1
disas
```

```
Dump of assembler code for function phase_1:
=> 0x0000000000400ee0 <+0>:     sub    $0x8,%rsp
   0x0000000000400ee4 <+4>:     mov    $0x402400,%esi
   0x0000000000400ee9 <+9>:     callq  0x401338 <strings_not_equal>
   0x0000000000400eee <+14>:    test   %eax,%eax
   0x0000000000400ef0 <+16>:    je     0x400ef7 <phase_1+23>
   0x0000000000400ef2 <+18>:    callq  0x40143a <explode_bomb>
   0x0000000000400ef7 <+23>:    add    $0x8,%rsp
   0x0000000000400efb <+27>:    retq
End of assembler dump.
```
After disassembling, we can see that for `callq strings_not_equal`, it is using `%esi` as its argument.
```
(gdb) x/s 0x402400
0x402400:       "Border relations with Canada have never been better."
```

### Phase 2

It starts from <phase_2+18> and loops between <phase_2+27> and <phase_2+52>. The key is `<+14>:    cmpl   $0x1,(%rsp)` and `<+30>:    add    %eax,%eax`.

### Phase 3

```
   0x0000000000400f51 <+14>:    mov    $0x4025cf,%esi
(gdb) x/s 0x4025cf
0x4025cf:       "%d %d"
```
The input format is two decimal numbers separated by a space.
```
<+9>:     lea    0x8(%rsp),%rdx`
<+39>:    cmpl   $0x7,0x8(%rsp)
<+44>:    ja     0x400fad <phase_3+106>
```
4 bytes of the first number is compared to 0x7, `pay attention to operand order for cmp`, which is different in linux and windows.
```
(gdb) x/2wd $rsp+0x8
0x7fffffffe548: 7     321
```
> exam test inputs: 7 321
```
<+50>:    jmpq   *0x402470(,%rax,8)
```
```
(gdb) x 0x402470 + 32
0x402490:       0x00400f91
```
go to dereferenced content in address `0x00400f91`
```
   0x0000000000400f91 <+78>:    mov    $0x185,%eax
   0x0000000000400f96 <+83>:    jmp    0x400fbe <phase_3+123>
```
```
   0x0000000000400fbe <+123>:   cmp    0xc(%rsp),%eax
   0x0000000000400fc2 <+127>:   je     0x400fc9 <phase_3+134>

(gdb) p $rsp
$72 = (void *) 0x7fffffffe540
(gdb) x/d 0x7fffffffe540+0xc
0x7fffffffe54c: 123
(gdb) p/d 0x185
$73 = 389
```

### Phase 4

Look over phase_4 function and we can find:

```
   0x000000000040101a <+14>:    mov    $0x4025cf,%esi
(gdb) x/s 0x4025cf
0x4025cf:       "%d %d"
   0x0000000000401051 <+69>:    cmpl   $0x0,0xc(%rsp)
   0x0000000000401056 <+74>:    je     0x40105d <phase_4+81>
   0x0000000000401058 <+76>:    callq  0x40143a <explode_bomb>
(gdb) x/wd $rsp+0x8
0x7fffffffe548: 10
(gdb) x/wd $rsp+0xc
0x7fffffffe54c: 123
```
second number should be `0`, here I tested with `10 123`.

```
   0x000000000040102e <+34>:    cmpl   $0xe,0x8(%rsp)
   0x0000000000401033 <+39>:    jbe    0x40103a <phase_4+46>
(gdb) x/d $rsp+0x8
0x7fffffffe548: 14
```
first number should be less than or equal to `0xe=14`

```
   0x0000000000401048 <+60>:    callq  0x400fce <func4>
   0x000000000040104d <+65>:    test   %eax,%eax
   0x000000000040104f <+67>:    jne    0x401058 <phase_4+76>
   0x0000000000401051 <+69>:    cmpl   $0x0,0xc(%rsp)
   0x0000000000401056 <+74>:    je     0x40105d <phase_4+81>
   0x0000000000401058 <+76>:    callq  0x40143a <explode_bomb>
```
func4 is called and the result is compared to 0x0, if it is not 0x0, it will call `explode_bomb`. Then we disassemble func4

```
   0x0000000000400fe2 <+20>:    cmp    %edi,%ecx
   0x0000000000400fe4 <+22>:    jle    0x400ff2 <func4+36>
   0x0000000000400ff2 <+36>:    mov    $0x0,%eax
   0x0000000000400ff7 <+41>:    cmp    %edi,%ecx
   0x0000000000400ff9 <+43>:    jge    0x401007 <func4+57>
```
to let func4 return 0x0, the code at <+36>, we can find that the input x must be `7 <= x <= 7`. So the first argument is 7.

### Phase 5

[CMU Bomb Lab with Radare2 — Phase 5 | by Mark Higgins | Medium](https://mybagoftricks.medium.com/cmu-bomb-lab-with-radare2-phase-5-939497fc896c)

I recommend using [Radare2](https://radare.org/) from now on.
