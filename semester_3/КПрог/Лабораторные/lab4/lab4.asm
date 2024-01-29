 org $8000
 ldx #$8200 ; јдрес первой €чейки первого блока
 ldaa #10   ; «аполнение A
 ldab #70   ; «аполнение B

; «аполнение €чеек числами
LoopFillCells 
 staa 0,x
 stab $20,x
 inca
 incb
 inx
 cpx #$821F  
 ble LoopFillCells ; пока x <= #$821F

 ;bra end
 ldx #$8200 ; јдрес первой €чейки первого блока

; ќбмен старших тетрад €чеек
LoopExhangeTetrad 
 ldaa 0,x
 staa $10
 bclr $10,%11110000
 ldaa $10 ; в A €чейка [0,x] с нул€ми в старшей тетраде

 ldab $20,x
 stab $10
 bclr $10,%00001111
 ldab $10 ; в B €чейка [$20,x] с нул€ми в младшей тетраде

 aba 
 staa $11 ; в $11 старша€ тетрада [$20,x], младша€ [0,x]


 ldaa $20,x
 staa $10
 bclr $10,%11110000
 ldaa $10 ; в A €чейка [$20,x] с нул€ми в старшей тетраде

 ldab 0,x
 stab $10
 bclr $10,%00001111
 ldab $10 ; в B €чейка [0,x] с нул€ми в младшей тетраде

 aba 
 staa $12 ; в $12 старша€ тетрада [0,x], младша€ [$20,x]


 ldaa $11
 staa 0,x ; €чейку $11 в [0,x]
 ldaa $12
 staa $20,x ; €чейку $12 в [$20,x]
 
 inx
 cpx #$821F 
 ble LoopExhangeTetrad ; пока x <= #$821F
;end