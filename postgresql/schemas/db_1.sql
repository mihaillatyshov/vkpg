DROP SCHEMA IF EXISTS tp CASCADE;

CREATE SCHEMA IF NOT EXISTS tp;

CREATE TABLE IF NOT EXISTS tp.users (
    id SERIAL PRIMARY KEY,
    nickname VARCHAR NOT NULL,
    fullname VARCHAR NOT NULL,
    about TEXT,
    email VARCHAR NOT NULL
);

CREATE UNIQUE INDEX ON tp.users (lower(nickname));

create unique INDEX ON tp.users (lower(email));


CREATE TABLE IF NOT EXISTS tp.forums (
    id SERIAL PRIMARY KEY,
    title VARCHAR NOT NULL,
    slug VARCHAR UNIQUE NOT NULL,
    posts INTEGER DEFAULT 0,
    threads INTEGER DEFAULT 0,

    user_id INTEGER REFERENCES tp.users NOT NULL 
);

CREATE TABLE IF NOT EXISTS tp.threads(
    id SERIAL PRIMARY KEY,
    title VARCHAR NOT NULL,
    slug VARCHAR UNIQUE,
    message VARCHAR NOT NULL,
    votes INTEGER DEFAULT 0,
    created_at TIMESTAMPTZ NOT NULL DEFAULT NOW(),
    
    forum_id INTEGER REFERENCES tp.forums NOT NULL,
    user_id INTEGER REFERENCES tp.users NOT NULL 
);

CREATE TABLE IF NOT EXISTS tp.posts (
    id SERIAL PRIMARY KEY,
    message VARCHAR NOT NULL,
    is_edited BOOLEAN DEFAULT FALSE,
    created_at TIMESTAMPTZ DEFAULT NOW(),
    path INTEGER[] NOT NULL,

    thread_id INTEGER REFERENCES tp.threads NOT NULL,
    user_id INTEGER REFERENCES tp.users NOT NULL, 
    parent_id INTEGER REFERENCES tp.posts NOT NULL
);

CREATE TABLE IF NOT EXISTS tp.forums_users (
    id SERIAL PRIMARY KEY,
    forum_id INTEGER REFERENCES tp.forums NOT NULL,
    user_id INTEGER REFERENCES tp.users NOT NULL,
    UNIQUE (forum_id, user_id) 
);

CREATE TABLE IF NOT EXISTS tp.votes (
    id SERIAL PRIMARY KEY,
    voice INTEGER NOT NULL,  --  1: like; -1: dislike
    
    thread_id INTEGER REFERENCES tp.threads NOT NULL,
    user_id INTEGER REFERENCES tp.users NOT NULL, 
    UNIQUE (thread_id, user_id) 
);
