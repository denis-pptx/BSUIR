 org $8000

 ldx #0 ; ��������� X

 ldab $8000 ; �������� � B
 abx        ; �������� B � X

 ; ����� ��� 4 ������ ��������

 ldab $8001
 abx

 ldab $8002
 abx

 ldab $8003
 abx

 ldab $8004
 abx

 ; ���� - � X ����� ����� $8000..$8004
 ldx #$4781

 stx $8120 ; ��� �������� X

 ; D / X -> X (��� B)

 xgdx
 ldx #$10
 idiv ; � B ������ 0 �������
 pshb

 ldd $8120 ; � D ������ ��� ����� X
 ldaa #0
 ldx #$10
 idiv
 xgdx ; � B ������ 1 �������
 pshb

 ldd $8120 ; � D ������ ��� ����� X
 ldab #0
 ldx #$1000
 idiv ; � A ������ 2 �������
 psha

 ldd $8120 ; � D ������ ��� ����� X
 ldab #0
 ldx #$1000
 idiv
 xgdx ; � B ������ 3 �������
 pshb
 