#include "../input/input.h"
#include "../output/output.h"
#include "../shell/shell.h"
#include "../gdt/gdt.h"
#include "../idt/idt.h"
#include "../isr/isr.h"
#include "../irq/irq.h"
#include "../pit/pit.h"

void process_cmd(unsigned char* cmd) {
    int length = 0;
    for(;; length++)
        if(!cmd[length])
            break;
    if(length > 5 && cmd[0] == 'e' && cmd[1] == 'c' && cmd[2] == 'h' && cmd[3] == 'o' && cmd[4] == ' ') {
        print(cmd + 5);
        print_char('\n');
        return;
    } else if (length == 3 && cmd[0] == 'c' && cmd[1] == 'l' && cmd[2] == 's') {
        cls();
        return;
    } 
	print((unsigned char*)"Unknown command!\n");
}

int kernel_main() {
    init_output();
    print((unsigned char*)"Video memory is set up into text mode\nInstalling GDT...                  ");
    gdt_install();
    print((unsigned char*)"OK\nInstalling IDT...                  ");
    idt_install();
    print((unsigned char*)"OK\nInstalling ISRs...                 ");
    isr_install();
    print((unsigned char*)"OK\nInstalling IRQs...                 ");
    irq_install();
    print((unsigned char*)"OK\nInstalling keyboard input...       ");
    init_input();
    print((unsigned char*)"OK\nInstalling timer...                ");
    timer_install();
    print((unsigned char*)"OK\nEnableing interrupts...            ");
    __asm__ __volatile__ ("sti");
    print((unsigned char*)"OK\nMain is loaded at: ");
    print_int((int)kernel_main);
    print_char('\n');
    while(1) {
        print((unsigned char*)"> ");
        process_cmd(next_cmd());
    }
}
    
