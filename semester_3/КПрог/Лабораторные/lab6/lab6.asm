; ����������� ������ [������]
printStr macro str
    mov ah,09h ; ����� ������� DOS   
    lea dx,str ; �������� str � DX   
    int 21h    ; 21 ����������     
endm

; ������ ������ [������]
enterStr macro str
    mov ah,0Ah  ; ������� DOS (������� ������ �������� �� STDIN � �����) 
    lea dx,str  ; �������� ������ � DX
    int 21h
endm  

; ������ � ������ ������������ ���������� �������� ��� ����� [������]
; [������� � ������ ���� �����]
setMaxEnterSymbols macro str,number
    lea di,str    ; �������� ������ � DI
    mov al,number ; ������������ ����� �������� ��� �����       
    stosb         ; AL � ES:DI
endm    
 


.model small ; ������ ������ (��� � 1 ��������, ������ � ���� � DGROUP)
.code        ; ������� ����  

; ������ ���������
START: 
     
    mov ax,@data  ; @data - ������������� �������� ������
    mov ds,ax     ; ����� �������� ������ � � DS      
    mov es,ax     ; ����� �������� ������ � � ES      
    
    printStrBySymbol testString,testrString_size
    printStr toNewLine
    printStr toNewLine
    
    ;=======================������=======================
    printStr string_rightFormat
    printStr sfind_rightFormat 
    printStr spaste_rightFormat
    printStr toNewLine
    ;=======================������=======================
    
    
    
    ;=======================1 ������=======================  
    STRING_1: 
    
    setMaxEnterSymbols string,string_maxSize
    printStr string_info 
    enterStr string
    formatStr string_size,string   
    
    cmp string_size,0h ; if string_size == 0
    jne STRING_2       ; ������ �� ������
    
    printStr toNewLine
    printStr strEmpty   
    printStr toNewLine
    jmp STRING_1
    ;=======================1 ������======================
     
     
    
    ;=======================2 ������=======================   
    STRING_2:
    
    setMaxEnterSymbols sfind,sfind_maxSize    
    printStr toNewLine
    printStr sfind_info 
    enterStr sfind
    formatStr sfind_size,sfind
     
    cmp sfind_size,0h ; if string_size == 0
    jne STRING_3      ; ������ �� ������   
    
    printStr toNewLine
    printStr strEmpty   
    jmp STRING_2
    ;=======================2 ������=======================
     
     
    
    ;=======================3 ������======================= 
    STRING_3:
    
    setMaxEnterSymbols spaste,spaste_maxSize   
    printStr toNewLine
    printStr spaste_info 
    enterStr spaste
    formatStr spaste_size,spaste     
    
    cmp spaste_size,0h ; if string_size == 0
    jne stringsNormal  ; ������ �� ������ 
    
    printStr toNewLine
    printStr strEmpty   
    jmp STRING_3
    ;=======================3 ������=======================
    


    ; � ���������� �������� ��� ���������
    stringsNormal:

     
    mov al,string_size
    sub al,sfind_size
    inc al
    mov temp,al ; temp = string_size - sfind_size + 1  
                ; �� ���� ������ ���� for
    mov si,0h   ; SI ��������� � ���� �������� i
    
    for:
        cmp si,0h            ; if i == 0   
        je wordBeginning     ; ���� ������ � ������ �����   
        cmp string[si-1],' ' ; if string[i-1]==' ' 
        je wordBeginning     ; ���� ������ � ������ �����
        jmp notWordBeginning ; ����� � �� ������ �����
  
        ; ������ � ������ ����� 
        wordBeginning:  
            mov bx,0h   
        
            mov bl,sfind_size       ; BX = sfind_size
            cmp string[bx][si], ' ' ; if string[i + sfind_size] == ' '
            je wordEnd              ; ���� ������ ����� ����� 
            
            ;===========================================================
            ;cmp string[bx][si], '$' ; if string[i + sfind_size] == '$'
            mov ax,bx
            add ax,si 
            cmp string_size,al ; ������ ��������� � ��������
            ;===========================================================
            
            je wordEnd              ; ���� ������ ����� ����� 
                                    ; [������ ���� �� �������]
            jmp notWordEnd          ; ����� � ������� ����� ����� ��� 
      
            ; ���� ������ ����� �����  
            wordEnd: 
                mov dx,0h
                mov dl,sfind         ; DX = sfind[0]
                cmp string[si],dl    ; if string[i] != sfind[0] 
                jne notSearchingWord ; ��� ����� � �� �������
       
                push si           ; ���������� SI 
                mov ax,si
                lea si,string
                add si,ax         ; � SI �������� �� string[i]   
                lea di,sfind      ; � DI �������� �� sfind[0]
                mov cx,0h
                mov cl,sfind_size ; � CX ������ �������� �����
       
                repe cmpsb   ; ���������� string � sfind ���� ��� �����
                             ; � ���� CX <> 0
                              
                pop si       ; �������������� SI
                jnz notEqual ; ���� ��������� �� ������ �� �����
       
                ; ��������, ���� ����� 
                mov place,al  ; � place ������, � �������� ���������� �����
                mov found,01h ; found = true
                jmp exitFor   ; ����� �� for
       
                ; ��������� �� ������ �� �����
                notEqual:
                
                ; ��� ����� � �� �������
                notSearchingWord: 
                  
            ; ��� ������� ����� �����
            notWordEnd:   
        
        ; ������ � �� ������ ����� 
        notWordBeginning:  
          
        inc si      ; SI++
        mov ax,si
        cmp al,temp ; �������� si � temp 
        
    jl for ; SI < tmp -> ��������� ��������
    ; ���� loopnz for
     
    ; ����� �� �����
    exitFor:        
    
    cmp found,01h ; if found == true
    je placeFound ; ����� �������  
    
    ; ��������, ���� ����� �� �������
    printStr toNewLine 
    printStr strPlaceNotFound
    jmp end
    
    ; ��������, ���� ����� �������
    placeFound:       
    
    mov al,string_size
    add al,spaste_size
    inc al
    mov new_string_size,al ; new_string_size = string_size + spaste_size + 1
     
    ; ���������� '$' � ����� (���������� ������) 
    lea di,string          ; �������� ������ � DI
    mov dh,0d
    mov dl,new_string_size ; DX = new_string_size
    add di,dx              ; DI += new_string_size
    mov al,'$'             ; ������ '$'    
    stosb                  ; AL ('$') � ES:DI  
    
    std ; DF = 1
    
    lea si,string  
    mov ax,0h
    mov al,string_size ; AX = string_size
    add si,ax   
    dec si             ; SI � �������� �� ��������� ������ 
                       ; ��������� ������ 
           
    lea di,string
    mov ax,0h
    mov al,new_string_size ; AX = new_string_size
    add di,ax
    dec di                 ; DI � �������� �� ��������� ������
                           ; ����������� ������ 
    
    ; ������������ ����� ��� ���������� �����    
    mov ax,0h
    mov al,new_string_size    
    dec al
    sub al,place
    mov cx,ax ; CX = new_string_size - 1 - place       
    rep movsb ; DS:SI � ES:DI ���� CX <> 0
    
    ; ������� ���������� �����
    cld ; DF = 0 
    
    lea si,spaste ; SI � �������� �� ������ ������
                  ; ������������ �����
                            
    lea di,string 
    mov ax,0h
    mov al,place
    add di,ax ; DI � �������� �� ����� ������ 
              ; ������� � string
    
    mov ax,0h
    mov al,spaste_size
    mov cx,ax ; CX = spaste_size  
    
    rep movsb ; DS:SI � ES:DI ���� CX <> 0
    
    ; ������� ������� ����� ���������� �����
    mov bx,0h
    add bl,place
    add bl,spaste_size ; BX = place + spaste_size
    mov string[bx],' ' ; string[place + spaste_size] = ' ' 
    
    ; ����� ����������
    printStr toNewLine 
    printStr strResult 
    ;printStr string
    printStrBySymbol string,new_string_size
    
    

    end:           ; ����� ���������
    
    mov ax,4C00h   ; 4C (����� �� ���������) � AH
                   ; 00 (�������� ���������) � AL 
    int 21h        ; ������� DOS "��������� ���������" 
    


