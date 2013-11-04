#include "shell.h"

#include "../input/input.h"
#include "../output/output.h"

unsigned char buffer[256];

unsigned char* next_cmd() {
    int i = 0;
    while(1) {
        unsigned char c = next_char();
        if(c == 0x0e) {
            if(i > 0) {
                i--;
                print_char(0x08);
            }
        } else if(c == 0x1c) {
            buffer[i] = '\0';
            print_char('\n');
            return &buffer;
        } else {
            c = ascii_char(c);
            buffer[i++] = c;
            print_char(c);
        }
    }
}
