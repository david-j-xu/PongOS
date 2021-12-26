; Utility functions
bits 16
print_string:
    .loop:
        mov al, [bx]    ; moves character at bx to al
        cmp al, 0x00    ; checks if null
        je .done        ; if so, end loop
        call print_char ; print character
        add bx, 0x01    ; increment address
        jmp .loop       ; loop
    .done:
        ret             ; return to caller

print_char:
    ; Prints the byte stored in al
    mov ah, 0x0e    ; set AH to 0eh to print character
    int 0x10        ; interrupt to print character
    ret

load_sectors:
    ; loads dh sectors after the boot sector from drive dl
    push dx         ; save argument for error checking
    mov ah, 0x02    ; set up for read
    mov al, dh      ; read dh sectors
    mov ch, 0x00    ; cylinder 0
    mov dh, 0x00    ; head 0
    mov cl, 0x02    ; sector 0
    int 0x13        ; interrupt
    jc disk_error   ; if carry, halt
    pop dx          ; check correct number of sectors read
    cmp dh, al      ; check dh == number of sectors read
    jne disk_error  ; if so, print an error
    ret

disk_error:
    mov bx, DISK_ERROR_MSG 
    call print_string
    jmp $

DISK_ERROR_MSG:
    db `Disk read error!\n\r`, 0