BEGIN
    FOR i IN 1 .. 10000
    LOOP
        INSERT INTO MyTable (id, val) VALUES (i, ROUND(DBMS_RANDOM.value(1, 10000)));
    END LOOP;
END;