; ���������� ����� ������ [���������]
; [2 ����, �������� �� ������� �� �� ��������]
calcSizeOfStr PROC near
    mov si,strGeneral_offset ; strGeneral_offset �������� �������� ������
    add si,01d               ; SI++
    lodsb                    ; DS:SI � AL
    mov strGeneral_size,al 
    
    
    mov dl,0h                ; ���������� ��������
    mov bx,0h                ; ������ � ����������� ������
    mov di,strGeneral_offset ; �������� ������

    while: 
        cmp [di+bx+2],' ' ; ��������� �������� ������� � ��������  
        jne notSpace
        inc dl
        
        notSpace:
        
        ; ������� ������ �� �����
        inc bl  
        cmp bl,strGeneral_size
    jl while
      
    cmp dl,strGeneral_size
    jne stringNotEmpty
    mov strGeneral_size,0h     
    
    stringNotEmpty:
    
    ret
calcSizeOfStr endp    


; ��������������� ������ [������]
; [������ ������ ��� �����, �������� '$', ��������� �����]
formatStr macro str_size,str   
    
    ; ���������� ����� ������  
    lea si,str      ; �������� str � SI
    mov strGeneral_offset,si  
    call calcSizeOfStr
    mov dl,strGeneral_size
    mov str_size,dl
    
    ; �������� ������ �� 2 �����
    lea di,str ; �������� str � DI
    mov si,di
    add si,02d ; SI = DI + 2
     
    mov CH,0h
    mov CL,str_size ; CX = str_size 
    rep movsb       ; ��������� DS:SI � ES:DI,
                    ; ���� CX <> 0   
                      
    ; ���������� '$' � �����  
    lea di,str      ; �������� ������ � DI
    mov dh,0d
    mov dl,str_size ; DX = str_size
    add di,dx       ; DI += str_size
    mov al,'$'      ; ������ '$'    
    stosb           ; AL � ES:DI 
    
