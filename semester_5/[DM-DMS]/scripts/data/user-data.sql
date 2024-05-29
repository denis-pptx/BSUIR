USE library;

-- Action types
INSERT INTO action_type (id, name)
VALUES 
	(1, 'REGISTRATION'),
    (2, 'LOG IN'),
    (3, 'LOG OUT'),
    (4, 'USER ADDED');
    
-- Default users 
INSERT INTO user (id, username, password, email)
VALUES
    (1, 'john_doe', 'b24e3e21870645af14da826d4cb300c0f4f877c308efa30ff084f976f191aafb', 'john.doe@qwe.com'),
    (2, 'alice_smith', 'ce22191277eef4735bf5dce2d0bcc6b7c526cb36f3795c20f2aa8c29cb16d236', 'alice.smith@example.com'),
    (3, 'bob_jones', '4ddf4778cf223a0bea47eb4390a9ca51010fc8e17885f20448974bac05f12e38', 'bob.jones@bsuir.by'),
    (4, 'emma_wilson', '6ffbabd7f90f6566a29dcb13b331d77454199c4f01f67ca261e5a831d868d9b9', 'emma.wilson@example.com'),
    (5, 'michael_brown', '6c923030dc41c38da9cbe1ab6a40220f788554c9c1edbbe7487e2ea8e10ab857', 'michael.brown@example.com'),
    (6, 'olivia_davis', '84dc6cae4d6ee39234f484ab0a442f9e0a80f1212d49329eab1399379d7efef4', 'olivia.davis@example.com'),
    (7, 'william_miller', '074a4ffda60a27426ff9dd14abbaf10c410eb7a399f81e8740c8d7e33a1c4349', 'william.miller@inbox.ru'),
    (8, 'sophia_johnson', '76a8bc556e9ef0f07ab5b1535e65a70f7dd2fb0c6eaedff63201243ad5dca1a6', 'sophia.johnson@mail.ru'),
    (9, 'james_anderson', '0887f662f3ba57f7bedc525514a0ffe185e3dfaa41c6a648fcbcbdd4428529c9', 'james.anderson@gmail.com'),
    (10, 'emily_clark', '5c3c89549d70f4af4487430747e1ef4a0a4780ac0f5f3a506af0113fd7a39f77', 'emily.clark@gmail.com');

-- Profiles for default users
INSERT INTO user_profile (user_id, first_name, last_name, birth_date)
VALUES
    (1, 'John', 'Doe', '1990-05-15'),
    (2, 'Alice', 'Smith', '1985-12-10'),
    (3, 'Bob', 'Jones', '1988-08-20'),
    (4, 'Emma', 'Wilson', '1948-11-20'),
    (5, 'Michael', 'Brown', '1987-07-05'),
    (6, 'Olivia', 'Davis', '1991-09-12'),
    (7, 'William', 'Miller', '1996-02-14'),
    (8, 'Sophia', 'Johnson', '1993-02-18'),
    (9, 'James', 'Anderson', '1986-06-08'),
    (10, 'Emily', 'Clark', '1994-04-02');
    
-- Superusers
INSERT INTO user (username, password, email, is_admin) 
VALUES
	('denisko', '10a6e6cc8311a3e2bcc09bf6c199adecd5dd59408c343e926b129c4914f3cb01', 'denis.pptx@gmail.com', 1); # pass - test_password
    
-- Actions
INSERT INTO action (timestamp, description, action_type_id, user_id)
VALUES
    ('2023-09-01 08:00:00', 'User registered', 1, 1),
    ('2023-09-01 09:30:00', 'User logged in', 2, 1),
    ('2023-09-01 12:45:00', 'User logged out', 3, 1),
    ('2023-09-02 10:15:00', 'User registered', 1, 2),
    ('2023-09-02 14:20:00', 'User logged in', 2, 2),
    ('2023-09-02 17:30:00', 'User logged out', 3, 2),
    ('2023-09-03 11:00:00', 'User registered', 1, 3),
    ('2023-09-03 14:45:00', 'User logged in', 2, 3),
    ('2023-09-03 18:20:00', 'User logged out', 3, 3),
    ('2023-09-04 09:30:00', 'User registered', 1, 4),
    ('2023-09-04 11:15:00', 'User logged in', 2, 4),
    ('2023-09-04 14:00:00', 'User logged out', 3, 4),
    ('2023-09-05 08:45:00', 'User registered', 1, 5),
    ('2023-09-05 10:30:00', 'User logged in', 2, 5),
    ('2023-09-05 13:15:00', 'User logged out', 3, 5),
    ('2023-09-06 12:00:00', 'User registered', 1, 6),
    ('2023-09-06 14:45:00', 'User logged in', 2, 6),
    ('2023-09-06 17:30:00', 'User logged out', 3, 6),
    ('2023-09-07 08:30:00', 'User registered', 1, 7),
    ('2023-09-07 10:45:00', 'User logged in', 2, 7);