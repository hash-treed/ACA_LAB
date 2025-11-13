	.file	1 "./z/benchmarks/unroll_2x.c"

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
	.ascii	"Result 2x: %d\n\000"
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
	move	$5,$0
	li	$6,0x00010000		# 65536
	ori	$6,$6,0x869f
	la	$4,B
	la	$3,A
$L17:
	sll	$2,$5,1
	sw	$5,0($3)
	sw	$2,0($4)
	addu	$4,$4,4
	addu	$3,$3,4
	addu	$5,$5,1
	slt	$2,$6,$5
	beq	$2,$0,$L17
	move	$5,$0
	li	$11,0x00010000		# 65536
	ori	$11,$11,0x869f
	la	$4,C
	addu	$10,$4,4
	la	$3,B
	addu	$9,$3,4
	la	$2,A
	addu	$8,$2,4
	move	$7,$3
	move	$6,$2
$L22:
	.set	noreorder
	lw	$2,0($6)
	.set	reorder
	.set	noreorder
	lw	$3,0($7)
	.set	reorder
	addu	$5,$5,2
	addu	$2,$2,$3
	sw	$2,0($4)
	addu	$4,$4,8
	.set	noreorder
	lw	$2,0($8)
	.set	reorder
	.set	noreorder
	lw	$3,0($9)
	.set	reorder
	addu	$7,$7,8
	addu	$6,$6,8
	addu	$2,$2,$3
	sw	$2,0($10)
	addu	$10,$10,8
	addu	$9,$9,8
	addu	$8,$8,8
	slt	$2,$11,$5
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
