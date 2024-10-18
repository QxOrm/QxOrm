
CREATE TABLE author (author_id VARCHAR(255) NOT NULL PRIMARY KEY, name TEXT, birthdate DATETIME, sex INT);
CREATE TABLE blog (blog_id INT NOT NULL PRIMARY KEY IDENTITY(1,1), title VARCHAR(900), blog_text TEXT, date_creation DATE, author_id TEXT);
CREATE TABLE category (category_id INT NOT NULL PRIMARY KEY IDENTITY(1,1), name TEXT, description TEXT);
CREATE TABLE comment (comment_id INT NOT NULL PRIMARY KEY IDENTITY(1,1), title TEXT, comment_text TEXT, date_creation DATE, blog_id INT);
CREATE TABLE t_qxee_blog_category (blog_id INT, category_id INT);
CREATE INDEX idx_author_birthdate ON author (birthdate);
CREATE INDEX idx_blog_title ON blog (title);
ALTER TABLE blog ADD CONSTRAINT fk_blog_author_id FOREIGN KEY (author_id) REFERENCES author (author_id);
ALTER TABLE t_qxee_blog_category ADD CONSTRAINT fk_blog_list_category FOREIGN KEY (blog_id) REFERENCES blog (blog_id);
ALTER TABLE t_qxee_blog_category ADD CONSTRAINT fk_category_list_of_blog FOREIGN KEY (category_id) REFERENCES category (category_id);
ALTER TABLE comment ADD CONSTRAINT fk_comment_blog_id FOREIGN KEY (blog_id) REFERENCES blog (blog_id);

