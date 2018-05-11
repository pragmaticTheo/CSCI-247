0x00000000004004d6 <+0>:	push   %rbp
0x00000000004004d7 <+1>:	mov    %rsp,%rbp
=> 0x00000000004004da <+4>:	movl   $0x13,-0x10(%rbp)
0x00000000004004e1 <+11>:	movl   $0x22,-0xc(%rbp)
0x00000000004004e8 <+18>:	movl   $0xc,-0x8(%rbp)

0x00000000004004ef <+25>:	mov    -0x10(%rbp),%edx - Move x (19) into %edx.
Calculate 2x + x and store in %edx.
0x00000000004004f2 <+28>:	mov    %edx,%eax - Move 19 into %eax.
0x00000000004004f4 <+30>:	add    %eax,%eax - Double value in % eax.
0x00000000004004f6 <+32>:	add    %eax,%edx - Add 2x to x, store in %edx.

Calculate 4y + 3x and store in %edx.
0x00000000004004f8 <+34>:	mov    -0xc(%rbp),%eax - Write y (34) into %eax.
0x00000000004004fb <+37>:	shl    $0x2,%eax - Quadruple the value in %eax.
0x00000000004004fe <+40>:	add    %eax,%edx - add Add 4y to 3x.

Calculate 2 z
0x0000000000400500 <+42>:	mov    -0x8(%rbp),%eax - Move value of z into %eax.
0x0000000000400503 <+45>:	add    %eax,%eax - Double value in %eax.

Make new int a and assign value of 3x + 2z.
0x0000000000400505 <+47>:	add    %edx,%eax - Add (4y + 3x) to 2z
0x0000000000400507 <+49>:	mov    %eax,-0x4(%rbp) - a = 4y + 3x + 2z.
0x000000000040050a <+52>:	mov    -0x4(%rbp),%eax store value of a in register to return.
0x000000000040050d <+55>:	pop    %rbp
0x000000000040050e <+56>:	retq
