.section .init 
.globl _start 
_start:
    ldr r0, =0x20200000   /* load base for GPIO into r0 */
    mov r1, #1            /* load 1 into r1 */
    lsl r1, #21           /* put bit in correct place to mask pin 7 */
    str r1, [r0]          /* store value of r1 in memory to activate pin 7 */
    mov r2, #1            /* load 1 into r2 */
    lsl r2, #7            /* create mask to clear and set pin 7 */

Loop:
   str r2, [r0, #40]      /* clear pin 7 */
   b DelayCLR
FinCLRDelay:

   str r2, [r0, #28]      /* set pin 7 */
   b DelaySET
FinSETDelay:

   b Loop



DelayCLR:
    mov r4, 1000
DelayLoopCLR:
    sub r4, #1
    cmp r4, 0
    bgt DelayLoopCLR
    b FinCLRDelay
    
DelaySET:
    mov r4, 1000
DelayLoopSET:
    sub r4, #1
    cmp r4, 0
    bgt DelayLoopSET
    b FinSETDelay
