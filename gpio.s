    ldr r0, =0x20200000   /* load base for GPIO into r0 */
    mov r1, #1            /* load 1 into r1 */
    lsl r1, #18           /* put bit in correct place to mask GPIO 16 */
    str r1, [r0,#4]       /* store value of r1 in GPIO 16's indicator */
    mov r2, #1            /* load 1 into r2 */
    lsl r2, #16            /* mask to clear and set GPIO 16 (set bit 16) */
loop:
   str r2, [r0, #40]      /* clear GPIO 16 */
   b delayCLR
finCLRDelay:
   str r2, [r0, #28]      /* set GPIO 16 */
   b delaySET
finSETDelay:
   b loop
delayCLR:
    mov r4, #1000
delayLoopCLR:
    sub r4, r4, #1
    cmp r4, #0
    bgt delayLoopCLR
    b finCLRDelay
delaySET:
    mov r4, #1
delayLoopSET:
    sub r4, r4, #1
    cmp r4, #0
    bgt delayLoopSET
    b finSETDelay
