	.file	1 "./z/benchmarks/unroll_1x.c"

 # GNU C 2.7.2.3 [AL 1.1, MM 40, tma 0.1] SimpleScalar running sstrix compiled by GNU C

 # Cc1 defaults:
 # -mgas -mgpOPT

 # Cc1 arguments (-G value = 8, Cpu = default, ISA = 1):
 # -quiet -dumpbase -O2 -fverbose-asm -o

gcc2_compiled.:
__gnu_compiled_c:
	.rdata
	.align	2
$LC0:
	.ascii	"Result 1x: %d\n\000"
	.text
	.align	2
	.globl	main

	.comm	A,400000

	.comm	B,400000

	.comm	C,400000

	.extern	stdin, 4
	.extern	stdout, 4

	.text

	.loc	1 7
	.ent	main
main:
	.frame	$sp,24,$31		# vars= 0, regs= 1/0, args= 16, extra= 0
	.mask	0x80000000,-8
	.fmask	0x00000000,0
	subu	$sp,$sp,24
	sw	$31,16($sp)
	jal	__main
	move	$4,$0
	li	$6,0x00010000		# 65536
	ori	$6,$6,0x869f
	la	$5,B
	la	$3,A
$L17:
	sll	$2,$4,1
	sw	$4,0($3)
	sw	$2,0($5)
	addu	$5,$5,4
	addu	$3,$3,4
	addu	$4,$4,1
	slt	$2,$6,$4
	beq	$2,$0,$L17
	move	$4,$0
	li	$8,0x00010000		# 65536
	ori	$8,$8,0x869f
	la	$7,C
	la	$6,B
	la	$5,A
$L22:
	.set	noreorder
	lw	$2,0($5)
	.set	reorder
	.set	noreorder
	lw	$3,0($6)
	.set	reorder
	addu	$4,$4,1
	addu	$2,$2,$3
	sw	$2,0($7)
	addu	$7,$7,4
	addu	$6,$6,4
	addu	$5,$5,4
	slt	$2,$8,$4
	beq	$2,$0,$L22
	.set	noreorder
	lw	$5,C+399996
	.set	reorder
	la	$4,$LC0
	jal	printf
	move	$2,$0
	lw	$31,16($sp)
	addu	$sp,$sp,24
	j	$31
	.end	main
