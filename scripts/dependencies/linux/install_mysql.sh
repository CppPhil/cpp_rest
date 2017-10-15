#!/bin/bash

export DEBIAN_FRONTEND="noninteractive"
debconf-set-selections <<< "mysql-server mysql-server/root_password password mysql"
debconf-set-selections <<< "mysql-server mysql-server/root_password_again password mysql"
sudo apt-get -y install mysql-server-5.5
sudo chmod -R 755 /val/lib/mysql/
sudo apt-get install libmysqlclient-dev
sudo service mysql restart
mysql --user=root --password=mysql < ./scripts/sql/setup_db.sql

