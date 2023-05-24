.section .text.start
.align 4
.arm

.global _start
_start:
    ldr sp, =20018000
    b main 
