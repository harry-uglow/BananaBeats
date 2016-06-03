ldr r0,=0x20200000
mov r1,#1
lsl r1,#21
str r1,[r0,#4]
mov r2,#1
lsl r2,#17

main_loop:
str r2,[r0,#40]

mov r4,#1
lsl r4,#19

clear_delay:
sub r4,r4, #1
cmp r4,#0
bne clear_delay

str r2,[r0,#28]

mov r4,#1
lsl r4,#19

set_delay:
sub r4,r4,#1
cmp r4,#0
bne set_delay

b main_loop
