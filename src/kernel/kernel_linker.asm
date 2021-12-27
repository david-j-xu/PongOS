; Link correct entry point for kernel code
[bits 32]
[extern main]

_start:
    call main       ; jump to main
    ret             ; return