#include "system.h"

unsigned short *textmemptr;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;

#define COLS 80
#define ROWS 24

void scroll(void) {
    unsigned blank, temp;
    blank = 0x20 | (attrib << 8);
    if(csr_y >= ROWS) {
        temp = csr_y - ROWS + 1;
        memcpy ((unsigned char *)textmemptr, 
		(const unsigned char *)textmemptr + temp * COLS, 
		(ROWS - temp) * COLS * 2);
        memsetw (textmemptr + (ROWS - temp) * COLS, blank, COLS);
        csr_y = ROWS - 1;
    }
}

void move_csr(void) {
    unsigned temp;
    temp = csr_y * COLS + csr_x;
    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

void cls() {
    unsigned blank;
    int i;
    blank = 0x20 | (attrib << 8);
    for(i = 0; i < ROWS; i++)
        memsetw (textmemptr + i * COLS, blank, COLS);
    csr_x = 0;
    csr_y = 0;
    move_csr();
}

void putch(unsigned char c) {
    unsigned short *where;
    unsigned att = attrib << 8;
    if(c == 0x08) {
        if(csr_x != 0) { 
            csr_x--;
            putch(' ');
            csr_x--;
        }
    }
    else if(c == 0x09) {
        csr_x = (csr_x + 8) & ~(8 - 1);
    }
    else if(c == '\r') {
        csr_x = 0;
    }
    else if(c == '\n') {
        csr_x = 0;
        csr_y++;
    }
    else if(c >= ' ') {
        where = textmemptr + (csr_y * COLS + csr_x);
        *where = c | att;
        csr_x++;
    }
    if(csr_x >= COLS) {
        csr_x = 0;
        csr_y++;
    }
    scroll();
    move_csr();
}

void puts(unsigned char *text) {
    int i;
    for (i = 0; i < strlen((const char*)text); i++) {
        putch(text[i]);
    }
}

void settextcolor(unsigned char forecolor, unsigned char backcolor) {
    attrib = (backcolor << 4) | (forecolor & 0x0F);
}

void init_video(void) {
    textmemptr = (unsigned short *)0xB8000;
    cls();
}
