;;====================================
;; CS 2110 - Fall 2018
;; Homework 6
;;====================================
;; Name:
;;====================================

.orig x3000

  ;; YOUR CODE HERE :D


  ;; not(not a and not b)
	LD R1, A
	NOT R1, R1
	LD R2, B
	NOT R2, R2
	AND R3, R2, R1
	NOT R3, R3
	ST R3, ANSWER	
	HALT


A      .fill x1010
B      .fill x0404

ANSWER .blkw 1

.end
