-- DROP PROCEDURE restore_students;
CREATE OR REPLACE PROCEDURE restore_students(
    p_timestamp TIMESTAMP DEFAULT NULL,
    p_offset INTERVAL DAY TO SECOND DEFAULT NULL
) 
AS
    l_restore_timestamp TIMESTAMP;
BEGIN
    -- Оба не NULL
    IF (p_timestamp IS NULL) AND (p_offset IS NULL)
    THEN
        RAISE_APPLICATION_ERROR(-20000, 'A timestamp and an offset cant both be empty');
    END IF;

    -- Только один имеет значение
    IF (p_timestamp IS NOT NULL) AND (p_offset IS NULL) THEN
        l_restore_timestamp := p_timestamp;
    ELSIF (p_timestamp IS NULL) AND (p_offset IS NOT NULL) THEN
        l_restore_timestamp := SYSTIMESTAMP - p_offset;
    ELSE
        RAISE_APPLICATION_ERROR(-20000, 'Only either a timestamp or an offset can contain a value.');
    END IF;

    -- Восстановление
    -- DELETE FROM students;
    
    FOR log IN (SELECT * FROM log_students WHERE timestamp <= l_restore_timestamp) 
    LOOP
        IF log.ACTION = 'INSERT'
        THEN
            DELETE FROM students
            WHERE id = log.student_id;
            
            INSERT INTO students
            VALUES (log.student_id, log.student_name, log.group_id);
        ELSIF log.ACTION = 'UPDATE'
        THEN
            UPDATE students
            SET NAME = log.student_name, group_id = log.group_id
            WHERE ID = log.student_id;
        ELSIF log.ACTION = 'DELETE' 
        THEN
            DELETE FROM students 
            WHERE ID = log.student_id;
        END IF;
    END LOOP;
END;
/

--EXECUTE restore_students(TO_TIMESTAMP('2024-02-25 22:16:50', 'YYYY-MM-DD HH24:MI:SS'));
EXECUTE restore_students(p_offset => INTERVAL '0 03:00:00' DAY TO SECOND);