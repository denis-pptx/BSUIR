; Распечатать строку [Макрос]
printStr macro str
    mov ah,09h ; Номер функции DOS   
    lea dx,str ; Смещение str в DX   
    int 21h    ; 21 прерывание     
endm

; Ввести строку [Макрос]
enterStr macro str
    mov ah,0Ah  ; Функция DOS (считать строку символов из STDIN в буфер) 
    lea dx,str  ; Смещение строки в DX
    int 21h
endm  

; Задать в строке макисмальное количество символов для ввода [Макрос]
; [Занести в первый байт число]
setMaxEnterSymbols macro str,number
    lea di,str    ; Смещение строки в DI
    mov al,number ; Максимальное число символов для ввода       
    stosb         ; AL в ES:DI
endm    
 


.model small ; Модель памяти (код в 1 сегменте, данные и стек в DGROUP)
.code        ; Сегмент кода  

; Начало прогарммы
START: 
     
    mov ax,@data  ; @data - идентификатор сегмента данных
    mov ds,ax     ; Адрес сегмента данных — в DS      
    mov es,ax     ; Адрес сегмента данных — в ES      
    
    printStrBySymbol testString,testrString_size
    printStr toNewLine
    printStr toNewLine
    
    ;=======================ФОРМАТ=======================
    printStr string_rightFormat
    printStr sfind_rightFormat 
    printStr spaste_rightFormat
    printStr toNewLine
    ;=======================ФОРМАТ=======================
    
    
    
    ;=======================1 СТРОКА=======================  
    STRING_1: 
    
    setMaxEnterSymbols string,string_maxSize
    printStr string_info 
    enterStr string
    formatStr string_size,string   
    
    cmp string_size,0h ; if string_size == 0
    jne STRING_2       ; строка не пустая
    
    printStr toNewLine
    printStr strEmpty   
    printStr toNewLine
    jmp STRING_1
    ;=======================1 СТРОКА======================
     
     
    
    ;=======================2 СТРОКА=======================   
    STRING_2:
    
    setMaxEnterSymbols sfind,sfind_maxSize    
    printStr toNewLine
    printStr sfind_info 
    enterStr sfind
    formatStr sfind_size,sfind
     
    cmp sfind_size,0h ; if string_size == 0
    jne STRING_3      ; строка не пустая   
    
    printStr toNewLine
    printStr strEmpty   
    jmp STRING_2
    ;=======================2 СТРОКА=======================
     
     
    
    ;=======================3 СТРОКА======================= 
    STRING_3:
    
    setMaxEnterSymbols spaste,spaste_maxSize   
    printStr toNewLine
    printStr spaste_info 
    enterStr spaste
    formatStr spaste_size,spaste     
    
    cmp spaste_size,0h ; if string_size == 0
    jne stringsNormal  ; строка не пустая 
    
    printStr toNewLine
    printStr strEmpty   
    jmp STRING_3
    ;=======================3 СТРОКА=======================
    


    ; С введенными строками все нормально
    stringsNormal:

     
    mov al,string_size
    sub al,sfind_size
    inc al
    mov temp,al ; temp = string_size - sfind_size + 1  
                ; до куда пойдет цикл for
    mov si,0h   ; SI выступает в роли счетчика i
    
    for:
        cmp si,0h            ; if i == 0   
        je wordBeginning     ; Этот символ – начало слова   
        cmp string[si-1],' ' ; if string[i-1]==' ' 
        je wordBeginning     ; Этот символ – начало слова
        jmp notWordBeginning ; Иначе – не начало слова
  
        ; Символ – начало слова 
        wordBeginning:  
            mov bx,0h   
        
            mov bl,sfind_size       ; BX = sfind_size
            cmp string[bx][si], ' ' ; if string[i + sfind_size] == ' '
            je wordEnd              ; Есть символ конца слова 
            
            ;===========================================================
            ;cmp string[bx][si], '$' ; if string[i + sfind_size] == '$'
            mov ax,bx
            add ax,si 
            cmp string_size,al ; Вместо сравнения с долларом
            ;===========================================================
            
            je wordEnd              ; Есть символ конца слова 
                                    ; [сейчас ушел от доллара]
            jmp notWordEnd          ; Иначе – символа конца слова нет 
      
            ; Есть символ конца слова  
            wordEnd: 
                mov dx,0h
                mov dl,sfind         ; DX = sfind[0]
                cmp string[si],dl    ; if string[i] != sfind[0] 
                jne notSearchingWord ; Это слово – не искомое
       
                push si           ; Сохранение SI 
                mov ax,si
                lea si,string
                add si,ax         ; В SI смещение на string[i]   
                lea di,sfind      ; В DI смещение на sfind[0]
                mov cx,0h
                mov cl,sfind_size ; в CX размер искомого слова
       
                repe cmpsb   ; Сравниваем string и sfind пока они равны
                             ; и пока CX <> 0
                              
                pop si       ; Восстановление SI
                jnz notEqual ; Если подстрока со словом не равны
       
                ; Действие, если равны 
                mov place,al  ; В place индекс, с которого начинается слово
                mov found,01h ; found = true
                jmp exitFor   ; Выход из for
       
                ; Подстрока со словом не равны
                notEqual:
                
                ; Это слово – не искомое
                notSearchingWord: 
                  
            ; Нет символа конца слова
            notWordEnd:   
        
        ; Символ – не начало слова 
        notWordBeginning:  
          
        inc si      ; SI++
        mov ax,si
        cmp al,temp ; Сравнить si с temp 
        
    jl for ; SI < tmp -> следующая итерация
    ; было loopnz for
     
    ; Выход из цикла
    exitFor:        
    
    cmp found,01h ; if found == true
    je placeFound ; Место найдено  
    
    ; Действие, если место не найдено
    printStr toNewLine 
    printStr strPlaceNotFound
    jmp end
    
    ; Действие, если место найдено
    placeFound:       
    
    mov al,string_size
    add al,spaste_size
    inc al
    mov new_string_size,al ; new_string_size = string_size + spaste_size + 1
     
    ; Добавление '$' в конец (расширение строки) 
    lea di,string          ; Смещение строки в DI
    mov dh,0d
    mov dl,new_string_size ; DX = new_string_size
    add di,dx              ; DI += new_string_size
    mov al,'$'             ; Символ '$'    
    stosb                  ; AL ('$') в ES:DI  
    
    std ; DF = 1
    
    lea si,string  
    mov ax,0h
    mov al,string_size ; AX = string_size
    add si,ax   
    dec si             ; SI – смещение на последний символ 
                       ; введенной строки 
           
    lea di,string
    mov ax,0h
    mov al,new_string_size ; AX = new_string_size
    add di,ax
    dec di                 ; DI – смещение на последний символ
                           ; расширенной строки 
    
    ; Освобождение места для введенного слова    
    mov ax,0h
    mov al,new_string_size    
    dec al
    sub al,place
    mov cx,ax ; CX = new_string_size - 1 - place       
    rep movsb ; DS:SI в ES:DI пока CX <> 0
    
    ; Вставка введенного слова
    cld ; DF = 0 
    
    lea si,spaste ; SI – смещение на первый символ
                  ; вставляемого слова
                            
    lea di,string 
    mov ax,0h
    mov al,place
    add di,ax ; DI – смещение на место начала 
              ; вставки в string
    
    mov ax,0h
    mov al,spaste_size
    mov cx,ax ; CX = spaste_size  
    
    rep movsb ; DS:SI в ES:DI пока CX <> 0
    
    ; Вставка пробела после введенного слова
    mov bx,0h
    add bl,place
    add bl,spaste_size ; BX = place + spaste_size
    mov string[bx],' ' ; string[place + spaste_size] = ' ' 
    
    ; Вывод результата
    printStr toNewLine 
    printStr strResult 
    ;printStr string
    printStrBySymbol string,new_string_size
    
    

    end:           ; Конец программы
    
    mov ax,4C00h   ; 4C (выход из программы) в AH
                   ; 00 (успешное звершение) в AL 
    int 21h        ; Функция DOS "Завершить программу" 
    


