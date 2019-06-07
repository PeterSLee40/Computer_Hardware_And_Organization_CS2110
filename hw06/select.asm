;;====================================
;; CS 2110 - Fall 2018
;; Homework 6
;;====================================
;; Name: PETER LEE, PLEE99
;;====================================

.orig x3000

;SOODOOCOODE
;for i = 0 to ARRAY_LEN - 1: # Iterate through every position in the array
  ;min_idx = i # Find the element that will move to position i
  ;for j = i + 1 to ARRAY_LEN:
    ;if ARRAY_ADDR[j] < ARRAY_ADDR[min_idx]:
      ;min_idx = j
  ;swap(ARRAY_ADDR[i], ARRAY_ADDR[min_idx])
  ;temp = ARRAY_ADDR[i]
  ;ARRAY_ADDR[i] = ARRAY_ADDR[j]
  ;'ARRAY_ADDR[j] = temp


LD R2, ARRAY_ADDR           ; current index
LD R3, ARRAY_LEN            ;total length
AND R0, R0, 0               ;i
AND R1, R1, 0               ;j
AND R4, R4, #0              ;temp value
AND R6, R6, #0              ;temp address
AND R7, R7, #0              ;min value

AND R5, R5, #0
ADD R5, R3, #0
NOT R5, R5
ADD R5, R5, #1              ;negative length



LOOPI    ADD R0, R0, #0     ;; resets I
    AND R7, R7, #0
    AND R6, R6, #0
    ADD R6, R5, R0          ;; (i - length < 0)
    BRZP DONEI              ;; termination case

    AND R1, R1, #0
    ADD R1, R0, #1          ;;SET J TO BE I+1
    ADD R7, R0, #0

    LOOPJ ADD R1, R1, #0    ;;RESETS J

      AND R6, R6, #0 
      ADD R6, R5, R1        ;;(j - length < 0)
      BRZP DONEJ            ;;termination case

      ;if current - min < 0, min = current
      AND R6, R6, #0        ;;clear r6
      ADD R6, R2, R1        ;;start + j
      AND R3, R3, #0        ;;clear r3
      ADD R3, R2, R7        ;;start + min
      LDR R6, R6, #0        ;;ARRAY[start + j]
      LDR R3, R3, #0        ;;Array[start + min]
      NOT R3, R3
      ADD R3, R3, #1        ;;negative start+minx
      ADD R6, R6, R3        ;;ARRAY[start + j] - ARRAY[start + min]
      BRZP ENDIF
      AND R7, R7, #0
      ADD R7, R1, #0            ;; min = j
      ENDIF NOP


      ADD R1, R1, #1        ;;increments
      BR LOOPJ              ;;repeat
    DONEJ                   ;;end loop
    
    AND R6, R6, #0          ;;clear R6
    AND R4, R4, #0          ;;clear R4
    ADD R6, R2, R0          ;;get current address
    LDR R4, R6, #0          ;;load address r6 as r4, a temp value.
    
    AND R6, R6, #0          ;;clear R6, i + start_address
    ADD R6, R2, R0          ;;start + i
    ADD R3, R2, R7          ;;R3 =  start_address + min
    LDR R7, R3, #0          ;;r7 = array[start + nin]
    STR R7, R6, #0          ;;store array[start + min] at mem[start + i]
    STR R4, R3, #0          ;;store temp at mem[start + min]


    ADD R0, R0, #1          ;;increments
    BR  LOOPI               ;;repeat
  DONEI                     ;;end loop


HALT

ARRAY_ADDR .fill x4000
ARRAY_LEN  .fill 10

.end

.orig x4000
  .fill 7
  .fill 18
  .fill 0
  .fill 5
  .fill 9
  .fill 25
  .fill 1
  .fill 2
  .fill 10
  .fill 6
.end
