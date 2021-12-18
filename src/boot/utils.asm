; Utility functions

print_string:
    .loop:
        lodsb           ; loads next byte into al
        cmp al, 0x00    ; checks if null
        je .done        ; if so, end loop
        call print_char ; print character
        jmp .loop       ; loop
    .done:
        ret             ; return to caller

print_char:
    ; Prints the byte stored in al
    mov ah, 0x0e    ; set AH to 0eh to print character
    int 0x10        ; interrupt to print character
    ret