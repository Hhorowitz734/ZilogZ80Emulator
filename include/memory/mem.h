
// mem.h
// Main memory file

#ifndef MEM_H
#define MEM_H

#include <stdlib.h>
#include <iostream>

#include "../types.h"

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
        // Need a better way to do this; currently, this will always be true
        if (address < MAX_MEM) {
            return Data[address];
        } else { 
            std::cerr << "Memory read out of bounds at address: [" << std::hex << address << "]" << std::endl;
            exit(EXIT_FAILURE);
        }

    }
    
};

#endif