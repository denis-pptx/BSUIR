 org $8000
 ldx #$8200 ; ����� ������ ������ ������� �����
 ldaa #10   ; ���������� A
 ldab #70   ; ���������� B

; ���������� ����� �������
LoopFillCells 
 staa 0,x
 stab $20,x
 inca
 incb
 inx
 cpx #$821F  
 ble LoopFillCells ; ���� x <= #$821F

 ;bra end
 ldx #$8200 ; ����� ������ ������ ������� �����

; ����� ������� ������ �����
LoopExhangeTetrad 
 ldaa 0,x
 staa $10
 bclr $10,%11110000
 ldaa $10 ; � A ������ [0,x] � ������ � ������� �������

 ldab $20,x
 stab $10
 bclr $10,%00001111
 ldab $10 ; � B ������ [$20,x] � ������ � ������� �������

 aba 
 staa $11 ; � $11 ������� ������� [$20,x], ������� [0,x]


 ldaa $20,x
 staa $10
 bclr $10,%11110000
 ldaa $10 ; � A ������ [$20,x] � ������ � ������� �������

 ldab 0,x
 stab $10
 bclr $10,%00001111
 ldab $10 ; � B ������ [0,x] � ������ � ������� �������

 aba 
 staa $12 ; � $12 ������� ������� [0,x], ������� [$20,x]


 ldaa $11
 staa 0,x ; ������ $11 � [0,x]
 ldaa $12
 staa $20,x ; ������ $12 � [$20,x]
 
 inx
 cpx #$821F 
 ble LoopExhangeTetrad ; ���� x <= #$821F
;end