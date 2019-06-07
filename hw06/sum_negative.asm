;;====================================
;; CS 2110 - Fall 2018
;; Homework 6
;;====================================
;; Name:PETER LEE, PLEE99
;;====================================

.orig x3000


;; for (int i = 0; i < length; i++) {
;;	if array[i] < 0,
;;  sum = sum += array[i]
;;
;;
  ;; YOUR CODE HERE :D
	LD R1, ARRAY_ADDR 	;current index
	AND R0, R0, #0 		;answer
	AND R3, R3, #0  	;sum
	AND R4, R4, #0 		;temp
	LD R2, ARRAY_LEN	;total length


	LOOP    ADD R2, R2, #0 		;; resets register
		BRNZ DONE 				;; termination case
		LDR R4, R1, 0 			;; loads current
		BRZP LMAO
		ADD R3, R3, R4			;; sums current
		LMAO ADD R2, R2, -1			;; decremements i
		ADD R1, R1, 1			;; moves along in memory
		BR  LOOP				;; reiterates
	DONE ST R3, ANSWER
	HALT


ARRAY_ADDR .fill x4000
ARRAY_LEN  .fill 10

ANSWER     .blkw 1

.end

.orig x4000
  .fill 7
  .fill -18
  .fill 0
  .fill 5
  .fill -9
  .fill 25
  .fill 1
  .fill -2
  .fill 10
  .fill -6
.end
