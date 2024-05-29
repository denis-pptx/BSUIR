
-- C##dev SCHEME
DROP TABLE C##dev.students;

DROP TABLE C##dev.groups;

DROP TABLE C##dev.uni;

CREATE TABLE C##dev.uni (
    uni_id NUMBER NOT NULL,
    uni_name VARCHAR2(20) NOT NULL,
    CONSTRAINT uni_id_pk PRIMARY KEY (uni_id)
);
--CREATE TABLE C##dev.test (
--    test_id NUMBER NOT NULL
--);
CREATE TABLE C##dev.groups (
    gr_id NUMBER NOT NULL,
    gr_name VARCHAR2(20) NOT NULL,
    uni_id NUMBER NOT NULL,
    CONSTRAINT gr_id_pk PRIMARY KEY (gr_id),
    CONSTRAINT uni_id_fk FOREIGN KEY (uni_id) REFERENCES C##dev.uni (uni_id)
);

ALTER TABLE C##dev.groups ADD gr_motto VARCHAR2(200) NOT NULL;

CREATE INDEX gr_motto_idx ON C##dev.groups (gr_motto);

CREATE TABLE C##dev.students (
    st_id NUMBER NOT NULL,
    st_name VARCHAR2(20) NOT NULL,
    gr_id NUMBER NOT NULL,
    CONSTRAINT st_id_pk PRIMARY KEY (st_id),
    CONSTRAINT gr_id_fk FOREIGN KEY (gr_id) REFERENCES C##dev.groups (gr_id)
);

-- DROP LOOPS

ALTER TABLE C##dev.t3 DROP CONSTRAINT fk_3_2;

ALTER TABLE C##dev.account DROP CONSTRAINT h_id_fk;

DROP TABLE C##dev.t1;

DROP TABLE C##dev.t2;

DROP TABLE C##dev.t3;

DROP TABLE C##dev.human;

DROP TABLE C##dev.account;

CREATE TABLE C##dev.human (
    h_id NUMBER NOT NULL,
    acc_id NUMBER UNIQUE NOT NULL,
    CONSTRAINT h_id_pk PRIMARY KEY (h_id)
);

CREATE TABLE C##dev.account (
    acc_id NUMBER NOT NULL,
    h_id NUMBER UNIQUE NOT NULL,
    CONSTRAINT acc_id_pk PRIMARY KEY (acc_id),
    CONSTRAINT h_id_fk FOREIGN KEY (h_id) REFERENCES C##dev.human (h_id)
);

ALTER TABLE C##dev.human ADD CONSTRAINT acc_id_fk FOREIGN KEY (acc_id) REFERENCES C##dev.account (acc_id);

CREATE TABLE C##dev.t1 (
    id NUMBER PRIMARY KEY,
    t3_id NUMBER NOT NULL
);

CREATE TABLE C##dev.t2 (
    id NUMBER PRIMARY KEY
    --t3_id NUMBER NOT NULL
);

CREATE TABLE C##dev.t3 (
    id NUMBER PRIMARY KEY,
    t2_id NUMBER NOT NULL
);

ALTER TABLE C##dev.t1 ADD CONSTRAINT fk_1_3 FOREIGN KEY (t3_id) REFERENCES C##dev.t3 (id);

--ALTER TABLE C##dev.t2 ADD CONSTRAINT fk_2_3 FOREIGN KEY (t3_id) REFERENCES C##dev.t3 (id);

ALTER TABLE C##dev.t3 ADD CONSTRAINT fk_3_2 FOREIGN KEY (t2_id) REFERENCES C##dev.t2 (id);

-- C##prod SCHEME
DROP TABLE C##prod.students;

DROP TABLE C##prod.groups;

DROP TABLE C##prod.uni;

CREATE TABLE C##prod.uni (
    uni_id NUMBER NOT NULL,
    uni_name VARCHAR2(20) NOT NULL,
    CONSTRAINT uni_id_pk PRIMARY KEY (uni_id)
);

CREATE INDEX test_index ON C##prod.students (st_name);

CREATE TABLE C##prod.groups (
    gr_id NUMBER NOT NULL,
    gr_name VARCHAR2(20) NOT NULL,
    uni_id NUMBER NOT NULL,
    st_count NUMBER NOT NULL,
    CONSTRAINT gr_id_pk PRIMARY KEY (gr_id),
    CONSTRAINT uni_id_fk FOREIGN KEY (uni_id) REFERENCES C##prod.uni (uni_id)
);

CREATE TABLE C##prod.students (
    st_id NUMBER NOT NULL,
    st_name VARCHAR2(20) NOT NULL,
    st_surname VARCHAR2(20) NOT NULL,
    gr_id NUMBER NOT NULL,
    CONSTRAINT st_id_pk PRIMARY KEY (st_id),
    CONSTRAINT gr_id_fk FOREIGN KEY (gr_id) REFERENCES C##prod.groups (gr_id)
);

ALTER TABLE C##prod.students ADD CONSTRAINT st_name_length_check CHECK (length(st_name) >= 10);

CREATE INDEX C##prod.denis_ne_sdal ON C##prod.students(st_surname);
CREATE INDEX st_name_idx ON C##prod.students (st_name);


CREATE TABLE C##prod.t1 (
    id NUMBER PRIMARY KEY,
    t3_id NUMBER NOT NULL
);

CREATE TABLE C##prod.t2 (
    id NUMBER PRIMARY KEY
    --t3_id NUMBER NOT NULL
);

CREATE TABLE C##prod.t3 (
    id NUMBER PRIMARY KEY,
    t2_id NUMBER NOT NULL
);

ALTER TABLE C##prod.t1 ADD CONSTRAINT fk_1_3 FOREIGN KEY (t3_id) REFERENCES C##prod.t3 (id);

--ALTER TABLE C##dev.t2 ADD CONSTRAINT fk_2_3 FOREIGN KEY (t3_id) REFERENCES C##dev.t3 (id);

ALTER TABLE C##prod.t3 ADD CONSTRAINT fk_3_2 FOREIGN KEY (t2_id) REFERENCES C##prod.t2 (id);