CREATE OR REPLACE FUNCTION calculate_compensation(
    p_salary NUMBER,
    p_bonus_percentage NUMBER
) RETURN NUMBER
IS
    l_bonus NUMBER;
    l_compensation NUMBER;
    
    ex_salary EXCEPTION;
    ex_bonus EXCEPTION;
BEGIN
    -- Проверка на корректность введенных данных
    IF p_salary IS NULL 
        OR p_salary < 0
    THEN
        RAISE ex_salary;
    END IF;
    
    IF (p_bonus_percentage IS NULL) 
        OR (MOD(p_bonus_percentage, 1) != 0) 
        OR p_bonus_percentage < 0
    THEN
        RAISE ex_bonus;
    END IF;

    -- Преобразование целочисленного процента к дробному
    l_bonus := p_bonus_percentage / 100;

    -- Вычисление общего вознаграждения
    l_compensation := (1 + l_bonus) * 12 * p_salary;

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

EXEC DBMS_OUTPUT.PUT_LINE(calculate_compensation(1000, 21));