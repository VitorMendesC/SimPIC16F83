#include <xc.inc>
; psect   barfunc,local,class=CODE,delta=2 ; PIC10/12/16

psect reset_vector, class=CODE, delta=2
reset_vector:
    PAGESEL main
    goto main

    
COUNT equ 0x0C
R0 equ 0x0D
R1 equ 0x0E
R2 equ 0x0F
 
psect code, delta=2
main:
    sleep
    movlw 13
    movwf COUNT
    clrf R0
    clrf R1
    clrf R2
    incf R1
fib:
    movf R0, w
    addwf R1, w
    movwf R2
    movf R1, w
    movwf R0
    movf R2, w
    movwf R1
    decfsz COUNT
    goto fib
    sleep
END
    
    
    