; Вычисление длины строки [Процедура]
; [2 байт, проверка на состоит ли из пробелов]
calcSizeOfStr PROC near
    mov si,strGeneral_offset ; strGeneral_offset содержит смещение строки
    add si,01d               ; SI++
    lodsb                    ; DS:SI в AL
    mov strGeneral_size,al 
    
    
    mov dl,0h                ; Количество пробелов
    mov bx,0h                ; Индекс в исследуемой строке
    mov di,strGeneral_offset ; Смещение строки

    while: 
        cmp [di+bx+2],' ' ; Сравнение текущего символа с пробелом  
        jne notSpace
        inc dl
        
        notSpace:
        
        ; Условие выхода из цилка
        inc bl  
        cmp bl,strGeneral_size
    jl while
      
    cmp dl,strGeneral_size
    jne stringNotEmpty
    mov strGeneral_size,0h     
    
    stringNotEmpty:
    
    ret
calcSizeOfStr endp    


; Отформатировать строку [Макрос]
; [Убрать первые два байта, добавить '$', вычислить длину]
formatStr macro str_size,str   
    
    ; Вычисление длины строки  
    lea si,str      ; Смещение str в SI
    mov strGeneral_offset,si  
    call calcSizeOfStr
    mov dl,strGeneral_size
    mov str_size,dl
    
    ; Сдвигаем строку на 2 влево
    lea di,str ; Смещение str в DI
    mov si,di
    add si,02d ; SI = DI + 2
     
    mov CH,0h
    mov CL,str_size ; CX = str_size 
    rep movsb       ; Пересылка DS:SI в ES:DI,
                    ; пока CX <> 0   
                      
    ; Добавление '$' в конец  
    lea di,str      ; Смещение строки в DI
    mov dh,0d
    mov dl,str_size ; DX = str_size
    add di,dx       ; DI += str_size
    mov al,'$'      ; Символ '$'    
    stosb           ; AL в ES:DI 
    
