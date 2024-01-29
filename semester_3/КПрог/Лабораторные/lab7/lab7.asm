; ����������� ������ [������]
printStr macro str
    push ax
    push dx
    
    mov ah,09h ; ����� ������� DOS   
    lea dx,str ; �������� str � DX   
    int 21h    ; 21 ����������
    
    pop dx
    pop ax     
endm
 
; ����������� ������ [������]
printSymb macro ascii 
   mov ah,06h
   mov dl,ascii
   int 21h 
endm

; ������ ������ (��� � 1 ��������, ������ � ���� � DGROUP)
.model small  

; ������� ���� 
.code         

; ������ ���������
START: 
    
    mov ax,@data  ; @data - ������������� �������� ������
    mov ds,ax     ; ����� �������� ������ � � DS      
    mov es,ax     ; ����� �������� ������ � � ES      
   
    
    ;===================������ � $$$===================
    printStrBySymbol testString,testrString_size
    printStr toNewLine
    printStr toNewLine
    ;==================================================
     
     
    ;====������� ������������ ����� ��� ��������� �����======
    lea di,strNumber ; �������� ������ � DI
    mov al,06d       ; ������������ ����� �������� ��� �����      
    stosb            ; AL � ES:DI 
    ;========================================================
    
    
    ;==============����� "����� ������ ������"===============
    printStr strFormat
    printStr toNewLine
    printStr toNewLine
    ;========================================================
    
    
    ;====================���� ���������======================  
    printStr strRange
    
    
RANGE_INPUT: 
    
 
    printStr toNewLine  
    printStr strRangeFormat
    
    ; �������� ��
    printStr toNewLine 
    mov needPrintFrom, 1h  
    mov needPrintTo, 0h 
    
    call enterNumber
    mov dx,number
    mov numberFrom,dx
    
    ; �������� ��
    mov needPrintFrom, 0h  
    mov needPrintTo, 1h 
    
    printStr toNewLine
    call enterNumber
    mov dx,number
    mov numberTo,dx 
    
     
    
    mov ax,numberFrom
    mov bx,numberTo
    cmp ax,bx
    ja RANGE_INPUT
    ;===========================================================  
    
     
    ;===============������� ����� � ������ ������?==============
    ask:
    printStr toNewLine
    mov needPrintFrom, 0h  
    mov needPrintTo, 0h 
    printStr strAskSymbolsAmount
    printStr toNewLine
    call enterNumber
    mov dx,number 
    mov array_size,dx
    
    cmp array_size,30d
    ja ask
    
    cmp array_size,0h
    jz ask
    ;===============������� ����� � ������ ������?==============
    
     
    ;===================���������� �������=================== 
    mov needPrintFrom, 0h  
    mov needPrintTo, 0h 
    
    printStr toNewLine   
    printStr toNewLine
    printStr strEnterArray
    printNumber array_size
    printStr toNewLine
     
    
    mov cx,array_size ; CX = array_size 
    lea si,array      ; SI �� ������ �������  
    
    mov numberOfNumber,1d
    mov needNumberOfNumber,1d
    
    inputWhile:
    
        push cx ; ��������� CX
        push si ; ��������� SI
        
        call enterNumber 
        printStr toNewLine
        
        pop si ; ������������ SI     
        pop cx ; ������������ CX
        
        ; ����� ������������� ��������   
        
        ; ���� 0 �������, �� ��� � ������������
        cmp number,0h
        je new_max
        
        mov dx,max_item
        cmp number,dx 
        jbe not_new_max ; if number <= max_item
        
        ; ������� ������� ����� ������������ (��������) 
        mov ax,number
        cmp ax,numberFrom
        jb not_new_max
        
        mov ax,number
        cmp ax,numberTo
        ja not_new_max
        
        ; ����� ������������ 
        new_max:
        mov dx,number
        mov max_item,dx
        mov existsMaxItemFromRange,01h  
        
        ; ������� ������� �� ����� ������������
        not_new_max:
        
        mov dx,number
        mov [si],dx  ; �������� ����� � ������
        add si,2d
       
        inc numberOfNumber
         
        ; ������� ������ �� �����
        dec cx  
        cmp cx,0d
 
    jnz inputWhile
    ;========================================================
     
     
    ;======���� �� ������� ���� �� 1 ����� �� ���������======
    cmp existsMaxItemFromRange,0h
    je noNumbersFromRange
    ;========================================================
    
    
    ;=================��������� �����������==================
    mov cx,0h    ; CX = 0, ������� for � symbolsOutput
    lea si,array ; SI �� ������ �������
    printStr toNewLine
    for:
        mov ax,[si] ; AX = ������� ������� �������
        
        
        ;=========��������, �� ��������� �� ��=========
        cmp ax,numberFrom
        jb notFromRange
        
        cmp ax,numberTo
        ja notFromRange
        ;==============================================
        
        
        ;=========��������, 0 �� ������� �����=========
        cmp ax,0h
        je startPrintSymbols ; ������ ������ �������
        ;==============================================
        
        
        ;======������� ����� �������� ��� �������====== 
        mov dx,0h
        mul max_symb
        div max_item ; AX = ����� �������� ��� �������
        ;============================================== 
        
        
        ;================����� ��������================ 
        startPrintSymbols:
        
        printStr symbStart ; ������� ������ ��������    
        
        push cx
        mov cx,ax 
        jcxz noSymbols 
        
        symbolsOutput:
            printStr symb  
            
            ; ������� ���������� �����
            dec cx
            cmp cx,0h
        jnz symbolsOutput 
        
        noSymbols:
        
        printSymb ' '
        printSymb '['
        printNumber [si] 
        printSymb ']'
        ;=============================================== 
        
        pop cx 
        printStr toNewLine
        
        notFromRange: 
        
        add si,2d 
        
        ; ������� ���������� ����� 
         
        inc cx
        cmp cx,array_size
    jnz for
    ;=================��������� �����������==================
    
    
    jmp end 
    
    
    ;=================��� ����� �� ���������==================
    noNumbersFromRange:
    
    printStr toNewLine
    printStr strNoNumbersFromRange
    ;=========================================================
      
      
    ;====================����� ���������====================
    end:
    mov ax,4C00h   ; 4C (����� �� ���������) � AH
                   ; 00 (�������� ���������) � AL 
    int 21h        ; ������� DOS "��������� ���������" 
    ;=======================================================
    
