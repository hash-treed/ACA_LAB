	.file	1 "./z/benchmarks/unroll_16x.c"

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
	.ascii	"Result 16x: %d\n\000"
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
	move	$7,$0
	li	$5,0x00010000		# 65536
	ori	$5,$5,0x869f
	la	$4,B
	la	$3,A
$L17:
	sll	$2,$7,1
	sw	$7,0($3)
	sw	$2,0($4)
	addu	$4,$4,4
	addu	$3,$3,4
	addu	$7,$7,1
	slt	$2,$5,$7
	beq	$2,$0,$L17
	move	$7,$0
	la	$10,C
	addu	$24,$10,60
	la	$9,B
	addu	$15,$9,60
	la	$8,A
	addu	$14,$8,60
	move	$13,$10
	move	$12,$9
	move	$11,$8
$L22:
	sll	$4,$7,2
	addu	$7,$7,16
	.set	noreorder
	lw	$2,0($11)
	.set	reorder
	.set	noreorder
	lw	$3,0($12)
	.set	reorder
	li	$6,0x00010000		# 65536
	ori	$6,$6,0x869f
	addu	$5,$9,$4
	slt	$6,$6,$7
	addu	$2,$2,$3
	sw	$2,0($13)
	addu	$2,$8,$4
	.set	noreorder
	lw	$3,4($2)
	.set	reorder
	addu	$13,$13,64
	.set	noreorder
	lw	$5,4($5)
	.set	reorder
	addu	$2,$10,4
	addu	$2,$4,$2
	addu	$3,$3,$5
	sw	$3,0($2)
	addu	$2,$8,$4
	.set	noreorder
	lw	$3,8($2)
	.set	reorder
	addu	$5,$9,$4
	.set	noreorder
	lw	$5,8($5)
	.set	reorder
	addu	$2,$10,8
	addu	$2,$4,$2
	addu	$3,$3,$5
	sw	$3,0($2)
	addu	$2,$8,$4
	.set	noreorder
	lw	$3,12($2)
	.set	reorder
	addu	$5,$9,$4
	.set	noreorder
	lw	$5,12($5)
	.set	reorder
	addu	$2,$10,12
	addu	$2,$4,$2
	addu	$3,$3,$5
	sw	$3,0($2)
	addu	$2,$8,$4
	.set	noreorder
	lw	$3,16($2)
	.set	reorder
	addu	$5,$9,$4
	.set	noreorder
	lw	$5,16($5)
	.set	reorder
	addu	$2,$10,16
	addu	$2,$4,$2
	addu	$3,$3,$5
	sw	$3,0($2)
	addu	$2,$8,$4
	.set	noreorder
	lw	$3,20($2)
	.set	reorder
	addu	$5,$9,$4
	.set	noreorder
	lw	$5,20($5)
	.set	reorder
	addu	$2,$10,20
	addu	$2,$4,$2
	addu	$3,$3,$5
	sw	$3,0($2)
	addu	$2,$8,$4
	.set	noreorder
	lw	$3,24($2)
	.set	reorder
	addu	$5,$9,$4
	.set	noreorder
	lw	$5,24($5)
	.set	reorder
	addu	$2,$10,24
	addu	$2,$4,$2
	addu	$3,$3,$5
	sw	$3,0($2)
	addu	$2,$8,$4
	.set	noreorder
	lw	$3,28($2)
	.set	reorder
	addu	$5,$9,$4
	.set	noreorder
	lw	$5,28($5)
	.set	reorder
	addu	$2,$10,28
	addu	$2,$4,$2
	addu	$3,$3,$5
	sw	$3,0($2)
	addu	$2,$8,$4
	.set	noreorder
	lw	$3,32($2)
	.set	reorder
	addu	$5,$9,$4
	.set	noreorder
	lw	$5,32($5)
	.set	reorder
	addu	$2,$10,32
	addu	$2,$4,$2
	addu	$3,$3,$5
	sw	$3,0($2)
	addu	$2,$8,$4
	.set	noreorder
	lw	$3,36($2)
	.set	reorder
	addu	$5,$9,$4
	.set	noreorder
	lw	$5,36($5)
	.set	reorder
	addu	$2,$10,36
	addu	$2,$4,$2
	addu	$3,$3,$5
	sw	$3,0($2)
	addu	$2,$8,$4
	.set	noreorder
	lw	$3,40($2)
	.set	reorder
	addu	$5,$9,$4
	.set	noreorder
	lw	$5,40($5)
	.set	reorder
	addu	$2,$10,40
	addu	$2,$4,$2
	addu	$3,$3,$5
	sw	$3,0($2)
	addu	$2,$8,$4
	.set	noreorder
	lw	$3,44($2)
	.set	reorder
	addu	$5,$9,$4
	.set	noreorder
	lw	$5,44($5)
	.set	reorder
	addu	$2,$10,44
	addu	$2,$4,$2
	addu	$3,$3,$5
	sw	$3,0($2)
	addu	$2,$8,$4
	.set	noreorder
	lw	$3,48($2)
	.set	reorder
	addu	$5,$9,$4
	.set	noreorder
	lw	$5,48($5)
	.set	reorder
	addu	$2,$10,48
	addu	$2,$4,$2
	addu	$3,$3,$5
	sw	$3,0($2)
	addu	$2,$8,$4
	.set	noreorder
	lw	$3,52($2)
	.set	reorder
	addu	$5,$9,$4
	.set	noreorder
	lw	$5,52($5)
	.set	reorder
	addu	$2,$10,52
	addu	$2,$4,$2
	addu	$3,$3,$5
	sw	$3,0($2)
	addu	$2,$8,$4
	.set	noreorder
	lw	$3,56($2)
	.set	reorder
	addu	$5,$9,$4
	.set	noreorder
	lw	$5,56($5)
	.set	reorder
	addu	$2,$10,56
	addu	$4,$4,$2
	addu	$3,$3,$5
	sw	$3,0($4)
	.set	noreorder
	lw	$2,0($14)
	.set	reorder
	.set	noreorder
	lw	$3,0($15)
	.set	reorder
	addu	$12,$12,64
	addu	$11,$11,64
	addu	$2,$2,$3
	sw	$2,0($24)
	addu	$24,$24,64
	addu	$15,$15,64
	addu	$14,$14,64
	beq	$6,$0,$L22
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
