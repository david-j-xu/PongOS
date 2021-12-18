; Bootloader
org 0x7c00 ; preconfigure offset of boot block

write:
    mov si, boot_message ; load string into source register
    call print_string   ; print the string
    jmp $               ; loop ad infinitum

%include "src/boot/utils.asm"

boot_message:
    db 'Booting OS', 0  ; null terminated string

; Marking as bootable sector
times 510-($-$$) db 0  ; padding
dw 0xaa55 ; magic number
