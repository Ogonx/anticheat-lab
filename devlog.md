## 2026-10-19 (day 1)
Learned: registers live inside the CPU and memory is RAM. 16 general purpose registers. eax is the low half of rax. On Windows x64, the first two int arguments arrive in ecx and edx and an int result goes back in eax.
Built or broke: read add(int, int) in Compiler Explorer at /Od (9 lines, saves arguments to stack memory and reloads them) and /O2 (1 lea plus ret, all in registers). Typed /02 with a zero first, which made both outputs look identical.
Stuck on: DWORD PTR is a size label, not a pointer. lea does arithmetic without reading memory. ret 0 is a normal return, not a return value of 0. Why the compiler saves arguments to the stack at all.
Tomorrow: stack, call and ret

## Day 2 (20 to 27 Oct)

Done:
- Finished the OST2 hex arithmetic exercise (add and subtract up to 64 bit).
- Wrote stack-demo (square and sum_of_squares) and stepped through it with F11 in the Disassembly window, watching rsp and the Memory window.

What I learned:
- call pushes an 8 byte return address and jumps. ret pops it into rip. rsp goes down 8, then up 8.
- Each function reserves stack with sub rsp,N and undoes it before ret, so rsp points at the return address right before ret.
- The return address on the stack was the address of the next instruction after the call in the caller.
- At /Od, a and b are saved into the 16 bytes above the return address. I think this is shadow space, to confirm in the Function Parameter Passing video.
- Return values come back in rax: square(3) gave 9, square(4) gave 16.

Where I got stuck:
- Memory window was pointed at a random address and showed ??. Fix: type rsp in the address box.
- Was stepping in the .cpp tab, which steps by line. Disassembly steps by instruction.
- Restarting the program changes all the addresses, so only compare differences.
- Forgot carries and borrows in the hex exercise a lot.

## Day 3 (30 Oct)

Done:
- Watched Calling Functions and Local Variables.
- Stepped through SingleLocalVariable and SingleLocalVariable2 in the debugger on my own PC (retargeted the course projects to the newer toolset).
- Filled in a step table and a stack diagram for the nested calls, and worked out why func2 reserves 38h and not 40h.

What I learned:
- Locals live in space reserved with sub rsp,N. mov [rsp],value stores a local, mov eax,[rsp] reads it back, add rsp,N gives the space back. After ret the old value is still in memory but below rsp.
- call sets rip to the target and pushes the return address. ret pops it into rip and adds 8 to rsp.
- Reserved sizes: func3 18h, func 28h, func2 38h, main 28h. Each one plus the 8 byte return address is a multiple of 16, because Windows x64 needs rsp 16-byte aligned at every call.
- 40h would give 48h, which is not a multiple of 16.
- A frame is padding (8) plus locals (16) plus shadow space (32), but only the parts a function needs. func2 needs all three, so 8+16+32 = 56 = 38h.
- Shadow space is 32 bytes the caller reserves for the callee's 4 register arguments. To confirm in the Function Parameter Passing video.

Where I got stuck:
- Got the direction of call wrong twice (it lowers rsp).
- Mixed up hex and decimal (48h is 72, not 48).
- Thought ret read the local variable. It reads the return address.
- The first build failed because the course projects used the VS 2019 toolset. Fix: retarget to the latest toolset.

Next: DoubleLocalVariable.