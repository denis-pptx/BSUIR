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
FOR INSERT OR UPDATE ON students
FOLLOWS students_ai_id
COMPOUND TRIGGER

    TYPE t_students_id IS TABLE OF NUMBER INDEX BY PLS_INTEGER;
    l_students_id t_students_id;

    BEFORE STATEMENT IS
    BEGIN
        l_students_id.DELETE;
    END BEFORE STATEMENT;

    BEFORE EACH ROW IS
    BEGIN
        l_students_id(l_students_id.COUNT + 1) := :NEW.ID;
    END BEFORE EACH ROW;

    AFTER STATEMENT IS
        l_count NUMBER;
        l_id NUMBER;
    BEGIN
        FOR i IN l_students_id.FIRST .. l_students_id.LAST
        LOOP
            l_id := l_students_id(i);
            
            SELECT COUNT(*) INTO l_count FROM students WHERE id = l_id;
            
            IF l_count != 1 THEN
                RAISE_APPLICATION_ERROR(-20000, 'The student id alreasy exists: ' || l_id);
            END IF;
        END LOOP;
    END AFTER STATEMENT;
END students_unique_id;
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
FOR INSERT OR UPDATE ON groups
FOLLOWS groups_ai_id
COMPOUND TRIGGER

    TYPE t_groups_id IS TABLE OF NUMBER INDEX BY PLS_INTEGER;
    l_groups_id t_groups_id;
    
    TYPE t_groups_name IS TABLE OF VARCHAR(100) INDEX BY PLS_INTEGER;
    l_groups_name t_groups_name;

    BEFORE STATEMENT IS
    BEGIN
        l_groups_id.DELETE;
        l_groups_name.DELETE;
    END BEFORE STATEMENT;

    BEFORE EACH ROW IS
    BEGIN
        l_groups_id(l_groups_id.COUNT + 1) := :NEW.id;
        l_groups_name(l_groups_name.COUNT + 1) := :NEW.name;
    END BEFORE EACH ROW;

    AFTER STATEMENT IS
        l_count NUMBER;
    BEGIN
        FOR i IN l_groups_id.FIRST .. l_groups_id.LAST
        LOOP
            -- check id
            SELECT COUNT(*) INTO l_count FROM groups WHERE id = l_groups_id(i);
            IF l_count != 1 THEN
                RAISE_APPLICATION_ERROR(-20000, 'The group id alreasy exists: ' || l_groups_id(i));
            END IF;
            
            -- check name
            SELECT COUNT(*) INTO l_count FROM groups WHERE name = l_groups_name(i);
            IF l_count != 1 THEN
                RAISE_APPLICATION_ERROR(-20000, 'The group name alreasy exists: ' || l_groups_name(i));
            END IF;
        END LOOP;
    END AFTER STATEMENT;
END groups_unique;
/