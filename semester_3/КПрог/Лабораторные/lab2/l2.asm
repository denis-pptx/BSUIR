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

 txs ; ��������� X � SP
 ; ���������� SP �� 7
 psha
 psha
 psha
 psha
 psha
 psha
 psha
 tsx ; ��������� SP � X

 pshx ; �������� X � ����
  
 