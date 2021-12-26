; Bootloader
bits 16
org 0x7c00 ; preconfigure offset of boot block
KERNEL_LOC equ 0x1000       ; location of our kernel

write:                      ; write booting status to screen
    mov bx, BOOT_MESSAGE    ; load string into source register
    call print_string       ; print the string

set_boot_drive:             ; save state of boot drive to BOOT_DRIVE
    mov [BOOT_DRIVE], dl    ; copy dl to BOOT_DRIVE

set_stack:
    mov bp, 0x9000          ; set stack base pointer to 0x8000
    mov sp, bp              ; set stack pointer to base pointer

load_kernel:
    mov bx, KERNEL_LOAD_MESSAGE     ; Place status string
    call print_string               ; Print loading kernel message

switch_to_pm:
    mov bx, PROTECTED_MODE_MESSAGE  ; Place status string
    call print_string               ; Print transition to 32 bit protected mode
    call pm_switch                  ; initiate switch to 32 bit protected mode

    jmp $

load_next_sectors:
    mov bx, 0x0000              ; set ES to 0x0000
    mov es, bx                  ; set ES to 0x0000
    mov bx, 0x9000              ; Load next sectors to ES:0x9000
    mov dh, [LOAD_NUM_SECTORS]  ; Specify the number of sectors to be loaded
    mov dl, [BOOT_DRIVE]        ; load from the boot drive
    call load_sectors           ; load the drives

; include bootstrapping and utility functions
%include "src/boot/boot_utils.asm"
; include global descriptor table definition
%include "src/boot/gdt.asm"
; include protected mode utility functions
%include "src/boot/pm_utils.asm"
; include code allowing switch to protected mode
%include "src/boot/pm_switch.asm"

bits 32
kernel_execute:
    call clear_display
    mov ebx, HELLO_WORLD
    call print_string_pm
    jmp $                       ; hang if error occurred

; global boot variables
BOOT_DRIVE:
    db 0                        ; store boot drive number here
BOOT_MESSAGE:
    db `Booting PongOS...\n\r`, 0
KERNEL_LOAD_MESSAGE:
    db `Loading Kernel...\n\r`, 0
PROTECTED_MODE_MESSAGE:
    db `Entering 32 bit protected mode...\n\r`, 0
HELLO_WORLD:
    db `Hello World!`, 0
LOAD_NUM_SECTORS:
    db 0xF                      ; load the next 15 sectors

; Marking as bootable sector
times 510-($-$$) db 0   ; padding
dw 0xaa55               ; magic number