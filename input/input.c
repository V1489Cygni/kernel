#include "input.h"

#include "../service/service.h"
#include "../irq/irq.h"
#include "../output/output.h"

volatile unsigned char ready;
volatile unsigned char last;
unsigned char shift;
unsigned char table[0x80];
unsigned char shift_table[0x80];

void keyboard_handler(regs *r) {
    ready = 1;
    last = inportb(0x60);
}

unsigned char next_byte() {
    while(!ready) {
        __asm__ __volatile__ ("hlt");
    }
    ready = 0;
    return last;    
}

unsigned char next_char() {
    while(1) {
        unsigned char c = next_byte();
        if(c == 0x2a + 0x80 || c == 0x36 + 0x80) {
            shift = 0;
        } else if(c == 0x2a || c == 0x36) {
            shift = 1;
        } else if(c == 0x1c || c == 0x0e || (c < 0x80 && table[c])) {
            return c;
        }
    }			
}

unsigned char ascii_char(unsigned char byte) {
    if(shift) {
        return shift_table[byte];
    }
    return table[byte];
}

void init_input() {
    for(int i = 0; i < 0x80; i++) {
        table[i] = 0;
        shift_table[i] = 0;
    }
    table[2] = '1';
    table[3] = '2';
    table[4] = '3';
    table[5] = '4';
    table[6] = '5';
    table[7] = '6';
    table[8] = '7';
    table[9] = '8';
    table[10] = '9';
    table[11] = '0';
    table[12] = '-';
    table[13] = '=';
    table[16] = 'q';
    table[17] = 'w';
    table[18] = 'e';
    table[19] = 'r';
    table[20] = 't';
    table[21] = 'y';
    table[22] = 'u';
    table[23] = 'i';
    table[24] = 'o';
    table[25] = 'p';
    table[26] = '[';
    table[27] = ']';
    table[30] = 'a';
    table[31] = 's';
    table[32] = 'd';
    table[33] = 'f';
    table[34] = 'g';
    table[35] = 'h';
    table[36] = 'j';
    table[37] = 'k';
    table[38] = 'l';
    table[39] = ';';
    table[40] = 0x27;
    table[43] = 0x5c;
    table[44] = 'z';
    table[45] = 'x';
    table[46] = 'c';
    table[47] = 'v';
    table[48] = 'b';
    table[49] = 'n';
    table[50] = 'm';
    table[51] = ',';
    table[52] = '.';
    table[53] = '/';
    table[57] = ' ';
    shift_table[2] = '!';
    shift_table[3] = '@';
    shift_table[4] = '#';
    shift_table[5] = '$';
    shift_table[6] = '%';
    shift_table[7] = '^';
    shift_table[8] = '&';
    shift_table[9] = '*';
    shift_table[10] = '(';
    shift_table[11] = ')';
    shift_table[12] = '_';
    shift_table[13] = '+';
    shift_table[16] = 'Q';
    shift_table[17] = 'W';
    shift_table[18] = 'E';
    shift_table[19] = 'R';
    shift_table[20] = 'T';
    shift_table[21] = 'Y';
    shift_table[22] = 'U';
    shift_table[23] = 'I';
    shift_table[24] = 'O';
    shift_table[25] = 'P';
    shift_table[26] = '{';
    shift_table[27] = '}';
    shift_table[30] = 'A';
    shift_table[31] = 'S';
    shift_table[32] = 'D';
    shift_table[33] = 'F';
    shift_table[34] = 'G';
    shift_table[35] = 'H';
    shift_table[36] = 'J';
    shift_table[37] = 'K';
    shift_table[38] = 'L';
    shift_table[39] = ':';
    shift_table[40] = 0x22;
    shift_table[43] = '|';
    shift_table[44] = 'Z';
    shift_table[45] = 'X';
    shift_table[46] = 'C';
    shift_table[47] = 'V';
    shift_table[48] = 'B';
    shift_table[49] = 'N';
    shift_table[50] = 'M';
    shift_table[51] = '<';
    shift_table[52] = '>';
    shift_table[53] = '?';
    shift_table[57] = ' ';
    ready = 0;
    shift = 0;
    last = 0;
    irq_install_handler(1, keyboard_handler);
}
