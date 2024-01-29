createFile MACRO name, id
    mov ah,3Ch       ; ������� DOS 3Ch (������� ����)
    mov cx,00100000b ; ������� �����
    mov dx,name      ; ����� ASCIZ-������ � ������ �����
    int 21h          ; ������� ����
    mov id,ax        ; ��������� ����������
endm
   
    .model tiny 
    
    .code
;org 80h         ; �������� 80h �� ������ PSP
;cmd_length db ? ; ����� ��������� ������
;cmd_line db ?   ; ���� ��������� ������

    org 100h ; ������ ��������� 100h �� ������ PSP
    
     
start:
   ; argc equ dw 0 ; ����� ����������  
    
    
    cld       ; ��� ������ ��������� ���������
    mov bp,sp ; ��������� ������� ������� ����� � BP
    
    mov cl,[80h] ; ������ ��������� ������
    cmp cl,1 ; �������� ����� ��������� ������
    jle exit ; ����� �� ���������
    
    ; ������������� ������ ���������� � PSP ���, �����
    ; ������ �������� ������������ ����� (ASCIZ-������)
    ; ������ ���� ���������� ��������� � ����
    ; � ���������� argc �������� ����� ����������
    
    mov cx,-1 ; ��� ������ ������ �� ��������
    mov di,81h ; ������ ��������� ������ � ES:DI
    
find_param:
    mov al,' '        ; AL = ������
    repz scasb        ; ������ �� ������
    dec di            ; DI = ����� ������ ��������� 
    push di           ; ��������� ����� � ����
    inc argc          ; ��������� argc �� 1
    mov si,di         ; SI = DI ��� ��������� ������� lodsb
    
scan_params:
    lodsb           ; ��������� ������ �� ���������
    cmp al,0Dh      ; ���� 0Dh � ��������� ��������
    je params_ended ; ��������� �����������
    cmp al,20h      ; ��������� � ��������
    jne scan_params ; ������� �������� �� ����������
    
    dec si               ; SI = ������ ���� ����� ���������
    mov [si],0  ; �������� � ���� 0
    mov di,si            ; DI = SI ��� ������� scasb
    inc di               ; DI = ��������� ����� ���� ������
     
    jmp find_param ; ���������� ������ ��������� ������
    
params_ended:
    ;=========================
    cmp [si-2],0
    jne cmdDontEndsWithEnter
    dec argc
    cmdDontEndsWithEnter:
    ;=========================
    dec si              ; SI = ������ ���� ����� ����� 
                        ; ���������� ���������
    mov byte ptr [si],0 ; �������� � ���� 0

    ; ������ � �����������
     
    ;continue: 
    ;createFile [offsetFileName],source_file_ID 
exit: 
    mov sp,bp 
 
    ret ; ����� ��������� 
   
    argc dw 0 ; ����� ����������  
    offsetFileName dw 0 ; �������� � PSP �� ���� � �����
    
    source_file_name db 'd:\data.txt',0 ; �������� ����
    source_file_ID   dw 0               ; ����������   
    
; ������ ���������

end start