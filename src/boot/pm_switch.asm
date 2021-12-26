; Switch to 32 bit protected mode
bits 16
pm_switch:
    cli                     ; prevent interrupts during switch
    lgdt [gdt_descriptor]   ; load global descriptor table

    mov eax, cr0            ; move cr0 to eax
    or  eax, 0x1            ; set the first bit to indicate in protected mode
    mov cr0, eax            ; set cr0 to updated register

    jmp CODE_SEG:pm_init    ; initialize once in protected mode


bits 32                     ; now in protected mode
pm_init:
    mov ax, DATA_SEG        ; set ax register to the data segment
    
    mov ds, ax              ; copy to other registers
    mov es, ax 
    mov ss, ax 
    mov fs, ax 
    mov gs, ax 

    mov ebp, 0x90000        ; set up larger stack
    mov esp, ebp

    call kernel_execute
