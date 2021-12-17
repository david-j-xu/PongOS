; Bootloader

mov ax, 0


hello_world:
    mov ah, 0x0e
    mov al, 'H'
    int 0x10
    mov al, 'e'
    int 0x10
    mov al, 'l'
    int 0x10
    mov al, 'l'
    int 0x10
    mov al, 'o'
    int 0x10
    mov al, 10
    int 0x10
    mov al, 13
    int 0x10
    jmp $

times 510-($-$$) db 0  ; fill remaining elements of bootsector with 0

dw 0xaa55 ; magic number