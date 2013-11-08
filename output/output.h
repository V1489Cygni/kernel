#ifndef OUTPUT_H
#define OUTPUT_H

void scroll();
void move_csr();
void cls();
void print_char(unsigned char);
void print_int(int);
void print(unsigned char*);
void settextcolor(unsigned char, unsigned char);
void init_output();

#endif
