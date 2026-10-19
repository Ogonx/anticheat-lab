## 2026-10-19 (day 1)
Learned: registers live inside the CPU and memory is RAM. 16 general purpose registers. eax is the low half of rax. On Windows x64, the first two int arguments arrive in ecx and edx and an int result goes back in eax.
Built or broke: read add(int, int) in Compiler Explorer at /Od (9 lines, saves arguments to stack memory and reloads them) and /O2 (1 lea plus ret, all in registers). Typed /02 with a zero first, which made both outputs look identical.
Stuck on: DWORD PTR is a size label, not a pointer. lea does arithmetic without reading memory. ret 0 is a normal return, not a return value of 0. Why the compiler saves arguments to the stack at all.
Tomorrow: stack, call and ret