-- Task2. Test unique groups.id
INSERT INTO groups(id, name, c_val) VALUES (1, 'group_name1', 0);
INSERT INTO groups(id, name, c_val) VALUES (null, 'group_name2', 0);
INSERT INTO groups(id, name, c_val) VALUES (null, 'group_name3', 0);
INSERT INTO groups(id, name, c_val) VALUES (1, 'group_name4', 0);
SELECT * FROM groups;

-- Task2. Test unique groups.name
INSERT INTO groups(id, name, c_val) VALUES (null, 'group_name5', 0);
INSERT INTO groups(id, name, c_val) VALUES (null, 'group_name3', 0);
UPDATE groups SET name = 'group_name1' where id = 5;
SELECT * FROM groups;

-- Task2. Test unique students.id
INSERT INTO students(id,name,group_id) VALUES (1, 'student_name1', 1);
INSERT INTO students(id,name,group_id) VALUES (1, 'student_name1', 1);
INSERT INTO students(id,name,group_id) VALUES (null, 'student_name1', 1);
UPDATE students SET id = 1 WHERE id = 2;
SELECT * FROM students;

-- Task3. Check FK only on exising record
ALTER TRIGGER update_c_val DISABLE;
INSERT INTO students(name, group_id) VALUES ('name1', 4);
INSERT INTO students(name, group_id) VALUES ('name2', 5555);

-- Task3. Check cascade delete
ALTER TRIGGER update_c_val DISABLE;
DELETE FROM groups WHERE id = 4;
SELECT * FROM students;

-- Task 4
SELECT * FROM log_students;

-- Task 5
DELETE FROM students;
EXECUTE restore_students(TO_TIMESTAMP('2024-02-28 17:50:23', 'YYYY-MM-DD HH24:MI:SS'));
-- EXECUTE restore_students(p_offset => INTERVAL '0 00:03:00' DAY TO SECOND);

-- Task 6. Check c_val of group
ALTER TRIGGER update_c_val ENABLE;
INSERT INTO students VALUES(null, 'name', 5);
INSERT INTO students VALUES(null, 'name', 3);
INSERT INTO students VALUES(null, 'name', 3);
DELETE FROM students WHERE group_id = 1;
SELECT * FROM groups;