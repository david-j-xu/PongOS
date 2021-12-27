; Bootloader
[bits 16]
[org 0x7c00] ; preconfigure offset of boot block

boot_main:
    write:                      ; write booting status to screen
        mov bx, BOOT_MESSAGE    ; load string into source register
        call print_string       ; print the string

    set_boot_drive:             ; save state of boot drive to BOOT_DRIVE
        mov [BOOT_DRIVE], dl    ; copy dl to BOOT_DRIVE

    set_stack:
        mov bp, 0x9000          ; set stack base pointer to 0x8000
        mov sp, bp              ; set stack pointer to base pointer
    
    call load_kernel            ; load the next sectors into memory starting at KERNEL_LOC
    call switch_to_pm           ; switch to 32 bit protected mod
    hlt                         ; hang

; include bootstrapping and utility functions
%include "src/boot/boot_utils.asm"
; include global descriptor table definition
%include "src/boot/gdt.asm"
; include protected mode utility functions
%include "src/boot/pm_utils.asm"
; include code allowing switch to protected mode
%include "src/boot/pm_switch.asm"

KERNEL_LOC equ 0x1000       ; location of our kernel

[bits 16]
load_kernel:
    mov bx, KERNEL_LOAD_MESSAGE     ; Place status string
    call print_string               ; Print loading kernel message

    mov ax, 0x0                     ; set ax register to 0x00
    mov es, ax                      ; set es register to 0x00
    mov bx, KERNEL_LOC              ; set bx register to 0x1000
    mov dh, [LOAD_NUM_SECTORS]      ; set to load [LOAD_NUM_SECTORS] sectors
    mov dl, [BOOT_DRIVE]            ; set correct boot drive here
    call load_sectors               ; load the next sectors to ES:BX

    ret

[bits 16]
switch_to_pm:
    mov bx, PROTECTED_MODE_MESSAGE  ; Place status string
    call print_string               ; Print transition to 32 bit protected mode

    call switch_vga_mode            ; switch VGA mode to graphics

    call pm_switch                  ; initiate switch to 32 bit protected mode
    hlt

[bits 32]
kernel_execute:
    ; call clear_display          ; clear VGA display
    call KERNEL_LOC             ; call into our kernel
    hlt                         ; hang if error occurred

; global boot variables
BOOT_DRIVE:
    db 0                        ; store boot drive number here
BOOT_MESSAGE:
    db `Booting PongOS...\n\r`, 0
KERNEL_LOAD_MESSAGE:
    db `Loading Kernel...\n\r`, 0
PROTECTED_MODE_MESSAGE:
    db `Entering 32 bit protected mode...\n\r`, 0
LOAD_NUM_SECTORS:
    db 53                      ; load the next 53 sectors

; Marking as bootable sector
times 510-($-$$) db 0   ; padding
dw 0xaa55               ; magic number