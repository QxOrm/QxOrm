
CREATE TABLE `author` (`author_id` VARCHAR(255) NOT NULL, `name` TEXT, `birthdate` TIMESTAMP, `sex` INTEGER, PRIMARY KEY (`author_id`));
CREATE TABLE `blog` (`blog_id` INTEGER NOT NULL AUTO_INCREMENT, `title` TEXT, `blog_text` TEXT, `date_creation` DATE, `author_id` TEXT, PRIMARY KEY (`blog_id`));
CREATE TABLE `category` (`category_id` INTEGER NOT NULL AUTO_INCREMENT, `name` TEXT, `description` TEXT, PRIMARY KEY (`category_id`));
CREATE TABLE `comment` (`comment_id` INTEGER NOT NULL AUTO_INCREMENT, `title` TEXT, `comment_text` TEXT, `date_creation` DATE, `blog_id` INTEGER, PRIMARY KEY (`comment_id`));
CREATE TABLE t_qxee_blog_category (blog_id INTEGER, category_id INTEGER);
CREATE INDEX idx_author_birthdate ON `author` (`birthdate`);
CREATE INDEX idx_blog_title ON `blog` (`title`(255));
ALTER TABLE `blog` ADD CONSTRAINT fk_blog_author_id FOREIGN KEY (`author_id`) REFERENCES `author` (`author_id`);
ALTER TABLE t_qxee_blog_category ADD CONSTRAINT fk_blog_list_category FOREIGN KEY (blog_id) REFERENCES `blog` (`blog_id`);
ALTER TABLE t_qxee_blog_category ADD CONSTRAINT fk_category_list_of_blog FOREIGN KEY (category_id) REFERENCES `category` (`category_id`);
ALTER TABLE `comment` ADD CONSTRAINT fk_comment_blog_id FOREIGN KEY (`blog_id`) REFERENCES `blog` (`blog_id`);

