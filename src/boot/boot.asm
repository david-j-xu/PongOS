; Bootloader
org 0x7c00 ; preconfigure offset of boot block

write:
    mov bx, BOOT_MESSAGE ; load string into source register
    call print_string   ; print the string

set_boot_drive:
    mov [BOOT_DRIVE], dl

set_stack:
    mov bp, 0x8000          ; set stack base pointer to 0x8000
    mov sp, bp              ; set stack pointer to base pointer

load_next_sectors:
    mov bx, 0x0000              ; set ES to 0x0000
    mov es, bx                  ; set ES to 0x0000
    mov bx, 0x9000              ; Load next sectors to ES:0x9000
    mov dh, [LOAD_NUM_SECTORS]  ; Specify the number of sectors to be loaded
    mov dl, [BOOT_DRIVE]        ; load from the boot drive
    call load_sectors           ; load the drives

test_load:
    mov ax, [0x9000]
    call print_char
    mov ax, [0x9000 + 512]
    call print_char

    jmp $

%include "src/boot/utils.asm"

BOOT_DRIVE:
    db 0                ; store boot drive number here
BOOT_MESSAGE:
    db `Booting PongOS...\n\r`, 0  ; null terminated string
LOAD_NUM_SECTORS:
    db 3

; Marking as bootable sector
times 510-($-$$) db 0  ; padding
dw 0xaa55 ; magic number

; second sector code:
times 256 dw 0x6162
times 256 dw 0x6364
times 256 dw 0x6566
times 256 dw 0x6768