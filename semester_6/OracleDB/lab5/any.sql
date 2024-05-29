DELETE FROM uni;

DELETE FROM groups;

DELETE FROM students;

DELETE FROM uni_logs;

DELETE FROM groups_logs;

DELETE FROM students_logs;

DELETE from reports_logs;

INSERT INTO uni (
    uni_name,
    creation_date
) VALUES(
    'u1',
    TIMESTAMP '2024-04-20 12:00:00'
);

--INSERT INTO uni (
--    uni_name,
--    creation_date
--) VALUES(
--    'test5',
--    TIMESTAMP '2024-04-20 12:00:00'
--);


INSERT INTO uni (
    uni_name,
    creation_date
) VALUES(
    'u2',
    TIMESTAMP '2024-04-21 12:00:00'
);

INSERT INTO uni (
    uni_name,
    creation_date
) VALUES(
    'u3',
    TIMESTAMP '2024-04-22 12:00:00'
);

UPDATE uni
SET
    creation_date = systimestamp
WHERE
    uni_name = 'u1';

DELETE FROM uni
WHERE
    uni_name = 'u3';

SELECT *
FROM uni_logs
ORDER BY change_date;

SELECT *
FROM uni
ORDER BY uni_id;

CALL func_package.roll_back(TIMESTAMP '2024-05-03 06:59:00');

CALL func_package.roll_back(600000);


CALL func_package.report();
CALL func_package.report(TIMESTAMP '2024-04-01 07:29:00');