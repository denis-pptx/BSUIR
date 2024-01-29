
readChars MACRO id, number, buf 
    mov ah,3Fh    ; Функция DOS (чтение из файла)
    mov bx,id     ; Загрузка дескриптора
    mov cx,number ; Количество считываемых чисволов
    lea dx,buf    ; Загрузка буфера 
    int 21h       ; Считать данные    
endm

writeChars MACRO id, number, buf
    mov ah,40h    ; Функция DOS (запись в файл)
    mov bx,id     ; Дескриптор
    mov cx,number ; Количество записываемых символов
    lea dx,buf    ; Буфер 
    int 21h       ; Записать данные 
endm


setCursor MACRO id, distance, type 
    mov ah,42h      ; Функция DOS (переместить указатель чтения/записи)
    mov bx,id       ; Идентификатор
    mov cx,0h       ;
    mov dx,distance ;
    mov al,type     ; Относительно чего
    int 21h         ; Переместить указатель  
endm

closeFile MACRO id
    mov bx,id  ; Дескриптор
    mov ah,3Eh ; Функция DOS 3Eh
    int 21h    ; Закрыть файл
endm 

deleteFile MACRO name
    mov ah,41h  ; Функция DOS 41h (удалить файл)
    lea dx,name ; Адрес ASCIZ-строки с именем файла 
    int 21h     ; Удалить файл
endm

createFile MACRO name, id
    mov ah,3Ch       ; Функция DOS 3Ch (создать файл)
    mov cx,00100000b ; Атрибут файла
    lea dx,name      ; Адрес ASCIZ-строки с именем файла
    int 21h          ; Создать файл
    mov id,ax        ; Сохранить дескриптор
endm


openFile MACRO name, id
    lea dx,name ; адрес ASCIZ-строки с именем файла
    mov ah,3Dh  ; Функция DOS 3Dh (открыть существующий файл)  
    mov al,02h  ; 02 - для чтения и записи
    int 21h     ; Открыть файл    
    mov id,ax   ; Сохранить дескриптор
endm

.code         

START: 
    
    mov ax,@data  ; @data - идентификатор сегмента данных
    mov ds,ax     ; Адрес сегмента данных — в DS      
    mov es,ax     ; Адрес сегмента данных — в ES      
    
    
    openFile source_file_name, source_file_ID            ; Открыть исходный файл 
    createFile temp_file_name,temp_file_ID               ; Создать временный файл  
    createFile destination_file_name,destination_file_ID ; Создать файл с результатом 

    mainWhile:
        
        ; Считывание порции символов
        readChars source_file_ID, buffer_dose, buffer  
        mov charsRead,ax
        
        ; Поиск симола 0Dh в считанном буфере
        mov cx,charsRead ; Количество считанных символов   
        mov al,0Dh       ; Символ 0Dh 
        lea di,buffer    ; Смещение буфера
        repne scasb      ; Сравниваем, пока не равны 
        jz Exists0Dh     ; ZF = 1?  
        
        ; Действие, если нет символа 0Dh
        NotExists0Dh: 
        
            mov dx,charsRead           ; Число символов в порции = 
            mov charsOfStringInDose,dx ; = число считанных символов
            mov isEndOfString,00h      ; Конца строки нет
            
            ; Поиск символа NULL в считанном буфере
            mov cx,charsRead          ; Количество считанных символов  
            mov al,0h                 ; Символ NULL
            lea di,buffer             ; Смещение буфера
            repne scasb               ; Сравниваем, пока не равны
            jnz writeCharsInTempFile  ; ZF <> 0?
         
                ; Действие, если есть символ NULL
                dec charsOfStringInDose  ; charsOfStringInDose--   
                mov isEndOfString,01h    ; Конец строки
                mov isEndOfFile,01h      ; Конец файла
                jmp writeCharsInTempFile
                 
        ; Действие, если есть символ 0Dh
        Exists0Dh:
        
            ; Определения числа символов строки в порции
            ; charsOfStringInDose = charsRead - CX + 1   
            mov dx,charsRead 
            mov charsOfStringInDose,dx
            sub charsOfStringInDose,cx
            inc charsOfStringInDose
            mov isEndOfString,01h
        
            ; Кейс когда .. .. .. .. 0Dh, порция закончилась
            ; то есть в порцию не влезло 0Ah
            mov bx,charsOfStringInDose
            mov buffer[bx-1],0Ah
        
        
        ; Запись символов во временный файл
        writeCharsInTempFile:  
        writeChars temp_file_ID,charsOfStringInDose,buffer 
        mov dx,charsOfStringInDose  ; charactersInString +=
        add charsInString,dx        ; += charOfStringInDose
        
        ; Есть конец строки или нет
        cmp isEndOfString,0h
        je notEndOfString
        
        ; Действие, если в порции есть конец строки
        endOfString:
        
            ; Установка курсора в source_file
            ; cursorOffset = -(charsRead - charsOfStringInDose) 
            mov bx,charsRead
            mov cursorOffset,bx
            mov bx,charsOfStringInDose
            sub cursorOffset,bx
            neg cursorOffset
            setCursor source_file_ID,cursorOffset,01h
             
             
             
            ; Проверка, подходит ли строка из файла под условие
            ; "не содержать ни одного символа из заданных"
            setCursor temp_file_ID,00h,00h ; Курсор на начало файла   
            mov dx,charsInString
            mov charsInStringCopy,dx
            mov dx,buffer_dose
            cmp charsInStringCopy,dx
            jbe skipCheckCycle
            
            ; Цикл сравнения порциями
            checkCycle:
                readChars temp_file_ID buffer_dose, buffer ; Считать символы 
                checkBufferMacro buffer_dose               ; Проверить
                cmp contains,01h
                je resetTempfile
            
                mov dx,buffer_dose       ;
                sub charsInStringCopy,dx ; charsInStringCopy -= buffer_dose  
               
                mov dx,buffer_dose       ; Сравнение charsInStringCopy    
                cmp charsInStringCopy,dx ; и buffer_dose 
            ja checkCycle                ; charsInStringCopy > buffer_dose? 
            
            ; charsInStringCopy <= buffer_dose 
            skipCheckCycle: 
            readChars temp_file_ID charsInStringCopy, buffer ; Считать символы
            checkBufferMacro charsInStringCopy               ; Проверить
            cmp contains,01h
            je resetTempfile
            
            
            
            ; Пересылка строки из temp_file в destination_file
            setCursor temp_file_ID,00h,00h ; Курсор на начало файла  
            mov dx,buffer_dose             ;
            cmp charsInString,dx           ;
            jbe skipTransferCycle          ; charsInString <= buffer_dose?  
            
            ; Цикл пересылки строки порциями
            transferCycle:
                readChars temp_file_ID buffer_dose, buffer         ; Считать символы
                writeChars destination_file_ID buffer_dose, buffer ; Записать символы
               
                mov dx,buffer_dose   ;
                sub charsInString,dx ; charsInString -= buffer_dose  
               
                mov dx,buffer_dose   ; Сравнение charsInString    
                cmp charsInString,dx ; и buffer_dose 
            ja transferCycle         ; charsInString > buffer_dose? 
            
            ; charsInString <= buffer_dose 
            skipTransferCycle:
            readChars temp_file_ID charsInString, buffer         ; Считать символы
            writeChars destination_file_ID charsInString, buffer ; Записать символы
            
            
            
            ; Сбросить временный файл
            resetTempfile:                                                      
            mov charsInString,0h           ; charsInString = 0 
            setCursor temp_file_ID,00h,00h ; Курсор на начало файла

        ; Действие, если в порции нет конца строки
        notEndOfString:
            mov isEndOfString,0h ; Не конец строки
            cmp isEndOfFile,01h  ; Сравнение
        
    jne mainWhile ; Конец файла?
    

    ; Завершение программы
    exit:
    closeFile temp_file_ID    ; Закрыть временный файл
    deleteFile temp_file_name ; Удалить временный файл  
    
    mov ax,4C00h   ; 4C (выход из программы) в AH
                   ; 00 (успешное звершение) в AL 
    int 21h        ; Функция DOS "Завершить программу"  

