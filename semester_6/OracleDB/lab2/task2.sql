-- Автоинкремент students.id
-- DROP TRIGGER students_ai_id;

CREATE OR REPLACE TRIGGER students_ai_id
BEFORE INSERT ON students
FOR EACH ROW
DECLARE 
    l_max_id NUMBER;
BEGIN
    IF :NEW.ID IS NULL 
    THEN
        SELECT MAX(id) INTO l_max_id FROM students;
        
        IF l_max_id IS NULL 
        THEN
            :NEW.ID := 1;
        ELSE 
            :NEW.ID := l_max_id + 1;
        END IF;
    END IF;
END;
/

-- Уникальность students.id
-- DROP TRIGGER students_unique_id;

CREATE OR REPLACE TRIGGER students_unique_id
BEFORE INSERT ON students
FOR EACH ROW
FOLLOWS students_ai_id
DECLARE
    l_count NUMBER;
BEGIN
    SELECT COUNT(*) INTO l_count FROM students WHERE id = :NEW.id;
    IF l_count != 0 
    THEN
        RAISE_APPLICATION_ERROR(-20000, 'Ошибка: Нарушение уникальности поля ID в таблице students.');
    END IF;

END;
/

-- Автоинкремент groups.id
-- DROP TRIGGER groups_ai_id;

CREATE OR REPLACE TRIGGER groups_ai_id
BEFORE INSERT ON groups
FOR EACH ROW
DECLARE 
    l_max_id NUMBER;
BEGIN
    IF :NEW.ID IS NULL 
    THEN
        SELECT MAX(id) INTO l_max_id FROM groups;
        
        IF l_max_id IS NULL 
        THEN
            :NEW.ID := 1;
        ELSE 
            :NEW.ID := l_max_id + 1;
        END IF;
    END IF;
END;
/

-- Уникальность groups.id и groups.name
-- DROP TRIGGER groups_unique;

CREATE OR REPLACE TRIGGER groups_unique
BEFORE INSERT ON groups
FOR EACH ROW
FOLLOWS groups_ai_id
DECLARE
    l_count NUMBER;
BEGIN
    SELECT COUNT(*) INTO l_count FROM groups WHERE id = :NEW.id;
    IF l_count != 0 THEN
        RAISE_APPLICATION_ERROR(-20000, 'Ошибка: Нарушение уникальности поля id в таблице groups.');
    END IF;
    
    SELECT COUNT(*) INTO l_count FROM groups WHERE name = :NEW.name;
    IF l_count != 0 THEN
        RAISE_APPLICATION_ERROR(-20000, 'Ошибка: Нарушение уникальности поля name в таблице groups.');
    END IF;
END;
/