; ��������� � ���� �����
; [��������� ��������� � number]    
enterNumber proc near
    
    enterNumberProcStart: 
    
    ; ���� �� �������� "from" 
    fromCheck:
    cmp needPrintFrom,0h
    je toCheck
    printStr strFrom
    
    ; ���� �� �������� "to"
    toCheck:
    cmp needPrintTo,0h
    je numberOfNumberCheck
    printStr strTo
    
    ; ���� �� �������� ����� ����� � �������    
    numberOfNumberCheck:
    cmp needNumberOfNumber,0h
    je dontPrint
     
    printNumber numberOfNumber
    printSymb ')'
    printSymb ' '
    
    dontPrint:
     
    ; ���� ����� � ������
    mov ah,0Ah        ; ������� DOS (������� ������ �������� �� STDIN � �����) 
    lea dx,strNumber  ; �������� ������ � DX
    int 21h   
    
    ; ���������� ����� ���������� �����
    lea si,strNumber      ; �������� strNumber � SI
    add si,01d            ; SI++  
    mov ax,0h             ; �������� AX
    lodsb                 ; DS:SI � AL   
    mov cx,ax             ; CX = ����� ���������� �����
         
    ; ����� ���������� ����� 0
    cmp cx,0h
    jz strInvalid
      
    mov number,0h  ; ����� ����� ������������� � number    
    mov ax,01d ; AX � ������� �������
    
    while:
        mov bx,0h    
        mov si,cx
        add si,01d ; SI � �������� �� ������� ������ �����
        mov bl,strNumber[si] ; BX � ASCII ��� �������� �������
        
        ; �������� �� ��, �������� �� ������ ������ 0..9
        cmp bl,48d
        jl strInvalid; < 48
        cmp bl,57d
        jg strInvalid; > 57
        
        sub bl,48d ; BX = ������� �����
        
        push ax  ; ���������� AX    
        
        clc           ; �������� ���� ��������
        mul bx        ; AX = ������� ����� * 10 � ������� 
        jc overflow   ; ���� ���� ���� �������� �� mul 
        add number,ax ; ��������� ��� � ����������� �����
        jc overflow   ; ���� ���� ���� �������� �� add
        
        pop ax        ; �������������� AX
        
        mul ten ; AX *= 10
        
        ; ������� ������ �� �����
        dec cx  
        cmp cx,0
    jne while                    
    
    ret
    
    ; ������������
    overflow:
    pop ax ; ����� ������� SP �� IP

    printStr toNewLine
    printStr strOverflow
    printStr toNewLine
    printStr strRepeat
    printStr toNewLine
    jmp enterNumberProcStart
    ret  
    
    ; ���������� ������  
    strInvalid:

    printStr toNewLine
    printStr strInvalidFormat
    printStr toNewLine
    printStr strRepeat
    printStr toNewLine
    jmp enterNumberProcStart
    ret
    
    
