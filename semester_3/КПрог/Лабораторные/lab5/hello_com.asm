; hello_com.asm
    .model tiny     ; ������ ������ (���, ������ � ���� � 1 ��������)
    .code           ; ������� ����
    org 100h        ; ��������� �������� IP
start:
    mov ah,9                ; ����� ������� DOS - � AH
    mov dx,offset message   ; ����� ������ � � DX
    int 21h                 ; ����� ��������� ������� DOS
    ret                     ; ���������� COM-��������� (�������� ���������� ������� � DOS)
message db "Hello World!",07h,'$' ; ������ ��� ������, 07h � �������� ������
end start                         ; ����� ���������