-- Процедура для вставки записи
CREATE OR REPLACE PROCEDURE InsertRecord(p_id NUMBER, p_val NUMBER) 
AS
BEGIN
    INSERT INTO MyTable (id, val) 
    VALUES (p_id, p_val);
END InsertRecord;
/

-- Процедура для обновления записи
CREATE OR REPLACE PROCEDURE UpdateRecord(p_id NUMBER, p_new_val NUMBER) 
AS
BEGIN
    UPDATE MyTable 
    SET val = p_new_val 
    WHERE id = p_id;
END UpdateRecord;
/

-- Процедура для удаления записи
CREATE OR REPLACE PROCEDURE DeleteRecord(p_id NUMBER) 
AS
BEGIN
    DELETE FROM MyTable 
    WHERE id = p_id;
END DeleteRecord;
/

-- Вызов процедуры для вставки записи
EXEC InsertRecord(1, 10);

-- Вызов процедуры для обновления записи
EXEC UpdateRecord(10000, 8155);

-- Вызов процедуры для удаления записи
EXEC DeleteRecord(1);

-- 
SELECT * FROM MyTable;