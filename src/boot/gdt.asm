; Defining and setting up the global descriptor table
bits 16
gdt_start:

gdt_null:
    times 2 dd 0x0   ; write the 8 byte null descriptor

gdt_code:               ; code segment descriptor
    dw 0xffff           ; limit
    dw 0x0              ; base (top 2 bytes)
    db 0x0              ; base (next byte)
    db 10011010b        ; first flags, type flags
    db 11001111b        ; second flags, limit
    db 0x0              ; base (last byte)

gdt_data:
    dw 0xffff           ; limit
    dw 0x0              ; base (top 2 bytes)
    db 0x0              ; base (next byte)
    db 10010010b        ; first flags, type flags
    db 11001111b        ; second flags, limit
    db 0x0              ; base (last byte)

gdt_end:                ; mark end of the gdt

gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; size of the gdt
    dd gdt_start                ; start address

; define constants for location of the code and data segments
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start


