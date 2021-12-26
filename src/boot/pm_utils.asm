; utility functions in 32-bit protected mode
[bits 32]
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

clear_display:
    ; clears the vga display
    pusha                   ; preserve current register values
    mov edx, VIDEO_MEMORY   ; set beginning memory address
    mov bx, 0x7D0           ; set counter to number of pixels
    mov al, 0x00            ; write NULL at each location
    mov ah, WHITE_ON_BLACK  ; set write mode for each location
    .loop:
        cmp bx, 0x0         ; if counter is 0, stop and end
        je .done            ; jump to end of loop
        mov [edx], eax      ; write to the next address in graphics
        add edx, 2          ; increment the address
        dec bx              ; decrement the counter
        jmp .loop           ; continue looping
    .done:
        popa                ; restore register values
        ret                 ; return

print_string_pm:
    ; writes the null terminated string pointed to by ebx to top right of screen
    pusha                       ; store current register values
    mov edx, VIDEO_MEMORY       ; store video memory address in edx
    .loop:
        mov al, [ebx]           ; move current character to al
        mov ah, WHITE_ON_BLACK  ; place settings into ah
        cmp al, 0x00            ; see if null
        je  .done               ; if so, complete the loop
        mov [edx], eax             ; place correct value into video memory
        add ebx, 1              ; increment pointer in string
        add edx, 2              ; increment pointer in video memory
        jmp .loop
    .done:
        popa                    ; restore register values
        ret                     ; return
