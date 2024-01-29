
readChars MACRO id, number, buf 
    mov ah,3Fh    ; ������� DOS (������ �� �����)
    mov bx,id     ; �������� �����������
    mov cx,number ; ���������� ����������� ��������
    lea dx,buf    ; �������� ������ 
    int 21h       ; ������� ������    
endm

writeChars MACRO id, number, buf
    mov ah,40h    ; ������� DOS (������ � ����)
    mov bx,id     ; ����������
    mov cx,number ; ���������� ������������ ��������
    lea dx,buf    ; ����� 
    int 21h       ; �������� ������ 
endm


setCursor MACRO id, distance, type 
    mov ah,42h      ; ������� DOS (����������� ��������� ������/������)
    mov bx,id       ; �������������
    mov cx,0h       ;
    mov dx,distance ;
    mov al,type     ; ������������ ����
    int 21h         ; ����������� ���������  
endm

closeFile MACRO id
    mov bx,id  ; ����������
    mov ah,3Eh ; ������� DOS 3Eh
    int 21h    ; ������� ����
endm 

deleteFile MACRO name
    mov ah,41h  ; ������� DOS 41h (������� ����)
    lea dx,name ; ����� ASCIZ-������ � ������ ����� 
    int 21h     ; ������� ����
endm

createFile MACRO name, id
    mov ah,3Ch       ; ������� DOS 3Ch (������� ����)
    mov cx,00100000b ; ������� �����
    lea dx,name      ; ����� ASCIZ-������ � ������ �����
    int 21h          ; ������� ����
    mov id,ax        ; ��������� ����������
endm


openFile MACRO name, id
    lea dx,name ; ����� ASCIZ-������ � ������ �����
    mov ah,3Dh  ; ������� DOS 3Dh (������� ������������ ����)  
    mov al,02h  ; 02 - ��� ������ � ������
    int 21h     ; ������� ����    
    mov id,ax   ; ��������� ����������
endm

.code         

START: 
    
    mov ax,@data  ; @data - ������������� �������� ������
    mov ds,ax     ; ����� �������� ������ � � DS      
    mov es,ax     ; ����� �������� ������ � � ES      
    
    
    openFile source_file_name, source_file_ID            ; ������� �������� ���� 
    createFile temp_file_name,temp_file_ID               ; ������� ��������� ����  
    createFile destination_file_name,destination_file_ID ; ������� ���� � ����������� 

    mainWhile:
        
        ; ���������� ������ ��������
        readChars source_file_ID, buffer_dose, buffer  
        mov charsRead,ax
        
        ; ����� ������ 0Dh � ��������� ������
        mov cx,charsRead ; ���������� ��������� ��������   
        mov al,0Dh       ; ������ 0Dh 
        lea di,buffer    ; �������� ������
        repne scasb      ; ����������, ���� �� ����� 
        jz Exists0Dh     ; ZF = 1?  
        
        ; ��������, ���� ��� ������� 0Dh
        NotExists0Dh: 
        
            mov dx,charsRead           ; ����� �������� � ������ = 
            mov charsOfStringInDose,dx ; = ����� ��������� ��������
            mov isEndOfString,00h      ; ����� ������ ���
            
            ; ����� ������� NULL � ��������� ������
            mov cx,charsRead          ; ���������� ��������� ��������  
            mov al,0h                 ; ������ NULL
            lea di,buffer             ; �������� ������
            repne scasb               ; ����������, ���� �� �����
            jnz writeCharsInTempFile  ; ZF <> 0?
         
                ; ��������, ���� ���� ������ NULL
                dec charsOfStringInDose  ; charsOfStringInDose--   
                mov isEndOfString,01h    ; ����� ������
                mov isEndOfFile,01h      ; ����� �����
                jmp writeCharsInTempFile
                 
        ; ��������, ���� ���� ������ 0Dh
        Exists0Dh:
        
            ; ����������� ����� �������� ������ � ������
            ; charsOfStringInDose = charsRead - CX + 1   
            mov dx,charsRead 
            mov charsOfStringInDose,dx
            sub charsOfStringInDose,cx
            inc charsOfStringInDose
            mov isEndOfString,01h
        
            ; ���� ����� .. .. .. .. 0Dh, ������ �����������
            ; �� ���� � ������ �� ������ 0Ah
            mov bx,charsOfStringInDose
            mov buffer[bx-1],0Ah
        
        
        ; ������ �������� �� ��������� ����
        writeCharsInTempFile:  
        writeChars temp_file_ID,charsOfStringInDose,buffer 
        mov dx,charsOfStringInDose  ; charactersInString +=
        add charsInString,dx        ; += charOfStringInDose
        
        ; ���� ����� ������ ��� ���
        cmp isEndOfString,0h
        je notEndOfString
        
        ; ��������, ���� � ������ ���� ����� ������
        endOfString:
        
            ; ��������� ������� � source_file
            ; cursorOffset = -(charsRead - charsOfStringInDose) 
            mov bx,charsRead
            mov cursorOffset,bx
            mov bx,charsOfStringInDose
            sub cursorOffset,bx
            neg cursorOffset
            setCursor source_file_ID,cursorOffset,01h
             
             
             
            ; ��������, �������� �� ������ �� ����� ��� �������
            ; "�� ��������� �� ������ ������� �� ��������"
            setCursor temp_file_ID,00h,00h ; ������ �� ������ �����   
            mov dx,charsInString
            mov charsInStringCopy,dx
            mov dx,buffer_dose
            cmp charsInStringCopy,dx
            jbe skipCheckCycle
            
            ; ���� ��������� ��������
            checkCycle:
                readChars temp_file_ID buffer_dose, buffer ; ������� ������� 
                checkBufferMacro buffer_dose               ; ���������
                cmp contains,01h
                je resetTempfile
            
                mov dx,buffer_dose       ;
                sub charsInStringCopy,dx ; charsInStringCopy -= buffer_dose  
               
                mov dx,buffer_dose       ; ��������� charsInStringCopy    
                cmp charsInStringCopy,dx ; � buffer_dose 
            ja checkCycle                ; charsInStringCopy > buffer_dose? 
            
            ; charsInStringCopy <= buffer_dose 
            skipCheckCycle: 
            readChars temp_file_ID charsInStringCopy, buffer ; ������� �������
            checkBufferMacro charsInStringCopy               ; ���������
            cmp contains,01h
            je resetTempfile
            
            
            
            ; ��������� ������ �� temp_file � destination_file
            setCursor temp_file_ID,00h,00h ; ������ �� ������ �����  
            mov dx,buffer_dose             ;
            cmp charsInString,dx           ;
            jbe skipTransferCycle          ; charsInString <= buffer_dose?  
            
            ; ���� ��������� ������ ��������
            transferCycle:
                readChars temp_file_ID buffer_dose, buffer         ; ������� �������
                writeChars destination_file_ID buffer_dose, buffer ; �������� �������
               
                mov dx,buffer_dose   ;
                sub charsInString,dx ; charsInString -= buffer_dose  
               
                mov dx,buffer_dose   ; ��������� charsInString    
                cmp charsInString,dx ; � buffer_dose 
            ja transferCycle         ; charsInString > buffer_dose? 
            
            ; charsInString <= buffer_dose 
            skipTransferCycle:
            readChars temp_file_ID charsInString, buffer         ; ������� �������
            writeChars destination_file_ID charsInString, buffer ; �������� �������
            
            
            
            ; �������� ��������� ����
            resetTempfile:                                                      
            mov charsInString,0h           ; charsInString = 0 
            setCursor temp_file_ID,00h,00h ; ������ �� ������ �����

        ; ��������, ���� � ������ ��� ����� ������
        notEndOfString:
            mov isEndOfString,0h ; �� ����� ������
            cmp isEndOfFile,01h  ; ���������
        
    jne mainWhile ; ����� �����?
    

    ; ���������� ���������
    exit:
    closeFile temp_file_ID    ; ������� ��������� ����
    deleteFile temp_file_name ; ������� ��������� ����  
    
    mov ax,4C00h   ; 4C (����� �� ���������) � AH
                   ; 00 (�������� ���������) � AL 
    int 21h        ; ������� DOS "��������� ���������"  

