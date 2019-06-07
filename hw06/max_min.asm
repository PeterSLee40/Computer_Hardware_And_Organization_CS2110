;;====================================
;; CS 2110 - Fall 2018
;; Homework 6
;;====================================
;; Name:
;;====================================

.orig x3000

  ;; YOUR CODE HERE :D
  ;; get the top of the list
  ;; if int > max, max = int
  ;; if int min, min = int
  ;; go to next index (or remove from list)
  ;; repeat until empty

  AND R0, R0, 0      ; cur val
  AND R1, R1, 0      ; cur address
  AND R2, R2, 0      ; next address
  LD R1, HEAD_ADDR
  LD R3, MIN_INT      ; max register initialized with min
  LD R4, MAX_INT      ; min register initialized with max

  AND R5, R5, 0       ; temp 2's complement max
  AND R6, R6, 0       ; temp 2's complement min


  ;;do while index is not 0
  DO1 NOP   ;DO
    LDR R2, R1, 0         ; get next pointer
    LDR R0, R1, 1         ; read current

    AND R5, R5, 0         ;
    AND R7, R7, 0         ; clear reg 7
    ADD R5, R0, 0         ; sets r5 to current
    NOT R5, R5            ; 
    ADD R5, R5, 1         ; twos complement cUrrent
    ADD R7, R3, R5        ; max - current
    BRNZ NOTOVERFLOW      ; if sum is positive, 
      ADD R3, R3, 0       ; if max is negative,
      BRZP NOTOVERFLOW
        ADD R0, R0, 0     ;current is positive
        BRP OVERFLOW      ;then overflow
    NOTOVERFLOW ADD R7, R7, 0
    BRZP LESSTHANMAX
      OVERFLOW
      AND R3, R3, 0
      ADD R3, R3, R0
    LESSTHANMAX NOP

    LDR R0, R1, 1         ; read current
    AND R5, R5, 0         ;
    AND R7, R7, 0
    ADD R5, R4, 0         ;
    NOT R5, R5            ;
    ADD R5, R5, 1         ; twos complement max
    ADD R7, R0, R5
    BRZP MORETHANMIN
      AND R4, R4, 0
      ADD R4, R0, R4
    MORETHANMIN NOP


    ;if greater than max, set new max
    ;if less than min, set new min.
  AND R1, R1, 0
  ADD R1, R2, 0
  BRP DO1   ;while next is not 0 condition
ST R3, ANSWER_MAX
ST R4, ANSWER_MIN
HALT


HEAD_ADDR  .fill x4000

MAX_INT    .fill x7FFF
MIN_INT    .fill x8000

ANSWER_MAX .blkw 1
ANSWER_MIN .blkw 1

.end

.orig x4000
  .fill x4002         ;; Node 1
  .fill 4
  .fill x4004         ;; Node 2
  .fill 5
  .fill x4006         ;; Node 3
  .fill 25
  .fill x4008         ;; Node 4
  .fill 1
  .fill x0000         ;; Node 5
  .fill 10
.end
