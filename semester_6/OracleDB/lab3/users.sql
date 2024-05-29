DROP USER C##dev;
DROP USER C##prod;
DROP USER C##denis;

CREATE USER C##dev IDENTIFIED BY my_password;
CREATE USER C##prod IDENTIFIED BY my_password;
CREATE USER C##denis IDENTIFIED BY my_password;

GRANT CREATE SESSION TO C##dev;
GRANT CREATE SESSION TO C##prod;
grant sysdba to C##denis container=all;
GRANT ALL PRIVILEGES TO C##denis;