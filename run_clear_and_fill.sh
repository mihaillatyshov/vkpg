#!/bin/bash
psql 'postgresql://postgres:postgres@localhost:5432/forum' -f ./postgresql/schemas/db_1.sql
cd tests
python3 fill_db.py