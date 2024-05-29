-- Обновление c_val в group (количество студентов)
-- DROP TRIGGER update_c_val;

CREATE OR REPLACE TRIGGER update_c_val
AFTER INSERT OR UPDATE OR DELETE ON students
FOR EACH ROW
BEGIN 
    IF UPDATING THEN
        UPDATE groups
        SET c_val = c_val + 1
        WHERE id = :NEW.group_id;

        UPDATE groups
        SET c_val = c_val - 1
        WHERE id = :OLD.group_id;
    END IF;

    IF INSERTING THEN
        UPDATE groups
        SET c_val = c_val + 1
        WHERE id = :NEW.group_id;
    END IF;

    IF DELETING THEN
        UPDATE groups
        SET c_val = c_val - 1
        WHERE id = :OLD.group_id;
    END IF;
END;
/