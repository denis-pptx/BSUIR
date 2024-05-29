CREATE OR REPLACE FUNCTION calculate_compensation(
    p_salary VARCHAR2,
    p_bonus_percentage VARCHAR2
) RETURN NUMBER
IS
    l_salary NUMBER;
    l_bonus_percentage NUMBER;
    
    l_bonus NUMBER;
    l_compensation NUMBER;
    
    ex_salary EXCEPTION;
    ex_bonus EXCEPTION;
BEGIN
    -- Конвертация
    l_salary := TO_NUMBER(p_salary);
    l_bonus_percentage := TO_NUMBER(p_bonus_percentage);
    
    -- Проверка на корректность введенных данных
    IF l_salary IS NULL 
        OR l_salary < 0
    THEN
        RAISE ex_salary;
    END IF;
    
    IF (l_bonus_percentage IS NULL) 
        OR (MOD(l_bonus_percentage, 1) != 0) 
        OR l_bonus_percentage < 0
    THEN
        RAISE ex_bonus;
    END IF;

    -- Преобразование целочисленного процента к дробному
    l_bonus := l_bonus_percentage / 100;

    -- Вычисление общего вознаграждения
    l_compensation := (1 + l_bonus) * 12 * l_salary;

    RETURN l_compensation;
EXCEPTION
    WHEN ex_salary THEN
        DBMS_OUTPUT.PUT_LINE('Invalid salary');
        RETURN NULL;
    WHEN ex_bonus THEN
        DBMS_OUTPUT.PUT_LINE('Invalid bonus');
        RETURN NULL;
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('Invalid data');
        RETURN NULL;
END calculate_compensation;
/

EXEC DBMS_OUTPUT.PUT_LINE(calculate_compensation(1000, '215'));