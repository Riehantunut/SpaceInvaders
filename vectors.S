.macro movi reg, val
	lui \reg, %hi(\val)
	ori \reg, \reg, %lo(\val)
.endm

.macro STUB num
	.align 4
	.section .vector_new_\num,"ax",@progbits
	.global __vector_\num
	__vector_\num:
		movi $k0, _isr_primary_install
		lw $k0, \num * 4($k0)
		jr $k0
.endm

.align 4
.global __use_isr_install
__use_isr_install:
STUB 0
STUB 1
STUB 2
STUB 3
STUB 4
STUB 5
STUB 6
STUB 7

STUB 8
STUB 9
STUB 10
STUB 11
STUB 12
STUB 13
STUB 14
STUB 15

STUB 16
STUB 17
STUB 18
STUB 19
STUB 20
STUB 21
STUB 22
STUB 23

STUB 24
STUB 25
STUB 26
STUB 27
STUB 28
STUB 29
STUB 30
STUB 31

STUB 32
STUB 33
STUB 34
STUB 35
STUB 36
STUB 37
STUB 38
STUB 39

STUB 40
STUB 41
STUB 42
STUB 43
STUB 44
STUB 45
STUB 46
STUB 47

STUB 48
STUB 49
STUB 50
STUB 51
STUB 52
STUB 53
STUB 54
STUB 55

STUB 56
STUB 57
STUB 58
STUB 59
STUB 60
STUB 61
STUB 62
STUB 63


.section .text

.align 4
.global _isr_stub
_isr_stub:
	eret
	nop

.align 4
.global _isr_primary_install
_isr_primary_install:
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub

.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub

.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub

.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub

.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub

.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub

.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub

.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub
.word _isr_stub

# Exceptions are handled here (trap, syscall, etc)
.section .gen_handler,"ax",@progbits
.set noreorder
.ent _gen_exception
_gen_exception:
	mfc0 $k0, $14, 0
	addi $k0, $k0, 4
	mtc0 $k0, $14, 0
	eret

.end _gen_exception
