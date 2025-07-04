CREATE TABLE aaa (
    id NUMBER GENERATED BY DEFAULT ON NULL AS IDENTITY,
    name VARCHAR2(6),
    bbb_id NUMBER NOT NULL,
    CONSTRAINT aaa_id_pk PRIMARY KEY (id)
);

CREATE TABLE bbb (
    id NUMBER GENERATED BY DEFAULT ON NULL AS IDENTITY,
    name VARCHAR2(30),
    aaa_id NUMBER NOT NULL,
    CONSTRAINT bbb_id_pk PRIMARY KEY (id)
);

insert into aaa values(1, 'a1', 1);
insert into aaa values(2, 'a2', 1);
insert into aaa values(3, 'a3', 1);
insert into aaa values(4, 'a3', 1);
insert into aaa values(5, 'a5', 1);


insert into bbb values(1, 'b1', 1);
insert into bbb values(2, 'b2', 1);
insert into bbb values(3, 'b3', 1);
insert into bbb values(4, 'b3', 1);
insert into bbb values(5, 'b3', 1);

--drop table aaa;
--drop table bbb;

SELECT * from aaa;
SELECT * from bbb;