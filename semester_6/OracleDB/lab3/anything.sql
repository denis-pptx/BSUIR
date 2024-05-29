CALL compare_schemas('C##DEV', 'C##PROD');

SELECT index_name 
    FROM all_indexes
    WHERE (owner = 'C##PROD')
        AND index_name NOT LIKE 'SYS%';