	.file	1 "./z/benchmarks/unroll_8x.c"

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
	.ascii	"Result 8x: %d\n\000"
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
	.frame	$sp,48,$31		# vars= 0, regs= 8/0, args= 16, extra= 0
	.mask	0x807f0000,-4
	.fmask	0x00000000,0
	subu	$sp,$sp,48
	sw	$31,44($sp)
	sw	$22,40($sp)
	sw	$21,36($sp)
	sw	$20,32($sp)
	sw	$19,28($sp)
	sw	$18,24($sp)
	sw	$17,20($sp)
	sw	$16,16($sp)
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
	addu	$22,$10,28
	la	$8,B
	addu	$21,$8,28
	la	$9,A
	addu	$20,$9,28
	addu	$19,$10,12
	addu	$18,$9,12
	addu	$17,$10,8
	addu	$16,$8,8
	addu	$25,$9,8
	addu	$24,$10,4
	addu	$15,$8,4
	addu	$14,$9,4
	move	$13,$10
	move	$12,$8
	move	$11,$9
$L22:
	sll	$5,$7,2
	addu	$7,$7,8
	.set	noreorder
	lw	$2,0($11)
	.set	reorder
	.set	noreorder
	lw	$3,0($12)
	.set	reorder
	li	$6,0x00010000		# 65536
	ori	$6,$6,0x869f
	addu	$4,$8,$5
	slt	$6,$6,$7
	addu	$2,$2,$3
	sw	$2,0($13)
	addu	$13,$13,32
	.set	noreorder
	lw	$2,0($14)
	.set	reorder
	.set	noreorder
	lw	$3,0($15)
	.set	reorder
	addu	$12,$12,32
	addu	$11,$11,32
	addu	$2,$2,$3
	sw	$2,0($24)
	addu	$24,$24,32
	.set	noreorder
	lw	$2,0($25)
	.set	reorder
	.set	noreorder
	lw	$3,0($16)
	.set	reorder
	addu	$15,$15,32
	addu	$14,$14,32
	addu	$2,$2,$3
	addu	$3,$8,$5
	sw	$2,0($17)
	.set	noreorder
	lw	$2,0($18)
	.set	reorder
	.set	noreorder
	lw	$3,12($3)
	.set	reorder
	addu	$17,$17,32
	addu	$16,$16,32
	addu	$2,$2,$3
	sw	$2,0($19)
	addu	$2,$9,$5
	.set	noreorder
	lw	$3,16($2)
	.set	reorder
	addu	$25,$25,32
	.set	noreorder
	lw	$4,16($4)
	.set	reorder
	addu	$2,$10,16
	addu	$2,$5,$2
	addu	$3,$3,$4
	sw	$3,0($2)
	addu	$2,$9,$5
	.set	noreorder
	lw	$3,20($2)
	.set	reorder
	addu	$4,$8,$5
	.set	noreorder
	lw	$4,20($4)
	.set	reorder
	addu	$2,$10,20
	addu	$2,$5,$2
	addu	$3,$3,$4
	sw	$3,0($2)
	addu	$2,$9,$5
	.set	noreorder
	lw	$3,24($2)
	.set	reorder
	addu	$4,$8,$5
	.set	noreorder
	lw	$4,24($4)
	.set	reorder
	addu	$2,$10,24
	addu	$5,$5,$2
	addu	$3,$3,$4
	sw	$3,0($5)
	.set	noreorder
	lw	$2,0($20)
	.set	reorder
	.set	noreorder
	lw	$3,0($21)
	.set	reorder
	addu	$19,$19,32
	addu	$18,$18,32
	addu	$2,$2,$3
	sw	$2,0($22)
	addu	$22,$22,32
	addu	$21,$21,32
	addu	$20,$20,32
	beq	$6,$0,$L22
	.set	noreorder
	lw	$5,C+399996
	.set	reorder
	la	$4,$LC0
	jal	printf
	move	$2,$0
	lw	$31,44($sp)
	lw	$22,40($sp)
	lw	$21,36($sp)
	lw	$20,32($sp)
	lw	$19,28($sp)
	lw	$18,24($sp)
	lw	$17,20($sp)
	lw	$16,16($sp)
	addu	$sp,$sp,48
	j	$31
	.end	main
