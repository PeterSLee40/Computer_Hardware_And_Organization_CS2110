;;====================================
;; CS 2110 - Fall 2018
;; Homework 7
;; buildheap.asm
;;====================================
;; Name: Peter Lee
;;====================================

; Little reminder from your pals: don't run this directly by pressing
; ``Run'' in complx, since (look below) there's nothing put at address
; x3000. Instead, load it and use ``Debug'' -> ``Simulate Subroutine
; Call'' and choose the ``strlen'' label.

.orig x3000

halt

heapify
  ADD R6, R6, -4
  STR R7, R6, 2
  STR R5, R6, 1
  ADD R5, R6, 0
  ADD R6, R6, -5
  STR R0, R6, 4
  STR R1, R6, 3
  STR R2, R6, 2
  STR R3, R6, 1
  STR R4, R6, 0

LDR R0, R5, 6    ;load i into r0; contains reference to largest
;ADD R6, R6, -4 ;place stack pointer to build up first portion of the stack (a)
;STR R7, R6, 2  ;save old return address
;STR R5, R6, 1  ;save old frame pointer
;ADD R5, R6, 0  ;set current frame pointer
;ADD R6, R6, -5 ;place stack pointer to save all of the registers on the stack (b)
;STR R0, R6, 4  ;save R0
;STR R1, R6, 3  ;save R1
;STR R2, R6, 2  ;save R2
;STR R3, R6, 1  ;save R3
;STR R4, R6, 0  ;save R4;
;
;ADD R2, R0, -1  ;r2 is n-1
;BRnz BASE       ;check if n-1 is zero or neg
;ADD R6, R6, -4  ;R6 will now point to one above R4
;ADD R1, R0, -1  ;getting n-1;;
;
;STR R4, R6, 4   ;store n    
;STR R3, R6, 3   ;store largest addr
;STR R2, R6, 2   ;store childval
;STR R1, R6, 1   ;store child addr
;STR R0, R6, 0   ;store parent addr
;JSR heapify     ;recall subroutine;


STACK_BREAKDOWN
	LDR R3, R5, -4
	LDR R0, R5, -1
	LDR R4, R5, -5
	LDR R1, R5, -2
	LDR R2, R5, -3
	  
	  
	  ADD R6, R5, 0
	  LDR R7, R6, 2
	  LDR R5, R6, 1
	  ADD R6, R6, 1
	  RET 


buildheap
  ADD R6, R6, -4
  STR R7, R6, 2
  STR R5, R6, 1
  ADD R5, R6, 0
  ADD R6, R6, -5
  STR R0, R6, 4
  STR R1, R6, 3
  STR R2, R6, 2
  STR R3, R6, 1
  STR R4, R6, 0
; [ implement buildheap here ]
  LDR R1, R5, 4 ; 	R1 CONTAINS ARRAY
  LDR R0, R5, 5 ;	r0 now stores n
  LDR R2, R5, 5 ; 	R2 stores n

  BRn DONE
LOOP
  ADD R6, R6, -1
  STR R0, R6, 0
  ADD R6, R6, -1
  STR R2, R6, 0
  ADD R6, R6, -1
  STR R1, R6, 0
  JSR heapify

  ADD R0, R0, -1
  BRn DONE
  BR LOOP

DONE
STACK_BR2
	LDR R0, R5, -1
  	LDR R4, R5, -5
  	LDR R2, R5, -3
  	LDR R1, R5, -2
 	LDR R3, R5, -4
  	ADD R6, R5, 0
  	LDR R5, R6, 1
  	LDR R7, R6, 2
  	ADD R6, R6, 3
  	RET 

; Needed by Simulate Subroutine Call in complx
STACK .fill xF000
.end

; You should not have to LD from any label, take the
; address off the stack instead :)
