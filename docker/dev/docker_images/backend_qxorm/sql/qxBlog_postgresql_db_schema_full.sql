
CREATE TABLE author (author_id TEXT NOT NULL PRIMARY KEY, name TEXT, birthdate TIMESTAMP, sex INTEGER) WITH (OIDS = FALSE);
CREATE TABLE blog (blog_id BIGSERIAL NOT NULL PRIMARY KEY, title TEXT, blog_text TEXT, date_creation DATE, author_id TEXT) WITH (OIDS = FALSE);
CREATE TABLE category (category_id BIGSERIAL NOT NULL PRIMARY KEY, name TEXT, description TEXT) WITH (OIDS = FALSE);
CREATE TABLE comment (comment_id BIGSERIAL NOT NULL PRIMARY KEY, title TEXT, comment_text TEXT, date_creation DATE, blog_id INTEGER) WITH (OIDS = FALSE);
CREATE TABLE t_qxee_blog_category (blog_id BIGSERIAL, category_id BIGSERIAL) WITH (OIDS = FALSE);
CREATE INDEX idx_author_birthdate ON author (birthdate);
CREATE INDEX idx_blog_title ON blog (title);
ALTER TABLE blog ADD CONSTRAINT fk_blog_author_id FOREIGN KEY (author_id) REFERENCES author (author_id);
ALTER TABLE t_qxee_blog_category ADD CONSTRAINT fk_blog_list_category FOREIGN KEY (blog_id) REFERENCES blog (blog_id);
ALTER TABLE t_qxee_blog_category ADD CONSTRAINT fk_category_list_of_blog FOREIGN KEY (category_id) REFERENCES category (category_id);
ALTER TABLE comment ADD CONSTRAINT fk_comment_blog_id FOREIGN KEY (blog_id) REFERENCES blog (blog_id);

