ldr r0,=0x20200000
mov r1,#1
lsl r1,#18
str r1,[r0,#4]
mov r2,#1
lsl r2,#16
loop:
str r2,[r0,#40]
mov r4,#0xF00000
wait1:
sub r4,r4, #1
cmp r4,#0
bne wait1
str r2,[r0,#28]
mov r4,#0xF00000
wait2:
sub r4,r4,#1
cmp r4,#0
bne wait2
b loop
