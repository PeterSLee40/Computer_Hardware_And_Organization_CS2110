;;====================================
;; CS 2110 - Fall 2018
;; Homework 7
;; string_ops.asm
;;====================================
;; Name: Peter Lee 
;;====================================

; Little reminder from your pals: don't run this directly by pressing
; ``Run'' in complx, since (look below) there's nothing put at address
; x3000. Instead, load it and use ``Debug'' -> ``Simulate Subroutine
; Call'' and choose the ``strlen'' label.

.orig x3000

halt

strlen
    ADD R6, R6, -3   ;initialize space for everything
    STR R7, R6, 1    ;store RA
    STR R5, R6, 0    ;store old FP
    ADD R6, R6, -4   ;initialize space for registers
    ADD R5, R6, 3    ;place new FP
    STR R2, R6, 1    ;store R2 on the stack
    STR R0, R6, 3    ;store R0 on the stack
    STR R1, R6, 2    ;store R1 on the stack
    STR R3, R6, 0    ;store R3 on the stack

    LDR R0, R5, 4    ;load the address of string into R0
    AND R1, R1, 0    ;reset R1 to 0, it'll be the length

LOOPSTRING
    ADD R2, R0, R1   ;R2 -> address of current character
    LDR R2, R2, 0    ;R2 -> value of current character

    BRZ ENDSTRING    ;if value of character is 0, reached the end

    ADD R1, R1, 1    ;increment string length
    BR LOOPSTRING

ENDSTRING
    STR R1, R5, 3    ;store strlen at the return value spot


TEARDOWN
    LDR R3, R6, 0   ;reload R3
    LDR R2, R6, 1   ;reload R2
    LDR R1, R6, 2   ;reload R1
    LDR R0, R6, 3   ;reload R0
    ADD R6, R6, 4   ;add the stack pointer
    LDR R5, R6, 0   ;reload old FP
    LDR R7, R6, 1   ;reload return address
    ADD R6, R6, 2   ;put the stack pointer at the rv
    RET



count_occurrence
;;store address of string into strin length, then call 
;; [ implement count_occurrence() here ]
    ADD R6, R6, -3 ;place stack pointer to build up first portion of the stack (a)
    STR R7, R6, 1 ;save old return address
    STR R5, R6, 0  ;save old frame pointer
    ADD R6, R6, -6 ;place stack pointer to save all of the registers on the stack (b)
    ADD R5, R6, 5  ;NEW FP
    STR R1, R6, 3  ;save R1
    STR R0, R6, 4  ;save R0
    STR R2, R6, 2  ;save R2
    STR R4, R6, 0  ;save R4
    STR R3, R6, 1  ;save R3
    AND R4, R4, 0
    STR R4, R6, 5       ;store strlen

    LDR R0, R5, 4  ;R0 <= n
    LDR R3, R5, 5   ;STORE CHAR IN R3
    AND R1, R1, 0   ;THE COUNT

    ADD R6, R6, -1
    STR R0, R6, 0
    JSR strlen

    LDR R2, R6, 0   ;store result
    ADD R6, R6, 2   ;teardown

    LOOP
        ADD R2, R2, -1
        BRN ENDLOOP     ;TERMINATING
        LDR R4, R0 , 0
        NOT R4, R4
        ADD R4, R4, 1
        ADD R4, R4, R3
        BRNP CONTINUE
        ADD R1, R1, 1
        CONTINUE ADD R0, R0, 1
            BR LOOP

    ENDLOOP
        STR R1, R5, 3
    BREAKDOWN
        LDR R4, R6, 0
        LDR R2, R6, 2
        LDR R3, R6, 1
        LDR R1, R6, 3
        LDR R0, R6, 4
        ADD R6, R6, 6   ;ADD STACK POINTER
        LDR R5, R6, 0   ;GET OLD FP
        LDR R7, R6, 1   ;GET OLD RET ADDR
        ADD R6, R6, 2   ;PUT Stack pointer at return val.
        RET



;
;
;
;
;
;



; Needed by Simulate Subroutine Call in complx
STACK .fill xF000
.end

; You should not have to LD from any label, take the
; address off the stack instead :)
