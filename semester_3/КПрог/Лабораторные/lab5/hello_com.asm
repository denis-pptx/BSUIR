; hello_com.asm
    .model tiny     ; Модель памяти (код, данные и стек в 1 сегменте)
    .code           ; Сегмент кода
    org 100h        ; Начальное значение IP
start:
    mov ah,9                ; Номер функции DOS - в AH
    mov dx,offset message   ; Адрес строки — в DX
    int 21h                 ; Вызов системной функции DOS
    ret                     ; Завершение COM-программы (передать управление обратно в DOS)
message db "Hello World!",07h,'$' ; Строка для вывода, 07h — звуковой сигнал
end start                         ; Конец программы