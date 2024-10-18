
CREATE TABLE author (author_id VARCHAR2(4000) NOT NULL PRIMARY KEY, name CLOB, birthdate TIMESTAMP, sex INTEGER);
CREATE TABLE blog (blog_id INTEGER NOT NULL PRIMARY KEY, title VARCHAR2(4000), blog_text CLOB, date_creation DATE, author_id CLOB);
CREATE SEQUENCE seq_inc_blog START WITH 1 INCREMENT BY 1;
CREATE OR REPLACE TRIGGER trigger_inc_blog
	BEFORE INSERT OR UPDATE OF blog_id ON blog
	FOR EACH ROW
	BEGIN
		IF ( :NEW.blog_id = 0 OR :NEW.blog_id IS NULL ) THEN
			SELECT seq_inc_blog.NEXTVAL INTO :NEW.blog_id FROM DUAL;
		END IF;
	END;
	/

CREATE TABLE category (category_id INTEGER NOT NULL PRIMARY KEY, name CLOB, description CLOB);
CREATE SEQUENCE seq_inc_category START WITH 1 INCREMENT BY 1;
CREATE OR REPLACE TRIGGER trigger_inc_category
	BEFORE INSERT OR UPDATE OF category_id ON category
	FOR EACH ROW
	BEGIN
		IF ( :NEW.category_id = 0 OR :NEW.category_id IS NULL ) THEN
			SELECT seq_inc_category.NEXTVAL INTO :NEW.category_id FROM DUAL;
		END IF;
	END;
	/

CREATE TABLE comment (comment_id INTEGER NOT NULL PRIMARY KEY, title CLOB, comment_text CLOB, date_creation DATE, blog_id INTEGER);
CREATE SEQUENCE seq_inc_comment START WITH 1 INCREMENT BY 1;
CREATE OR REPLACE TRIGGER trigger_inc_comment
	BEFORE INSERT OR UPDATE OF comment_id ON comment
	FOR EACH ROW
	BEGIN
		IF ( :NEW.comment_id = 0 OR :NEW.comment_id IS NULL ) THEN
			SELECT seq_inc_comment.NEXTVAL INTO :NEW.comment_id FROM DUAL;
		END IF;
	END;
	/

CREATE TABLE t_qxee_blog_category (blog_id INTEGER, category_id INTEGER);
CREATE INDEX idx_author_birthdate ON author (birthdate);
CREATE INDEX idx_blog_title ON blog (title);
ALTER TABLE blog ADD CONSTRAINT fk_blog_author_id FOREIGN KEY (author_id) REFERENCES author (author_id);
ALTER TABLE t_qxee_blog_category ADD CONSTRAINT fk_blog_list_category FOREIGN KEY (blog_id) REFERENCES blog (blog_id);
ALTER TABLE t_qxee_blog_category ADD CONSTRAINT fk_category_list_of_blog FOREIGN KEY (category_id) REFERENCES category (category_id);
ALTER TABLE comment ADD CONSTRAINT fk_comment_blog_id FOREIGN KEY (blog_id) REFERENCES blog (blog_id);