enterNumber endp    

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


; ����������� ����� [���������]
printNumberProc PROC near
    
    mov cx,0h ; ���������� ���� � �����
    
    ; ���������� ���� � ���
    pushDigitsWhile:
        mov dx,0h
        mov ax,numberGeneral ; AX = �����
        div ten              ; DX:AX / ten = DX:AX
   
        mov numberGeneral,ax ; numberGeneral ��� /= 10

        add dx,48d ; DX += 48 (������� � ASCII)
        push dx ; DX = ������� ����� �����
        
        inc cx ; CX ++  
        
        ; ������� ������ �� �����
        cmp numberGeneral,0h
    jne pushDigitsWhile 
    
    ; ���������� �� ����� � ������ ����
    printDigitsWhile: 
        mov dx,0h
        mov ax,numberGeneral ; AX = �����
        div ten              ; DX:AX / ten = DX:AX
   
        mov numberGeneral,ax ; numberGeneral ��� /= 10

        ; ����� ����� DX 
        ; ���������� ����� ASCII ������� �� DL
        pop dx
        mov ah,06h
        int 21h
        
        
        ; ������� ������ �� �����  
        dec cx
        cmp cx,0h
    jne printDigitsWhile 
  
    ret
printNumberProc endp

; ����������� ����� [������]
printNumber macro digit
    push ax
    
    mov ax,digit 
    mov numberGeneral,ax
    call printNumberProc 
    
    pop ax
endm  


; ������� ������  
.data  
   testString db '$$$ I am a $wizard$, I can $print$ dollars $$$'   
   testrString_size db 46d  
   
   ; ���� �����
   strNumber db 10 DUP(?) ; ������, � ������� ������ �����
   number dw 0d           ; ��������� ����� (�������������)   
   strFormat db 'Enter non-negative hexadecimal numbers in',0Dh,0Ah,'the decimal notation separated by an enter$'
   strOverflow db 'Entered number is more than 65535$'    
   strInvalidFormat db 'Entered number is invalid$'
   strRepeat db 'Enter number in correct format again$'
   ;isValidNumber db 01d  
   ten dw 10d 
   numberOfNumber dw 0d; ����� ����� � �������
   needNumberOfNumber db 0h ; bool, �������� �� ����� �����
   
   
   ; ������
   array_size dw 10   ; ����������� ����� ��������� �������
   array dw 40 DUP(?) ; ������ ����� 
   max_item dw 0      ; ������������ ������� �������
   existsMaxItemFromRange db 0 
   strEnterArray db 'Enter array of values: $' 
   
   strAskSymbolsAmount db 'How many numbers would you like to enter [min: 1, max: 30]?$'
   
   ; �����������
   max_symb dw 50d       ; ������������ ���������� �������� ��� �����������
   symb db '#$'          ; ������ ��� ���������� �������� 
   symbStart db '> $' ; ������ ��� ������ �������� 
   
   ; �������� 
   numberFrom dw 0
   numberTo dw 0
   strRange db 'Build histogram for numbers$'
   strFrom db 'from: $'
   strTo db 'to:   $'
   strRangeFormat db '"from" must be <= "to"$'
   strNoNumbersFromRange db 'Not a single number from the range has been entered$'
   needPrintFrom db 0h
   needPrintTo db 0h
   
   ; ������� �������� �� ����� ������ (v,<)    
   toNewLine db 0Ah, 0Dh, '$' 
   
   ; ������ ��� �������� � ���������
   strGeneral_offset dw 0
   strGeneral_size db 0
   
   ; ����� ��� �������� � ���������
   numberGeneral dw 0
   
; ������� ����� (256 ����)      
.stack 100h     

; ����� ���������    
end START     

