#include "system.h"

unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count) {
    int i;
    for (i=0; i<count;i++) dest[i]=src[i];
    return dest;
}

unsigned char *memset(unsigned char *dest, unsigned char val, int count) {
    int i;
    for (i=0; i<count;i++) dest[i]=val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count) {
    int i;
    for (i=0; i<count;i++) dest[i]=val;
    return dest;
}

int strlen(const char *str) {
    int i;
    for (i=0;;i++) if (str[i] == '\0') return i;
}

unsigned char inportb (unsigned short _port) {
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data) {
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

void prc(unsigned char c) {
	unsigned char* hex = (unsigned char*)"0123456789ABCDEF";
	for(int i = 0; i < 16; i++)
		if(((c >> 4)&0xF) == i)
			putch(hex[i]);
	for(int i = 0; i < 16; i++)
		if((c&0xF) == i)
			putch(hex[i]);
}

void processCommand(unsigned char* cmd, int last) {
	if(last > 4) {
		if(cmd[0] == 'e' && cmd[1] == 'c' && cmd[2] == 'h' && cmd[3] == 'o' && cmd[4] == ' ') {
			puts(cmd + 5);
			putch('\n');
			return;
		}
	}
	puts((unsigned char*)"Unknown command!\n");
}

void cmain (unsigned long magic, unsigned long addr) {
    unsigned char table1[256];
	unsigned char table2[256];
	for(int i = 0; i < 256; i++) {
		table1[i] = 0;
		table2[i] = 0;
	}
    table1[2] = '1';
	table1[3] = '2';
	table1[4] = '3';
	table1[5] = '4';
	table1[6] = '5';
	table1[7] = '6';
	table1[8] = '7';
	table1[9] = '8';
	table1[10] = '9';
	table1[11] = '0';
	table1[12] = '-';
	table1[13] = '=';
	table1[16] = 'q';
	table1[17] = 'w';
	table1[18] = 'e';
	table1[19] = 'r';
	table1[20] = 't';
	table1[21] = 'y';
	table1[22] = 'u';
	table1[23] = 'i';
	table1[24] = 'o';
	table1[25] = 'p';
	table1[26] = '[';
	table1[27] = ']';
	table1[30] = 'a';
	table1[31] = 's';
	table1[32] = 'd';
	table1[33] = 'f';
	table1[34] = 'g';
	table1[35] = 'h';
	table1[36] = 'j';
	table1[37] = 'k';
	table1[38] = 'l';
	table1[39] = ';';
	table1[40] = 0x27;
	table1[43] = 0x5c;
	table1[44] = 'z';
	table1[45] = 'x';
	table1[46] = 'c';
	table1[47] = 'v';
	table1[48] = 'b';
	table1[49] = 'n';
	table1[50] = 'm';
	table1[51] = ',';
	table1[52] = '.';
	table1[53] = '/';
	table1[57] = ' ';
	table2[2] = '!';
	table2[3] = '@';
	table2[4] = '#';
	table2[5] = '$';
	table2[6] = '%';
	table2[7] = '^';
	table2[8] = '&';
	table2[9] = '*';
	table2[10] = '(';
	table2[11] = ')';
	table2[12] = '_';
	table2[13] = '+';
	table2[16] = 'Q';
	table2[17] = 'W';
	table2[18] = 'E';
	table2[19] = 'R';
	table2[20] = 'T';
	table2[21] = 'Y';
	table2[22] = 'U';
	table2[23] = 'I';
	table2[24] = 'O';
	table2[25] = 'P';
	table2[26] = '{';
	table2[27] = '}';
	table2[30] = 'A';
	table2[31] = 'S';
	table2[32] = 'D';
	table2[33] = 'F';
	table2[34] = 'G';
	table2[35] = 'H';
	table2[36] = 'J';
	table2[37] = 'K';
	table2[38] = 'L';
	table2[39] = ':';
	table2[40] = 0x22;
	table2[43] = '|';
	table2[44] = 'Z';
	table2[45] = 'X';
	table2[46] = 'C';
	table2[47] = 'V';
	table2[48] = 'B';
	table2[49] = 'N';
	table2[50] = 'M';
	table2[51] = '<';
	table2[52] = '>';
	table2[53] = '?';
	table2[57] = ' ';
	char shift = 0;
	unsigned char last = inportb(0x60);
	init_video();
	while(1) {
		puts ((unsigned char*)"> ");
		unsigned char buffer[256];
		unsigned int i = 0;
		unsigned char c;
		while(1) {
			c = inportb(0x60);
			if(c != last) {
				if(c == 0x2a + 0x80 || c == 0x36 + 0x80) {
					shift = 0;
				}
				last = c;
				if(c >= 0x80) {
					last = c;
				} else {
					if(c == 0x2a || c == 0x36) {
						shift = 1;
					} else if(c == 0x1c) {
						break;
					} else if(c == 0x0e) {
						last = 0x0e;
						if(i > 0) {
							i--;
							putch(0x08);
						}
					} else if(table1[c]) {
						if(shift) {
							putch(table2[c]);	
							buffer[i] = table2[c];
						} else {
							putch(table1[c]);
							buffer[i] = table1[c];
						}
						i++;
					}
				}			
			}
		}
		putch('\n');
		buffer[i] = '\0';
		processCommand(&buffer, i - 1);
	}
}
