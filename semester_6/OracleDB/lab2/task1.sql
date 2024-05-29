DROP TABLE groups;
DROP TABLE students;

CREATE TABLE groups (
    id NUMBER,
    name VARCHAR2(100),
    c_val NUMBER
);


CREATE TABLE students (
    id NUMBER,
    name VARCHAR2(100),
    group_id NUMBER
);
