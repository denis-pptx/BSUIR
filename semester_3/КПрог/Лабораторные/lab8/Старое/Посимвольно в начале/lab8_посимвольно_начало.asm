
readCharacters MACRO id, number, buf 
    mov ah,3Fh    ; ������� DOS (������ �� �����)
    mov bx,id     ; �������� �����������
    mov cx,number ; ���������� ����������� ��������
    lea dx,buf    ; �������� ������ 
    int 21h       ; ������� ������    
endm

writeCharacters MACRO id, number, buf
    mov ah,40h    ; ������� DOS (������ � ����)
    mov bx,id     ; ����������
    mov cx,number ; ���������� ������������ ��������
    lea dx,buf    ; ����� 
    int 21h       ; �������� ������ 
endm

setCursorAtZero MACRO id
    mov ah,42h ; ������� DOS (����������� ��������� ������/������)
    mov bx,id  ; �������������
    mov cx,0h  ;
    mov dx,0h  ;
    mov al,0h  ; �� 0 ������������ ������
    int 21h    ; ����������� ���������  
endm

.code         

START: 
    
    mov ax,@data  ; @data - ������������� �������� ������
    mov ds,ax     ; ����� �������� ������ � � DS      
    mov es,ax     ; ����� �������� ������ � � ES      
    
    ; �������� ��������� �����
    lea dx,source_file_name ; ����� ASCIZ-������ � ������ �����
    mov ah,3Dh              ; ������� DOS 3Dh (������� ������������ ����)
    mov al,00h              ; 00 - ������ ��� ������
    int 21h                 ; ������� ����    
    jc exit                 ; ���� ������ � �����
    mov source_file_ID,ax   ; ��������� ����������
     
    ; �������� ����� ����������
    ;lea dx,destination_file_name ; ����� ASCIZ-������ � ������ �����
    ;mov ah,3Dh                   ; ������� DOS 3Dh (������� ������������ ����)
    ;mov al,01h                   ; 1 - ������ ��� ������
    ;int 21h                      ; ������� ����    
    ;jc exit                      ; ���� ������ � �����
    ;mov destination_file_ID,ax   ; ��������� ����������
    
    ; ������� ���� (����� ��������� � ���� ����������)
    mov ah,3Ch            ; ������� DOS 3Ch (������� ����)
    mov cx,00100000b      ; ������� �����
    lea dx,temp_file_name ; ����� ASCIZ-������ � ������ �����
    int 21h               ; ������� ����
    mov temp_file_ID,ax   ; ��������� ����������
    
    ; �������� ����� ����������
    mov ah,3Ch            ; ������� DOS 3Ch (������� ����)
    mov cx,00100000b      ; ������� �����
    lea dx,destination_file_name ; ����� ASCIZ-������ � ������ �����
    int 21h               ; ������� ����
    mov destination_file_ID,ax   ; ��������� ����������
    

    
    mainWhile:
        

        readCharacters source_file_ID, 01h, buffer
         
        ;cmp ax,0h ; ���� ������� 0 �������� => ���� ���������� 
        ;jne notEndOfFile
        cmp buffer,0h ; buffer = 0 => ���� ���������� 
        jne notEndOfFile
        
         
        endOfFile:
        
        mov buffer,00h
        writeCharacters temp_file_ID, 01h, buffer 
        

        setCursorAtZero temp_file_ID ; �������������
 
        transferString_end:
            readCharacters temp_file_ID, 01h, buffer
            cmp buffer,00h
            je endMainWhile
            writeCharacters destination_file_ID, 01h, buffer
    
            
        jne transferString_end
        
        jmp endMainWhile
        
        
       
        
        notEndOfFile:
        
        cmp buffer,0Dh ; ������ 0Dh => ����� ������
        jne notEndOfString
        
        endOfString: 
        
        ; 0Dh
        writeCharacters temp_file_ID, 01h, buffer
    
        ; 0Ah
        readCharacters source_file_ID, 01h, buffer
        writeCharacters temp_file_ID, 01h, buffer 
    

        setCursorAtZero temp_file_ID 

        transferString:
            readCharacters temp_file_ID, 01h, buffer
            writeCharacters destination_file_ID, 01h, buffer
    
            cmp buffer,0Ah
        jne transferString

        
        ; ������� ���� (����� ��������� � ���� ����������)
        mov ah,3Ch            ; ������� DOS 3Ch (������� ����)
        mov cx,00100000b      ; ������� �����
        lea dx,temp_file_name ; ����� ASCIZ-������ � ������ �����
        int 21h               ; ������� ����
        mov temp_file_ID,ax   ; ��������� ����������
      
        jmp mainWhile
        
        notEndOfString:
        writeCharacters temp_file_ID, 01h, buffer
    
    jmp mainWhile
    
    endMainWhile:
    
    ; �������� �����
close_file:  
    mov bx,destination_file_ID
    mov ah,3Eh ; ������� DOS 3Eh
    int 21h    ; ������� ����

    ; ���������� ���������
exit:
    mov ax,4C00h   ; 4C (����� �� ���������) � AH
                   ; 00 (�������� ���������) � AL 
    int 21h        ; ������� DOS "��������� ���������"  
    
.data  

    source_file_name db 'd:\data.txt',0 ; �������� ����
    source_file_ID   dw 0               ; ����������
    
    destination_file_name db 'd:\result.txt',0 ; ���� � �����������
    destination_file_ID dw 0                   ; ���������� 
     
    temp_file_name db 'd:\temp.txt',0 ; ��������� ����
    temp_file_ID   dw 0               ; ����������    
    
    ;buffer db 100 DUP(0) ; ����� ������    
    buffer db 0
    
    characters db 'abc'
    
    isEndOfFile db 0 ; bool
.stack 100h     


end START     