; [Процедура] – результат в contains
; Есть ли символы в порции строки    
checkBuffer PROC near
    mov contains,0h 
    
    mov si,0h ; SI = 0 [счетчик]
    for1:
        mov dx,0h         ; DX = 0   
        mov dl,buffer[si] ; DX = текущий символ из порции 
        push si           ; Сохранение SI 
        
        mov si,0h         ; SI = 0 [счетчик] 
        for2:
            cmp dl,symbols[si] ; Сравнение символа из порции с 
            jne not_equals     ; символом из набора символов
            mov contains,01h   ; contains = 1 
            pop si             ; Восстановление SP
            ret                ; Выход из процедуры
            
            ; Не равен
            not_equals:
            
            ; Условие выхода из цикла
            inc si               ; SI++
            cmp si,symbolsNumber ; Сравнение
        jb for2 ; if si < symbolsNumber
        
        pop si ; Восстановление SI
        
        ; Условие выхода из цикла
        inc si                   ; SI++ 
        cmp si,bufferNumberCheck ; Сравнение
    jb for1 ; if si < bufferNumberCheck
    
    ret           
checkBuffer endp

; [Макрос] – есть ли символы в порции строки 
checkBufferMacro MACRO number
    mov dx,number
    mov bufferNumberCheck,dx
    call checkBuffer 
endm 

.data  

    source_file_name db 'd:\data.txt',0 ; Исходный файл
    source_file_ID   dw 0               ; Дескриптор
    
    destination_file_name db 'd:\result.txt',0 ; Файл с результатом
    destination_file_ID dw 0                   ; Дескриптор 
     
    temp_file_name db 'd:\temp.txt',0 ; Временный файл
    temp_file_ID   dw 0               ; Дескриптор    
    
    buffer      db 100 DUP(0) ; Буфер данных    
    buffer_dose dw 50d        ; Размер порции
    
    isEndOfFile   db 0 ; [bool] – конец ли файла 
    isEndOfString db 0 ; [bool] – конец ли строки 
    
    charsRead           dw 0 ; Считано символов    
    charsOfStringInDose dw 0 ; Символов строки в порции
    charsInString       dw 0 ; Символов в строке
    
    cursorOffset        dw 0 ; Смещение курсора
    
    symbols           db '0123456789' ; Символы, которых быть не дложно
    symbolsNumber     dw 10           ; Их число
    
    bufferNumberCheck dw 0 ; Количество символов из буфера для проверки
    charsInStringCopy dw 0 ; Символов в строке (копия)
    contains          db 0 ; [bool] – есть ли в первых charsOfStringInDose 
                           ; символах из buffer 1 из символов symbols 
.stack 100h     


end START     

