 org $8000

 ldx #0 ; Обнуление X

 ldab $8000 ; Загрузка в B
 abx        ; Сложение B с X

 ; Далее еще 4 схожие итерации

 ldab $8001
 abx

 ldab $8002
 abx

 ldab $8003
 abx

 ldab $8004
 abx

 ; Итог - в X сумма ячеек $8000..$8004

 txs ; Пересылка X в SP
 ; Уменьшение SP на 7
 psha
 psha
 psha
 psha
 psha
 psha
 psha
 tsx ; Пересылка SP в X

 pshx ; Загрузка X в стек
  
 