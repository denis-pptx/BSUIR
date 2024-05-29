CREATE OR REPLACE FUNCTION GenerateInsertCommand(p_id NUMBER DEFAULT 100) 
    RETURN VARCHAR2 
AS
    l_insert_command VARCHAR2(500);
BEGIN
    l_insert_command := 'INSERT INTO MyTable (id, val) VALUES (' || p_id || ', ' || ROUND(DBMS_RANDOM.VALUE(1,10000)) || ');';

    DBMS_OUTPUT.PUT_LINE(l_insert_command);

    RETURN l_insert_command;
END;
/

DECLARE
    l_result VARCHAR2(500);
BEGIN
    l_result := GenerateInsertCommand(123);
END;
/
