; hello_exe.asm
    .model small    ; Модель памяти (код в 1 сегменте, данные и стек в DGROUP)
    .stack 100h     ; Сегмент стека (256 байт)
    .code           ; Сегмент кода
start:
    mov ax,@data    ; @data - идентификатор сегмента данных
    mov ds,ax       ; Адрес сегмента данных — в DS
    mov dx, offset message   ; Адрес строки — в DX 
    mov ah,9                ; Номер функции DOS — в AH
    int 21h                 ; Функция DOS "Вывод строки"  
    mov dx,offset message2   ; Адрес строки — в DX    
    int 21h                 ; Функция DOS "Вывод строки"
    mov ax,4C00h    ; 4C (выход из программы) в AH, 00 (успешное звершение) в AL 
    int 21h         ; Функция DOS "Завершить программу"
    .data           ; Сегмент данных
message db "Hello World!",07h,0Dh,0Ah,'$' ; Строка для вывода, 07h — звуковой сигнал       
message2 db "Hello World 2 string!",07h,'$' ; Строка для вывода, 07h — звуковой сигнал
    end start   ; Конец программы