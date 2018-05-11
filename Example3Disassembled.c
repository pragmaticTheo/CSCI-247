0x0000000000400546 <+0>:	push   %rbp - Save old base pointer.
0x0000000000400547 <+1>:	mov    %rsp,%rbp - Move stack pointer into base pointer.
=> 0x000000000040054a <+4>:	sub    $0x40,%rsp - shift stack pointer downwards by 64 bytes.
0x000000000040054e <+8>:	mov    %fs:0x28,%rax
0x0000000000400557 <+17>:	mov    %rax,-0x8(%rbp) - move "magic number" into position.
0x000000000040055b <+21>:	xor    %eax,%eax - clear %eax register.
0x000000000040055d <+23>:	movl   $0x17,-0x30(%rbp) - a = 23
0x0000000000400564 <+30>:	movl   $0x13,-0x2c(%rbp) - b = 19

0x000000000040056b <+37>:	movl   $0xc,-0x28(%rbp) - Start Array. Array[0] = 12
0x0000000000400572 <+44>:	movl   $0x2,-0x20(%rbp) - End Array. Array[1] = 2

0x0000000000400579 <+51>:	movl   $0x3,-0x1c(%rbp) - c = 3
0x0000000000400580 <+58>:	movl   $0x1,-0x18(%rbp) - d = 1
0x0000000000400587 <+65>:	movl   $0x0,-0x34(%rbp) - e = 0

0x000000000040058e <+72>:	mov    -0x30(%rbp),%edx - Store 23 in %edx.
0x0000000000400591 <+75>:	mov    -0x20(%rbp),%eax - Store 2 in %eax.
0x0000000000400594 <+78>:	imul   %edx,%eax - Store 23 * 2 in %eax.
0x0000000000400597 <+81>:	add    %eax,-0x34(%rbp) - Store 46 in e.

0x000000000040059a <+84>:	mov    -0x2c(%rbp),%edx - Store 19 in %edx.
0x000000000040059d <+87>:	mov    -0x1c(%rbp),%eax - Store 3 in %eax.
0x00000000004005a0 <+90>:	imul   %edx,%eax - Store 19 * 3 in %eax.
0x00000000004005a3 <+93>:	add    %eax,-0x34(%rbp) - Store 57 + 46 in e.

0x00000000004005a6 <+96>:	mov    -0x28(%rbp),%edx - Store 12 in %edx.
0x00000000004005a9 <+99>:	mov    -0x18(%rbp),%eax - Store 1 in %eax.
0x00000000004005ac <+102>:	imul   %edx,%eax - Store 12 * 1 in %eax.
0x00000000004005af <+105>:	add    %eax,-0x34(%rbp) - Store 12 + 103 in e.

0x00000000004005b2 <+108>:	mov    $0x0,%eax - Store 0 in %eax (effectively clearing it)
0x00000000004005b7 <+113>:	mov    -0x8(%rbp),%rcx - Retrieve the "magic number"
0x00000000004005bb <+117>:	xor    %fs:0x28,%rcx - See if it's been tampered with.
0x00000000004005c4 <+126>:	je     0x4005cb <main+133> - Well, has it been tampered with?
0x00000000004005c6 <+128>:	callq  0x400420 <__stack_chk_fail@plt> - If so, stack overflow, baybee.
0x00000000004005cb <+133>:	leaveq - Abbreviation for copying %rbp back to %rsp, and then restoring old value of %rbp from the stack.
0x00000000004005cc <+134>:	retq - return from main.