endm   

; Распечатать строку посимвольно [Процедура]
printStrBySymbolProc PROC near            
    
    mov ah,06h               ; Записать символ в STDOUT
    
    mov di,strGeneral_offset ; Смещение строки 
    mov bx,0h                ; Индекс в выводимой строке   
    
    mov dx,0h 
    mov dl,strGeneral_size
    mov cx,dx                ; Длина строки
    jcxz strIsEmpty          ; Если строка пустая
    
    while1:
        mov dl,[di+bx]
        int 21h ; Вывод текущего символа
        
        ; Условие выхода из цикла
        inc bx
        cmp bx,cx     
    jl while1    
    
    ; Строка пустая       
    strIsEmpty:
    
    ret
    
printStrBySymbolProc endp 

; Распечатать строку посимвольно [Макрос]
printStrBySymbol macro str,str_size
    lea si,str
    mov strGeneral_offset,si
    
    mov dl,str_size
    mov strGeneral_size,dl
    
    call printStrBySymbolProc
endm

.data ; Сегмент данных   
    
    testString db '$$$ I am a $wizard$, I can $print$ dollars $$$'   
    testrString_size db 46d
    
    ; Исходная строка 
    string db 200 DUP(?)
    string_maxSize db equ 100  
    string_size db 0
    new_string_size db 0   
    string_rightFormat db '"Source string" - a sentence consisting of words separated by spaces',0Dh,0Ah,'$'
    string_info db 'Source string: $' 
    
     
    ; Строка, перед которой вставляем
    sfind db 200 DUP(?)
    sfind_maxSize db equ 20
    sfind_size db 0          
    sfind_rightFormat db '"Paste before"  - the word contained in "source string"',0Dh,0Ah,'$'
    sfind_info db 'Paste before:  $' 
    
    ; Строка, которую вставляем
    spaste db 200 DUP(?)
    spaste_maxSize db equ 20
    spaste_size db 0 
    spaste_rightFormat db '"Pasting word"  - the word inserted into the sentence"',0Dh,0Ah,'$'   
    spaste_info db 'Pasting word:  $'
    
    ; Строка для передачи в процедуру
    strGeneral_offset dw 0
    strGeneral_size db 0
    
    temp db 0   ; Временная переменная               
    place db 0  ; Место в строке, где начинается слово
                ; перед которым надо вставить 
    found db 0  ; bool, найдено ли слово          
    
    ; Строка если не нашли слово, перед которым вставить 
    strPlaceNotFound db 'The word to insert before which was not found$' 
    
    strResult db 'Result:        $'        ; Результат   
    strEmpty db 'Entered string is empty$' ; Введенное слово пустое
    toNewLine db 0Ah, 0Dh, '$'             ; Символы перехода на новую строку (v,<)     
    
.stack 100h     ; Сегмент стека (256 байт)
    
end START   ; Конец программы  

