.section .init, "ax"
.global _start
_start:
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
jal zero, timerInt
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
jal zero, buttonInt
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
add x0, x0, x0
.cfi_startproc
.cfi_undefined ra
.option push
.option norelax
la gp, __global_pointer$
.option pop
la sp, __stack_top
add s0, sp, zero
jal zero, main
.cfi_endproc
.end