;;====================================
;; CS 2110 - Fall 2018
;; Homework 7
;; buildheap.asm
;;====================================
;; Name: Peter Lee plee99
;;====================================

; Little reminder from your pals: don't run this directly by pressing
; ``Run'' in complx, since (look below) there's nothing put at address
; x3000. Instead, load it and use ``Debug'' -> ``Simulate Subroutine
; Call'' and choose the ``strlen'' label.

;arr fp + 4;
;n fp + 5;
;ifp + 6;

;void heapify(int[] arr, int n, int i) {
;int largest = i;               // Initialize largest as root 
;Int leftChild = 2*i + 1;       //left = 2*i + 1
;int rightChild = 2*i + 2;      // right = 2*i + 2;
;
;if (leftChild < n && arr[leftChild] > arr[largest])
;   largest = leftChild;;
;           //add 1 to the child address
;if (rightChild < n && arr[rightChild] > arr[largest])
;   largest = rightChild;
;
;if (largest != i) {
;   swap(arr[i], arr[largest]); // Recursively heapify the affected sub-tree 
;   heapify(arr, n, largest);
;}
;R0 address
;R1 child address
;R2 child val
;R3 largest
;r4 n (the size of arr)
.orig x3000

halt

heapify
;input
; [ implement heapify here ]

ADD R6, R6, -4 ;place stack pointer to build up first portion of the stack (a)
STR R7, R6, 2  ;save old return address
STR R5, R6, 1  ;save old frame pointer
ADD R5, R6, 0  ;set current frame pointer
ADD R6, R6, -5 ;place stack pointer to save all of the registers on the stack (b)
STR R0, R6, 4  ;save R0
STR R1, R6, 3  ;save R1
STR R2, R6, 2  ;save R2
STR R3, R6, 1  ;save R3
STR R4, R6, 0  ;save R4



ADD R2, R0, -1  ;r2 is n-1
BRnz BASE       ;check if n-1 is zero or neg
ADD R6, R6, -4  ;R6 will now point to one above R4
ADD R1, R0, -1  ;getting n-1

STR R4, R6, 4   ;store n    
STR R3, R6, 3   ;store largest addr
STR R2, R6, 2   ;store childval
STR R1, R6, 1   ;store child addr
STR R0, R6, 0   ;store parent addr
JSR heapify     ;recall subroutine

LDR R0, R6, 0  ;get address, param 1
LDR R1, R6, 1  ;n, param 2
LDR R2, R2, 2  ;i, param 3
LDR R3, R6, 3  ;largest, temp
LDR R4, R6, 4  ;child addr, temp
ADD R6, R6, 2  ;we want r6 to point to the top of the register stack


AND R3, R3, 0
ADD R3, R2, 0   ;SET LARGEST AS I

;do logics
AND R4, R4, 0
ADD R4, R2, R2
ADD R4, R4, 1  ;LEFT CHILD 2I+1

NOT R4, R4
ADD R4, R4, 1
IF11 ADD R2, R2, R4     ;check if leftchild < n (N-child1)
    BRN ENDIF1

AND R4, R4, 0
ADD R4, R2, R2
ADD R4, R4, 1           ;LEFT CHILD 2I+1
;if1
    ADD R4, R4, R0  ;GET ACTUAL ADDRESS
    LDR R4, R4, 0   ;GET VAL AT CHILD1
    NOT R4, R4
    ADD R4, R4, 1   ;-CHILD1VAL

    ADD R3, R3, R0  ;GET LARGEST ADDR
    LDR R3, R3, 0   ;LOAD VAL AT ADDR

    ADD R4, R4, R3 (LARGE - CHILD)
    BRNZ ENDIF1
    AND R4, R4, 0
    ADD R4, R2, R2
    ADD R4, R4, 1           ;LEFT CHILD 2I+1
ENDIF1

AND R4, R4, 0
ADD R4, R2, R2
ADD R4, R2, 2  ;RIGHT CHILD 2I+2

NOT R4, R4
ADD R4, R4, 1
IF21 ADD R4, R4, R1    ;check if rightchild < n (n-child2)
    BRN ENDIF2

AND R4, R4, 0
ADD R4, R2, R2
ADD R4, R2, 2  ;RIGHT CHILD 2I+2
;if2
    ADD R4, R4, R0  ;GET ACTUAL ADDRESS
    LDR R4, R4, 0   ;GET VAL AT CHILD1
    NOT R4, R4
    ADD R4, R4, 1   ;-CHILD1VAL

    ADD R3, R3, R0  ;GET LARGEST ADDR
    LDR R3, R3, 0   ;LOAD VAL AT ADDR

    ADD R4, R4, R3 (LARGE - CHILD)
    BRNZ ENDIF2
    AND R3, R3, 0;  largest = child1
    ADD R3, R2, R2
    ADD R3, R3, 2
ENDIF2

;SWAPPING TIMEEEEE
;if (largest != i) {
;   swap(arr[i], arr[largest]); // Recursively heapify the affected sub-tree 
;   heapify(arr[0], n[1], largest(NEW I));
;}

AND R4, R4, 0
NOT R4, R3
ADD R4, R4, 
ADD R4, R4, R2  (I-LARGEST)
BRZ NOSWAP
    AND R4, R4, 0
    ADD R4, R3, R0  ;R3 IS NOW LARGE ADDRESS
    LDR R4, R3, 0   ;SAVE R3 VALUE IN R4
    ADD R1, R0, R1  ;R1 IS NOW I ADDRESS
    AND R0, R0, 0
    LDR R0, R4, 0
    STR R4, R3, 0
    STR R1, R0, 0
NOSWAP

    

BR STACK_BREAKDOWN
BASE
AND R0, R0, 0
STR R0, R5, 3  ;place the return value in the return value place of the stack
BR STACK_BREAKDOWN

;keep building stack until you cant then tear down.
STACK_BREAKDOWN
LDR R4, R5, -5 ;restore R4
LDR R3, R5, -4 ;restore R3
LDR R2, R5, -3 ;restore R2
LDR R1, R5, -2 ;restore R1
LDR R0, R5, -1 ;restore R0
ADD R6, R5, 0  ;bring R6 back down to R5
LDR R5, R6, 1  ;restore old frame pointer
LDR R7, R6, 2  ;restore return address
ADD R6, R6, 3  ;have R6 point to the return value
RET



buildheap

; [ implement buildheap here ]


; Needed by Simulate Subroutine Call in complx
STACK .fill xF000
.end

; You should not have to LD from any label, take the
; address off the stack instead :)
