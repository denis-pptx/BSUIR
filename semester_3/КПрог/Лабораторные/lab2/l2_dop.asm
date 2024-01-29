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
 ldx #$4781

 stx $8120 ; Тут хранится X

 ; D / X -> X (ост B)

 xgdx
 ldx #$10
 idiv ; в B теперь 0 тетрада
 pshb

 ldd $8120 ; в D кидаем тот самый X
 ldaa #0
 ldx #$10
 idiv
 xgdx ; в B теперь 1 тетрада
 pshb

 ldd $8120 ; в D кидаем тот самый X
 ldab #0
 ldx #$1000
 idiv ; в A теперь 2 тетрада
 psha

 ldd $8120 ; в D кидаем тот самый X
 ldab #0
 ldx #$1000
 idiv
 xgdx ; в B теперь 3 тетрада
 pshb
 