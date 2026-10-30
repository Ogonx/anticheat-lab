\# Day 3: local variables and stack frames



SingleLocalVariable:

\- sub rsp,18h reserves 24 bytes. mov dword ptr \[rsp],5CA1AB1Eh stores i at rsp+0. mov eax,\[rsp] copies it into eax for the return. add rsp,18h gives the space back.

\- After ret the value is still in memory but below rsp, so it can be overwritten at any time.



SingleLocalVariable2 (main -> func -> func2 -> func3):

\- call pushes the return address and sets rip to the call target. ret pops it into rip and adds 8 to rsp.

\- Reserved sizes: func3 18h (24), func 28h (40), func2 38h (56), main 28h (40).

\- Each size plus the 8 byte return address is a multiple of 16 (Windows x64 needs rsp 16-byte aligned at every call).

\- func2 is 38h and not 40h because 40h + 8 = 48h (72), which is not a multiple of 16.

\- Frame breakdown: 8 padding + 16 locals + 32 shadow space. func3 = 8+16, func = 8+32, func2 = 8+16+32.

\- Shadow space is 32 bytes the caller reserves for the callee's 4 register arguments (rcx, rdx, r8, r9). To confirm in the Function Parameter Passing video.



Mistakes: wrong direction for call (it lowers rsp), mixed up hex and decimal (48h is 72, not 48), thought ret reads i (it reads the return address).

