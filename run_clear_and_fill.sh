#!/bin/bash
psql 'postgresql://postgres:postgres@localhost:5432/forum' -f ./postgresql/schemas/db_1.sql
cd tests
echo " "

echo "-- Users"
python3 -m unittest -v fill_user.py
echo " "

echo "-- Forums"
python3 -m unittest -v fill_forum.py
echo " "
