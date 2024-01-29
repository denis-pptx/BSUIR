createFile MACRO name, id
    mov ah,3Ch       ; Функция DOS 3Ch (создать файл)
    mov cx,00100000b ; Атрибут файла
    mov dx,name      ; Адрес ASCIZ-строки с именем файла
    int 21h          ; Создать файл
    mov id,ax        ; Сохранить дескриптор
endm
   
    .model tiny 
    
    .code
;org 80h         ; Смещение 80h от начала PSP
;cmd_length db ? ; Длина командной строки
;cmd_line db ?   ; Сама командная строка

    org 100h ; Начало программы 100h от начала PSP
    
     
start:
   ; argc equ dw 0 ; Число параметров  
    
    
    cld       ; Для команд строковой обработки
    mov bp,sp ; Сохранить текущую вершину стека в BP
    
    mov cl,[80h] ; Размер командной строки
    cmp cl,1 ; Проверка длины командной строки
    jle exit ; выход из программы
    
    ; Преобразовать список параметров в PSP так, чтобы
    ; каждый параметр заканчивался нулем (ASCIZ-строка)
    ; адреса всех параметров поместить в стек
    ; в переменную argc записать число параметров
    
    mov cx,-1 ; Для команд работы со строками
    mov di,81h ; Начало командной строки в ES:DI
    
find_param:
    mov al,' '        ; AL = пробел
    repz scasb        ; Искать не пробел
    dec di            ; DI = адрес начала параметра 
    push di           ; Сохранить адрес в стек
    inc argc          ; Увеличить argc на 1
    mov si,di         ; SI = DI для следующей команды lodsb
    
scan_params:
    lodsb           ; Прочитать символ из параметра
    cmp al,0Dh      ; Если 0Dh – последний параметр
    je params_ended ; Параметры закончились
    cmp al,20h      ; Сравнение с пробелом
    jne scan_params ; Текущий параметр не закончился
    
    dec si               ; SI = первый байт после параметра
    mov [si],0  ; Записать в него 0
    mov di,si            ; DI = SI для команды scasb
    inc di               ; DI = следующий после нуля символ
     
    jmp find_param ; Продолжить разбор командной строки
    
params_ended:
    ;=========================
    cmp [si-2],0
    jne cmdDontEndsWithEnter
    dec argc
    cmdDontEndsWithEnter:
    ;=========================
    dec si              ; SI = первый байт после конца 
                        ; последнего параметра
    mov byte ptr [si],0 ; Записать в него 0

    ; Работа с параметрами
     
    ;continue: 
    ;createFile [offsetFileName],source_file_ID 
exit: 
    mov sp,bp 
 
    ret ; Конец программы 
   
    argc dw 0 ; Число параметров  
    offsetFileName dw 0 ; Смещение в PSP на путь к файлу
    
    source_file_name db 'd:\data.txt',0 ; Исходный файл
    source_file_ID   dw 0               ; Дескриптор   
    
; Данные программы

end start