CREATE TABLE uni_logs (
    action_id NUMBER GENERATED BY DEFAULT ON NULL AS IDENTITY,
    uni_id NUMBER NOT NULL,
    uni_name VARCHAR2(20) NOT NULL,
    creation_date timestamp,
    change_date timestamp,
    change_type VARCHAR2(6),
    CONSTRAINT uni_logs_id_pk PRIMARY KEY (action_id)
);
/
CREATE TABLE groups_logs (
    action_id NUMBER GENERATED BY DEFAULT ON NULL AS IDENTITY,
    gr_id NUMBER NOT NULL,
    gr_name VARCHAR2(20) NOT NULL,
    uni_id NUMBER NOT NULL,
    creation_date timestamp,
    change_date timestamp,
    change_type VARCHAR2(6),
    CONSTRAINT gr_logs_id_pk PRIMARY KEY (action_id)
);
/
CREATE TABLE students_logs (
    action_id NUMBER GENERATED BY DEFAULT ON NULL AS IDENTITY,
    st_id NUMBER NOT NULL,
    st_name VARCHAR2(20) NOT NULL,
    gr_id NUMBER NOT NULL,
    enter_date timestamp,
    change_date timestamp,
    change_type VARCHAR2(6),
    CONSTRAINT stud_logs_id_pk PRIMARY KEY (action_id)
);
/
CREATE TABLE reports_logs (
    id NUMBER GENERATED ALWAYS AS IDENTITY,
    report_date timestamp,
    CONSTRAINT pk_reports_logs PRIMARY KEY (id)
);
/