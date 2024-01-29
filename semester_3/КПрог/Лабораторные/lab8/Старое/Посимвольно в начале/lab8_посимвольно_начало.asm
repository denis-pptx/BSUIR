
readCharacters MACRO id, number, buf 
    mov ah,3Fh    ; Функция DOS (чтение из файла)
    mov bx,id     ; Загрузка дескриптора
    mov cx,number ; Количество считываемых чисволов
    lea dx,buf    ; Загрузка буфера 
    int 21h       ; Считать данные    
endm

writeCharacters MACRO id, number, buf
    mov ah,40h    ; Функция DOS (запись в файл)
    mov bx,id     ; Дескриптор
    mov cx,number ; Количество записываемых символов
    lea dx,buf    ; Буфер 
    int 21h       ; Записать данные 
endm

setCursorAtZero MACRO id
    mov ah,42h ; Функция DOS (переместить указатель чтения/записи)
    mov bx,id  ; Идентификатор
    mov cx,0h  ;
    mov dx,0h  ;
    mov al,0h  ; На 0 относительно начала
    int 21h    ; Переместить указатель  
endm

.code         

START: 
    
    mov ax,@data  ; @data - идентификатор сегмента данных
    mov ds,ax     ; Адрес сегмента данных — в DS      
    mov es,ax     ; Адрес сегмента данных — в ES      
    
    ; Открытие исходного файла
    lea dx,source_file_name ; адрес ASCIZ-строки с именем файла
    mov ah,3Dh              ; Функция DOS 3Dh (открыть существующий файл)
    mov al,00h              ; 00 - только для чтения
    int 21h                 ; Открыть файл    
    jc exit                 ; Если ошибка – выход
    mov source_file_ID,ax   ; Сохранить дескриптор
     
    ; Открытие файла назначения
    ;lea dx,destination_file_name ; адрес ASCIZ-строки с именем файла
    ;mov ah,3Dh                   ; Функция DOS 3Dh (открыть существующий файл)
    ;mov al,01h                   ; 1 - только для записи
    ;int 21h                      ; Открыть файл    
    ;jc exit                      ; Если ошибка – выход
    ;mov destination_file_ID,ax   ; Сохранить дескриптор
    
    ; Создать файл (будет выступать в роли временного)
    mov ah,3Ch            ; Функция DOS 3Ch (создать файл)
    mov cx,00100000b      ; Атрибут файла
    lea dx,temp_file_name ; Адрес ASCIZ-строки с именем файла
    int 21h               ; Создать файл
    mov temp_file_ID,ax   ; Сохранить дескриптор
    
    ; Создание файла назначения
    mov ah,3Ch            ; Функция DOS 3Ch (создать файл)
    mov cx,00100000b      ; Атрибут файла
    lea dx,destination_file_name ; Адрес ASCIZ-строки с именем файла
    int 21h               ; Создать файл
    mov destination_file_ID,ax   ; Сохранить дескриптор
    

    
    mainWhile:
        

        readCharacters source_file_ID, 01h, buffer
         
        ;cmp ax,0h ; Было считано 0 символов => файл закончился 
        ;jne notEndOfFile
        cmp buffer,0h ; buffer = 0 => файл закончился 
        jne notEndOfFile
        
         
        endOfFile:
        
        mov buffer,00h
        writeCharacters temp_file_ID, 01h, buffer 
        

        setCursorAtZero temp_file_ID ; Идентификатор
 
        transferString_end:
            readCharacters temp_file_ID, 01h, buffer
            cmp buffer,00h
            je endMainWhile
            writeCharacters destination_file_ID, 01h, buffer
    
            
        jne transferString_end
        
        jmp endMainWhile
        
        
       
        
        notEndOfFile:
        
        cmp buffer,0Dh ; Символ 0Dh => конец строки
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

        
        ; Создать файл (будет выступать в роли временного)
        mov ah,3Ch            ; Функция DOS 3Ch (создать файл)
        mov cx,00100000b      ; Атрибут файла
        lea dx,temp_file_name ; Адрес ASCIZ-строки с именем файла
        int 21h               ; Создать файл
        mov temp_file_ID,ax   ; Сохранить дескриптор
      
        jmp mainWhile
        
        notEndOfString:
        writeCharacters temp_file_ID, 01h, buffer
    
    jmp mainWhile
    
    endMainWhile:
    
    ; Закрытие файла
close_file:  
    mov bx,destination_file_ID
    mov ah,3Eh ; Функция DOS 3Eh
    int 21h    ; Закрыть файл

    ; Завершение программы
exit:
    mov ax,4C00h   ; 4C (выход из программы) в AH
                   ; 00 (успешное звершение) в AL 
    int 21h        ; Функция DOS "Завершить программу"  
    
.data  

    source_file_name db 'd:\data.txt',0 ; Исходный файл
    source_file_ID   dw 0               ; Дескриптор
    
    destination_file_name db 'd:\result.txt',0 ; Файл с результатом
    destination_file_ID dw 0                   ; Дескриптор 
     
    temp_file_name db 'd:\temp.txt',0 ; Временный файл
    temp_file_ID   dw 0               ; Дескриптор    
    
    ;buffer db 100 DUP(0) ; Буфер данных    
    buffer db 0
    
    characters db 'abc'
    
    isEndOfFile db 0 ; bool
.stack 100h     


end START     