; [���������] � ��������� � contains
; ���� �� ������� � ������ ������    
checkBuffer PROC near
    mov contains,0h 
    
    mov si,0h ; SI = 0 [�������]
    for1:
        mov dx,0h         ; DX = 0   
        mov dl,buffer[si] ; DX = ������� ������ �� ������ 
        push si           ; ���������� SI 
        
        mov si,0h         ; SI = 0 [�������] 
        for2:
            cmp dl,symbols[si] ; ��������� ������� �� ������ � 
            jne not_equals     ; �������� �� ������ ��������
            mov contains,01h   ; contains = 1 
            pop si             ; �������������� SP
            ret                ; ����� �� ���������
            
            ; �� �����
            not_equals:
            
            ; ������� ������ �� �����
            inc si               ; SI++
            cmp si,symbolsNumber ; ���������
        jb for2 ; if si < symbolsNumber
        
        pop si ; �������������� SI
        
        ; ������� ������ �� �����
        inc si                   ; SI++ 
        cmp si,bufferNumberCheck ; ���������
    jb for1 ; if si < bufferNumberCheck
    
    ret           
checkBuffer endp

; [������] � ���� �� ������� � ������ ������ 
checkBufferMacro MACRO number
    mov dx,number
    mov bufferNumberCheck,dx
    call checkBuffer 
endm 

.data  

    source_file_name db 'd:\data.txt',0 ; �������� ����
    source_file_ID   dw 0               ; ����������
    
    destination_file_name db 'd:\result.txt',0 ; ���� � �����������
    destination_file_ID dw 0                   ; ���������� 
     
    temp_file_name db 'd:\temp.txt',0 ; ��������� ����
    temp_file_ID   dw 0               ; ����������    
    
    buffer      db 100 DUP(0) ; ����� ������    
    buffer_dose dw 50d        ; ������ ������
    
    isEndOfFile   db 0 ; [bool] � ����� �� ����� 
    isEndOfString db 0 ; [bool] � ����� �� ������ 
    
    charsRead           dw 0 ; ������� ��������    
    charsOfStringInDose dw 0 ; �������� ������ � ������
    charsInString       dw 0 ; �������� � ������
    
    cursorOffset        dw 0 ; �������� �������
    
    symbols           db '0123456789' ; �������, ������� ���� �� ������
    symbolsNumber     dw 10           ; �� �����
    
    bufferNumberCheck dw 0 ; ���������� �������� �� ������ ��� ��������
    charsInStringCopy dw 0 ; �������� � ������ (�����)
    contains          db 0 ; [bool] � ���� �� � ������ charsOfStringInDose 
                           ; �������� �� buffer 1 �� �������� symbols 
.stack 100h     


end START     

