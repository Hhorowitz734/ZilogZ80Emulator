
// I am trying to emulate the Zilog Z80 chip, which is the processor of the TI-84
// I like the TI 84 because it's the calculator I started programming on, and I used to do a lot of Z80 assembly
#include <iostream>
#include <stdlib.h>


struct CPU {
    using Byte = unsigned char;
    using Word = unsigned short;

    // SPECIAL PURPOSE REGISTERS
    Word PC; // Program counter
    Word SP; // Stack pointer   
    Word IX; // Index register
    Word IY; // Index register
    Byte I; // Interrupt vector
    Byte R; // Memory refresh

    // MAIN REGISTER SET
    Byte A, F; // Accumulator and flags register 
    Byte B, C; // BC pair
    Byte D, E; // DE pair
    Byte H, L; // HL pair
    
    // ALTERNATE REGISTER SET
    Byte A_, F_;
    Byte B_, C_;
    Byte D_, E_;
    Byte H_, L_;

    // STATUS FLAGS
    Byte C_F : 1; // Carry Flag
    Byte N_F : 1; // Add/Subtract
    Byte P_V_F : 1; // Parity/Overflow Flag
    Byte H_F : 1; // Half Carry Flag
    Byte Z_F : 1; // Zero Flag
    Byte S_F : 1; // Sign Flag
    Byte X_F : 1; // Not Used

};

int main() {

    CPU cpu;

    std::cout << "Hello, world!";
    
    return 0;
}
