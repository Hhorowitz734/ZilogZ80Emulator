
// cpu.h 
// Main CPU file

#ifndef CPU_H
#define CPU_H

#include <stdlib.h>
#include <iostream>

#include "../types.h"
#include "../memory/mem.h"

namespace Opcodes {

    static constexpr Byte NOP = 0x00; // No operation
    static constexpr Byte LD_BC_NN = 0x01; // Load BC with 2 byte int


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

    Byte fetchOpcode(Mem& memory, Word& PC, u32& cycles) {

        // Getting the opcode is a 4 cycle operation on the Z80
        Byte opcode = memory.read(PC++);
        cycles -= 4;
        return opcode;
    
    }

    Byte memoryRead(Mem& memory, Word address, u32& cycles) const {

        // Reading a byte from memory is a 3 cycle operation on the Z80
        Byte data = memory.read(address);
        cycles -= 3;
        return data;

    }

    void Execute(u32& cycles, Mem& memory) {

        using namespace Opcodes;

        // cycles - Number of CPU cycles to execute for 
        while (cycles >= 0) {

            // 1) Fetch the opcode
            Byte opcode = fetchOpcode(memory, PC, cycles);

            // 2) Increment PC
            PC++;
            
            // 3) Decode opcode
            switch (opcode) {

                // NOP (No operation)
                case NOP: 
                    cycles -=4;
                    break;

                // LD BC, nn
                // Loads a 16 bit value into the BC register pair
                // E.g. 0x1234  B -> 0x12  C -> 0x34
                case LD_BC_NN:

                    // Read low byte of nn into C, high byte into B
                    C = memoryRead(memory, PC, cycles);
                    B = memoryRead(memory, PC++, cycles);

                    // Increment PC
                    PC++;

                    break;
                
                // Unknown opcode
                default: 
                    std::cerr << "Unknown opcode: [" << std::hex << (int)opcode << "]" << std::endl;
                    exit(EXIT_FAILURE);

            }

        }
        
    }

};

#endif