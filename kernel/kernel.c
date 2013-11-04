#include "../input/input.h"
#include "../output/output.h"
#include "../shell/shell.h"
#include "../gdt/gdt.h"
#include "../idt/idt.h"
#include "../isr/isr.h"

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
    init_input();
    init_output();
    gdt_install();
    idt_install();
    isr_install();
    while(1) {
        print((unsigned char*)"> ");
        process_cmd(next_cmd());
    }
}
    
