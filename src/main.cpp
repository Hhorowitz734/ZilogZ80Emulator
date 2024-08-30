
// I am trying to emulate the Zilog Z80 chip, which is the processor of the TI-84
// I like the TI 84 because it's the calculator I started programming on, and I used to do a lot of Z80 assembly
#include <iostream>
#include <stdlib.h>

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

struct Mem {

    // Sets up 64KG of memory
    static constexpr u32 MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM];

    Mem() {
        // Zero out the memory
        std::fill_n(Data, MAX_MEM, 0x00);
    }

    Byte read(Word address) const {

        // Check that word is within valid range (0x0000 - 0xFFFF)
        if (address < MAX_MEM) {
            return Data[address];
        } else { 
            std::cerr << "Memory read out of bounds at address: [" << std::hex << address << "]" << std::endl;
            exit(EXIT_FAILURE);
        }

    }
    
};


struct CPU {
    

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

    // INTERRUPT FLAGS
    Byte IFF1 : 1; // Disables interrupts from being accepted
    Byte IFF2 : 2; // Temporary storage location for IFF1
    Byte IM; // Interrupt mode (0, 1, or 2)

    void Reset(Mem& memory) {

        // Sets the program counter to memory address 0
        PC = 0x0000;

        // Clear registers I and R
        I = 0x00;
        R = 0x00;

        // Reset both IFF1 and IFF2
        // This disables interrupts
        IFF1 = 0;
        IFF2 = 0;

        // Set interrupt mode to 0
        IM = 0;

    }

    void Execute(u32& cycles, Mem& memory) {

        // cycles - Number of CPU cycles to execute for 
        while (cycles >= 0) {

            // 1) Fetch the opcode
            Byte opcode = memory.read(PC);

            // 2) Increment PC
            PC++;
            
            // 3) Decode opcode
            switch (opcode) {

                // NOP (No operation)
                case 0x00: 
                    cycles -=4;
                    break;

                // LD BC, nn
                // Loads a 16 bit value into the BC register pair
                // E.g. 0x1234  B -> 0x12  C -> 0x34
                case 0x01:

                    // Read low byte of nn into C, high byte into B
                    C = memory.read(PC);
                    B = memory.read(PC++);

                    // Increment PC and decrement cycles
                    PC++;
                    cycles -= 10;

                    break;
                
                // Unknown opcode
                default: 
                    std::cerr << "Unknown opcode: [" << std::hex << (int)opcode << "]" << std::endl;
                    exit(EXIT_FAILURE);

            }

        }
        
    }

};

int main() {

    CPU cpu;
    Mem mem;

    cpu.Reset(mem);
    
    return 0;
}
