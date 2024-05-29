-- Каскадное удаление студентов
-- DROP TRIGGER cascade_students_fk;

CREATE OR REPLACE TRIGGER cascade_students_fk
BEFORE DELETE ON groups
FOR EACH ROW
BEGIN
    DELETE FROM students
    WHERE group_id = :OLD.id;
END;
/

-- Проверка на существование группы
-- DROP TRIGGER students_check_fk;

CREATE OR REPLACE TRIGGER students_check_fk
BEFORE INSERT ON students
FOR EACH ROW
DECLARE
    l_count NUMBER;
BEGIN
    SELECT COUNT(*) INTO l_count FROM groups WHERE id = :NEW.group_id;
    
    IF l_count = 0 THEN
        RAISE_APPLICATION_ERROR(-20000, 'Ошибка: Указанный group_id не существует в таблице groups.');
    END IF;
END;
/
