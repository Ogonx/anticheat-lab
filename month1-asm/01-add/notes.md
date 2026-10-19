\# 01-add



Source:



main.cpp

int add(int a, int b)

{

&#x20;   return a + b;

}



On Windows x64, `a` arrives in `ecx` and `b` in `edx`. An `int` result goes back in `eax`.



\## /Od (no optimisation)



```asm

int add(int,int) PROC          ; function start (a label for the assembler, not an instruction)

mov DWORD PTR \[rsp+16], edx    ; store b (2nd argument, in edx) into stack memory at rsp+16

mov DWORD PTR \[rsp+8], ecx     ; store a (1st argument, in ecx) into stack memory at rsp+8

mov eax, DWORD PTR b$\[rsp]     ; load b back from rsp+16 into eax (b$ is the compiler's name for offset 16)

mov ecx, DWORD PTR a$\[rsp]     ; load a back from rsp+8 into ecx (a$ is the name for offset 8)

add ecx, eax                   ; ecx = ecx + eax, so ecx = a + b

mov eax, ecx                   ; copy the sum into eax, where the caller expects an int result

ret 0                          ; return to the caller (main), result is in eax

int add(int,int) ENDP          ; function end (also not an instruction)

```



At /Od every variable lives in memory. The compiler saves each argument to the stack and loads it straight back before using it.



\## /O2 (optimised)



```asm

int add(int,int) PROC                 ; function start

lea eax, DWORD PTR \[rcx+rdx]          ; eax = rcx + rdx (a + b). lea does the arithmetic without reading memory, and writes the sum to a third register

ret 0                                 ; return to the caller, result already in eax

int add(int,int) ENDP                 ; function end

```



At /O2 the arguments are used straight from the registers they arrive in, so memory is never touched.



\## Differences



1./0d uses 6 instructions plus ret; four mov's, an add, and a final mov but /O2	uses 1 instruction plus ret: a single lea.

2.the unoptimized version does a lot of busywork. it saves both arguments to memory, loads them back, adds them, and copies the sum into the result register. the optimised version just adds the two registers directly and writes the result in eax.

3\. /0d uses rsp but /O2 doesn't.

4\. /Od saves a and b from ecx and edx to the stack and loads them back before adding. /O2 reads them directly from rcx and rdx.

5\. /0d needs move eax, ecx to get the sum but /O2 doesn't as it just gets it from lea eax, DWORD PTR \[rcx+rdx]



\## What confused me



\- Why does the compiler save arguments to \[rsp+8] and \[rsp+16] at all?

