CREATE DATABASE IF NOT EXISTS testdb;
USE testdb;
DROP TABLE IF EXISTS test_type;
CREATE TABLE test_type (
    id MEDIUMINT NOT NULL AUTO_INCREMENT,
    num INTEGER NOT NULL,
    str TEXT NOT NULL,
    PRIMARY KEY (id)
);
GRANT ALL PRIVILEGES ON testdb.* TO testuser@localhost IDENTIFIED BY 'password';
