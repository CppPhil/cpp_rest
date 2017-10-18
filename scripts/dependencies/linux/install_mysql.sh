#!/bin/bash

sudo apt-get -y install mysql-client
export DEBIAN_FRONTEND="noninteractive"
debconf-set-selections <<< "mysql-server mysql-server/root_password password mysql"
debconf-set-selections <<< "mysql-server mysql-server/root_password_again password mysql"
sudo apt-get -y install mysql-server
sudo apt-get -y install default-libmysqlclient-dev
sudo service mysql restart
mysql --user=root --password="mysql" < ./scripts/sql/setup_db.sql

