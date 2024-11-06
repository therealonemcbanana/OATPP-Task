CREATE TABLE Notes (
    id                 INTEGER PRIMARY KEY autoincrement,
    name               VARCHAR,
    phone_number       VARCHAR UNIQUE,
    address            VARCHAR
);