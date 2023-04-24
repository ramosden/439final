#ifndef _ports_h_
#define _ports_h_

#include "machine.h"
#include "stdint.h"

/* Ports object to read/write the correct values to/from ports
We pair programmed this too! (Katherine, Denise, Elin) */

class Ports {
    public:
        uint16_t port_number;
        Ports(uint16_t port_number): port_number(port_number) {}

        ~Ports() {}

        unsigned char read() {
            return inb(port_number);
        }   

        void write(char val) {
            outb(this -> port_number, val);
        }
};

#endif