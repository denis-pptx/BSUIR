CREATE OR REPLACE FUNCTION CheckEvenOddCount 
    RETURN VARCHAR2 
AS
    l_even_count NUMBER := 0;
    l_odd_count NUMBER := 0;
BEGIN
    FOR rec IN (SELECT val FROM MyTable) 
    LOOP
        IF MOD(rec.val, 2) = 0 THEN
            l_even_count := l_even_count + 1;
        ELSE
            l_odd_count := l_odd_count + 1;
        END IF;
    END LOOP;

    IF l_even_count > l_odd_count THEN
        RETURN 'TRUE';
    ELSIF l_even_count < l_odd_count THEN
        RETURN 'FALSE';
    ELSE
        RETURN 'EQUAL';
    END IF;
END;
/

EXEC DBMS_OUTPUT.PUT_LINE(CheckEvenOddCount);
/