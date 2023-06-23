DROP SCHEMA IF EXISTS tp CASCADE;

CREATE SCHEMA IF NOT EXISTS tp;


CREATE TABLE IF NOT EXISTS tp.users (
    id SERIAL PRIMARY KEY,
    nickname VARCHAR NOT NULL,
    fullname VARCHAR NOT NULL,
    about TEXT,
    email VARCHAR NOT NULL
);

CREATE UNIQUE INDEX IF NOT EXISTS lower_user_nickname ON tp.users (lower(nickname));

CREATE UNIQUE INDEX IF NOT EXISTS lower_user_email    ON tp.users (lower(email));


CREATE TABLE IF NOT EXISTS tp.forums (
    id SERIAL PRIMARY KEY,
    title VARCHAR NOT NULL,
    slug VARCHAR NOT NULL,
    posts INTEGER DEFAULT 0,
    threads INTEGER DEFAULT 0,

    user_id INTEGER REFERENCES tp.users NOT NULL 
);

CREATE UNIQUE INDEX IF NOT EXISTS lower_forum_slug ON tp.forums (lower(slug));


CREATE TABLE IF NOT EXISTS tp.threads(
    id SERIAL PRIMARY KEY,
    title VARCHAR NOT NULL,
    slug VARCHAR,
    message VARCHAR NOT NULL,
    votes INTEGER DEFAULT 0,
    created_at TIMESTAMPTZ NOT NULL DEFAULT NOW(),
    
    forum_id INTEGER REFERENCES tp.forums NOT NULL,
    user_id INTEGER REFERENCES tp.users NOT NULL 
);

CREATE UNIQUE INDEX IF NOT EXISTS lower_thread_slug ON tp.threads (lower(slug));

CREATE TABLE IF NOT EXISTS tp.posts (
    id SERIAL PRIMARY KEY,
    message VARCHAR NOT NULL,
    is_edited BOOLEAN DEFAULT FALSE,
    created_at TIMESTAMPTZ DEFAULT NOW(),
    path INTEGER[] NOT NULL,

    thread_id INTEGER REFERENCES tp.threads NOT NULL,
    user_id INTEGER REFERENCES tp.users NOT NULL, 
    parent_id INTEGER NOT NULL DEFAULT 0
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


CREATE OR REPLACE FUNCTION post_update_path() RETURNS TRIGGER AS $$
BEGIN
    IF (NEW.parent_id = 0) THEN
        NEW.path = ARRAY[NEW.id];
        return NEW;
    END IF;

    IF (NEW.thread_id != (SELECT thread_id FROM tp.posts WHERE id = NEW.parent_id)) THEN
        RAISE EXCEPTION 'Wrong Parent or wrong ThreadId' USING ERRCODE = '25565';
    END IF;

    NEW.path = (SELECT path FROM tp.posts WHERE id = NEW.parent_id) || NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER before_post_insertion
    BEFORE INSERT ON tp.posts
    FOR EACH ROW EXECUTE PROCEDURE post_update_path();
