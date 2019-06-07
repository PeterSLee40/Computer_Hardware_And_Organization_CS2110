;;====================================
;; CS 2110 - Fall 2018
;; Homework 6
;;====================================
;; Name:
;;====================================

.orig x3000

  ;; YOUR CODE HERE :D

  AND R0, R0, #0	;;	i, current index
  
  AND R1, R1, #0	;;  temp value 1
  AND R2, R2, #0	;;  temp value 2
  AND R7, R7, #0

  LD R5, STR_ADDR_1	;; current address 1
  LD R6, STR_ADDR_2	;; current address 2
  

  LOOP
  	LDR R1, R5, 0				;;load current value
	LDR R2, R6, 0				;;load current value
	AND R7, R7, #0
	ADD R7, R1, R2				;;checks if both are zero, then end loop
	BRZ ENDLOOP 		;;end loop if value is zero
	
	NOT R2, R2			; 2'S COMPLEMENT R2
	ADD R2, R2, 1
	ADD R1, R1, R2		

	ADD R1, R1, 0
	BRNZ NOTBIG
		AND R1, R1, 0
		ADD R1, R1, 1
		BRNZP ENDLOOP
	NOTBIG NOP
	ADD R1, R1, 0
	BRZP NOTSMALL
		AND R1, R1, 0
		ADD R1, R1, -1
		BRNZP ENDLOOP
	NOTSMALL NOP
	ENDIF NOP
	ADD R5, R5, 1
	ADD R6, R6, 1
	BR LOOP
  ENDLOOP ST R1, ANSWER
  HALT

STR_ADDR_1 .fill x4000
STR_ADDR_2 .fill x4050

ANSWER     .blkw 1

.end

.orig x4000
  .stringz "This is a rest"
.end

.orig x4050
  .stringz "This is a rest"
.end