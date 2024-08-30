
// I am trying to emulate the Zilog Z80 chip, which is the processor of the TI-84
// I like the TI 84 because it's the calculator I started programming on, and I used to do a lot of Z80 assembly
#include <iostream>
#include <stdlib.h>

#include "../include/internals.h"



int main() {

    CPU cpu;
    Mem mem;

    cpu.Reset(mem);
    
    return 0;
}
