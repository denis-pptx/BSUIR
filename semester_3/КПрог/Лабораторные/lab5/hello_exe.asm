; hello_exe.asm
    .model small    ; ������ ������ (��� � 1 ��������, ������ � ���� � DGROUP)
    .stack 100h     ; ������� ����� (256 ����)
    .code           ; ������� ����
start:
    mov ax,@data    ; @data - ������������� �������� ������
    mov ds,ax       ; ����� �������� ������ � � DS
    mov dx, offset message   ; ����� ������ � � DX 
    mov ah,9                ; ����� ������� DOS � � AH
    int 21h                 ; ������� DOS "����� ������"  
    mov dx,offset message2   ; ����� ������ � � DX    
    int 21h                 ; ������� DOS "����� ������"
    mov ax,4C00h    ; 4C (����� �� ���������) � AH, 00 (�������� ���������) � AL 
    int 21h         ; ������� DOS "��������� ���������"
    .data           ; ������� ������
message db "Hello World!",07h,0Dh,0Ah,'$' ; ������ ��� ������, 07h � �������� ������       
message2 db "Hello World 2 string!",07h,'$' ; ������ ��� ������, 07h � �������� ������
    end start   ; ����� ���������