endm   

; ����������� ������ ����������� [���������]
printStrBySymbolProc PROC near            
    
    mov ah,06h               ; �������� ������ � STDOUT
    
    mov di,strGeneral_offset ; �������� ������ 
    mov bx,0h                ; ������ � ��������� ������   
    
    mov dx,0h 
    mov dl,strGeneral_size
    mov cx,dx                ; ����� ������
    jcxz strIsEmpty          ; ���� ������ ������
    
    while1:
        mov dl,[di+bx]
        int 21h ; ����� �������� �������
        
        ; ������� ������ �� �����
        inc bx
        cmp bx,cx     
    jl while1    
    
    ; ������ ������       
    strIsEmpty:
    
    ret
    
printStrBySymbolProc endp 

; ����������� ������ ����������� [������]
printStrBySymbol macro str,str_size
    lea si,str
    mov strGeneral_offset,si
    
    mov dl,str_size
    mov strGeneral_size,dl
    
    call printStrBySymbolProc
endm

.data ; ������� ������   
    
    testString db '$$$ I am a $wizard$, I can $print$ dollars $$$'   
    testrString_size db 46d
    
    ; �������� ������ 
    string db 200 DUP(?)
    string_maxSize db equ 100  
    string_size db 0
    new_string_size db 0   
    string_rightFormat db '"Source string" - a sentence consisting of words separated by spaces',0Dh,0Ah,'$'
    string_info db 'Source string: $' 
    
     
    ; ������, ����� ������� ���������
    sfind db 200 DUP(?)
    sfind_maxSize db equ 20
    sfind_size db 0          
    sfind_rightFormat db '"Paste before"  - the word contained in "source string"',0Dh,0Ah,'$'
    sfind_info db 'Paste before:  $' 
    
    ; ������, ������� ���������
    spaste db 200 DUP(?)
    spaste_maxSize db equ 20
    spaste_size db 0 
    spaste_rightFormat db '"Pasting word"  - the word inserted into the sentence"',0Dh,0Ah,'$'   
    spaste_info db 'Pasting word:  $'
    
    ; ������ ��� �������� � ���������
    strGeneral_offset dw 0
    strGeneral_size db 0
    
    temp db 0   ; ��������� ����������               
    place db 0  ; ����� � ������, ��� ���������� �����
                ; ����� ������� ���� �������� 
    found db 0  ; bool, ������� �� �����          
    
    ; ������ ���� �� ����� �����, ����� ������� �������� 
    strPlaceNotFound db 'The word to insert before which was not found$' 
    
    strResult db 'Result:        $'        ; ���������   
    strEmpty db 'Entered string is empty$' ; ��������� ����� ������
    toNewLine db 0Ah, 0Dh, '$'             ; ������� �������� �� ����� ������ (v,<)     
    
.stack 100h     ; ������� ����� (256 ����)
    
end START   ; ����� ���������  

