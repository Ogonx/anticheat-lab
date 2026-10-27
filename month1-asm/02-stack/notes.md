\# Day 2: the stack



call pushes the 8 byte return address, then jumps. ret pops 8 bytes into rip.



rsp (last 3 hex digits, one run):

\- start of main: 9C8

\- on call sum\_of\_squares: 8B0 (main setup: push rbp, push rdi, sub rsp,108h = -280)

\- inside sum\_of\_squares: 8A8 (-8, return address)

\- on call square: 770 (setup = -312)

\- inside square: 768 (-8)

\- square body: 670 (setup = -248)

\- on ret in square: 768 (lea + 2 pops undo the setup)

\- after ret: 770 (+8)



Return address at rsp after call = address of the instruction after the call in main.

square(3) = 9, square(4) = 16 (0x10), both returned in rax.



a and b are saved by mov \[rsp+8],ecx and mov \[rsp+10h],edx into the 16 bytes above the return address (shadow space, to confirm in the video).



Not yet seen: the final ret from sum\_of\_squares back into main.

