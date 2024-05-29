DROP PROCEDURE C##dev.denis_sdal;

CREATE OR REPLACE PROCEDURE C##dev.denis_sdal AS
BEGIN
    dbms_output.put_line('Hello world');
END;
/




DROP PROCEDURE C##dev.cur_date;
CREATE OR REPLACE PROCEDURE C##dev.cur_date AS
BEGIN
    dbms_output.put_line('cur date');
END;
/
DROP PROCEDURE C##prod.cur_date;
CREATE OR REPLACE PROCEDURE C##prod.cur_date AS
BEGIN
    dbms_output.put_line('cur date');
END;
/
DROP PROCEDURE C##prod.goodbye_world;
CREATE OR REPLACE PROCEDURE C##prod.goodbye_world AS
BEGIN
    dbms_output.put_line('Goodbye world');
END;
/
DROP PROCEDURE C##dev.diff_param;
CREATE OR REPLACE PROCEDURE C##dev.diff_param (param1 IN VARCHAR2) AS
BEGIN
    dbms_output.put_line('Param VARCHAR2: ' || param1);
END;
/
DROP PROCEDURE C##prod.diff_param;
CREATE OR REPLACE PROCEDURE C##prod.diff_param (param1 OUT VARCHAR2) AS
BEGIN
    dbms_output.put_line('Param NUMBER: ' || param1);
END;
/
DROP PROCEDURE C##dev.diff_code;
CREATE OR REPLACE PROCEDURE C##dev.diff_code (param1 VARCHAR2) AS
BEGIN
    dbms_output.put_line('Param VARCHAR2: ' || param1);
END;
/
DROP PROCEDURE C##prod.diff_code;
CREATE OR REPLACE PROCEDURE C##prod.diff_code (param1 VARCHAR2) AS
BEGIN
    dbms_output.put_line('Param param VARCHAR2: ' || param1);
END;