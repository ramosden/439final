//read bytes from IO ports 

/* use gheith's outb inb 
create port class with port object and constructor taking in port number
write method to execute outb
read method to execute inb

software registers
we have index ports to access them
write to index port the 

port for graphics mode and text mode to trigger them

index port
- write to this to tell hardware what port u want to R/W from
- tell qemu (hardware) to expose a port so we can read/write in instr
ex. write to index port 0x3c, to value port, can now write 3 
0x3c would then hold value c

read from port
- write into index port the port number, read from value port

wrapper class
 index port = 0x2c - security guard, ask for permission
 value part = 0x3c
port i want to write to = 0x3c1
value I want to write = 8
outb(ox2c,ox3c1) //3c1 will meet me at 0x3c (exposed at 3c)
outb(ox3c, 8) write 8 into 3c1 at location 3c
 hardware give me access to 0x3c
 combine index port and data port into single port 

data port
*/

// #include "ports.h"
// #include "machine.h"

// int port_number = 0;

// Ports * newPort = new Ports(port_number);


