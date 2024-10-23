REM -- DEFINE QXORM VERSION FOR DOCKER TAGS --
SET QX_VERSION=1.5.1

@ECHO OFF

REM -- DOCKER STOP ALL QXORM CONTAINERS --
FOR /f "tokens=*" %%i IN ('docker ps -q') DO docker stop %%i

REM -- DOCKER CLEAR DATA CACHE IMAGES --
FOR /f "tokens=*" %%i IN ('docker images -f "dangling=true" -q') DO docker rmi -f %%i
FOR /f "tokens=*" %%i IN ('docker images "qxorm\/*" -q') DO docker rmi -f %%i

docker network prune -f
docker volume prune -f
docker buildx prune -f
docker builder prune -f
docker system prune -f

@ECHO ON

REM -- DOCKER BUILD TEST QXBLOGRESTAPI --
cd ../docker/test/qxBlogRestApi/
docker build -t qxorm/ubuntu-with-qxorm-test-qxblogrestapi:%QX_VERSION% .

REM -- DOCKER BUILD DEV QXBLOGRESTAPI --
docker build --target dev -t qxorm/ubuntu-with-qxorm-dev-qxblogrestapi:%QX_VERSION% .

REM -- DOCKER COMPOSE QXORM WITH MARIADB --
cd ../../dev/compose_qxorm_with_mariadb/
docker compose build --build-arg "QX_VERSION=%QX_VERSION%"

REM -- DOCKER COMPOSE QXORM WITH MONGODB --
cd ../compose_qxorm_with_mongodb/
docker compose build --build-arg "QX_VERSION=%QX_VERSION%"

REM -- DOCKER COMPOSE QXORM WITH MYSQL --
cd ../compose_qxorm_with_mysql/
docker compose build --build-arg "QX_VERSION=%QX_VERSION%"

REM -- DOCKER COMPOSE QXORM WITH POSTGRESQL --
cd ../compose_qxorm_with_postgresql/
docker compose build --build-arg "QX_VERSION=%QX_VERSION%"

REM -- DOCKER COMPOSE QXORM WITH SQLITE --
cd ../compose_qxorm_with_sqlite/
docker compose build --build-arg "QX_VERSION=%QX_VERSION%"

REM -- DEFINE LATEST TAG FOR ALL DOCKER IMAGES --
docker tag qxorm/ubuntu-with-qxorm-test-qxblogrestapi:%QX_VERSION% qxorm/ubuntu-with-qxorm-test-qxblogrestapi:latest
docker tag qxorm/ubuntu-with-qxorm-dev-qxblogrestapi:%QX_VERSION% qxorm/ubuntu-with-qxorm-dev-qxblogrestapi:latest

docker tag qxorm/compose_qxorm_with_mariadb-nginx_reverse_proxy:%QX_VERSION% qxorm/compose_qxorm_with_mariadb-nginx_reverse_proxy:latest
docker tag qxorm/compose_qxorm_with_mariadb-frontend_html_js_css:%QX_VERSION% qxorm/compose_qxorm_with_mariadb-frontend_html_js_css:latest
docker tag qxorm/compose_qxorm_with_mariadb-backend_qxorm:%QX_VERSION% qxorm/compose_qxorm_with_mariadb-backend_qxorm:latest
docker tag qxorm/compose_qxorm_with_mariadb-db_mariadb:%QX_VERSION% qxorm/compose_qxorm_with_mariadb-db_mariadb:latest

docker tag qxorm/compose_qxorm_with_mongodb-nginx_reverse_proxy:%QX_VERSION% qxorm/compose_qxorm_with_mongodb-nginx_reverse_proxy:latest
docker tag qxorm/compose_qxorm_with_mongodb-frontend_html_js_css:%QX_VERSION% qxorm/compose_qxorm_with_mongodb-frontend_html_js_css:latest
docker tag qxorm/compose_qxorm_with_mongodb-backend_qxorm:%QX_VERSION% qxorm/compose_qxorm_with_mongodb-backend_qxorm:latest
docker tag qxorm/compose_qxorm_with_mongodb-db_mongodb:%QX_VERSION% qxorm/compose_qxorm_with_mongodb-db_mongodb:latest

docker tag qxorm/compose_qxorm_with_mysql-nginx_reverse_proxy:%QX_VERSION% qxorm/compose_qxorm_with_mysql-nginx_reverse_proxy:latest
docker tag qxorm/compose_qxorm_with_mysql-frontend_html_js_css:%QX_VERSION% qxorm/compose_qxorm_with_mysql-frontend_html_js_css:latest
docker tag qxorm/compose_qxorm_with_mysql-backend_qxorm:%QX_VERSION% qxorm/compose_qxorm_with_mysql-backend_qxorm:latest
docker tag qxorm/compose_qxorm_with_mysql-db_mysql:%QX_VERSION% qxorm/compose_qxorm_with_mysql-db_mysql:latest

docker tag qxorm/compose_qxorm_with_postgresql-nginx_reverse_proxy:%QX_VERSION% qxorm/compose_qxorm_with_postgresql-nginx_reverse_proxy:latest
docker tag qxorm/compose_qxorm_with_postgresql-frontend_html_js_css:%QX_VERSION% qxorm/compose_qxorm_with_postgresql-frontend_html_js_css:latest
docker tag qxorm/compose_qxorm_with_postgresql-backend_qxorm:%QX_VERSION% qxorm/compose_qxorm_with_postgresql-backend_qxorm:latest
docker tag qxorm/compose_qxorm_with_postgresql-db_postgresql:%QX_VERSION% qxorm/compose_qxorm_with_postgresql-db_postgresql:latest

docker tag qxorm/compose_qxorm_with_sqlite-nginx_reverse_proxy:%QX_VERSION% qxorm/compose_qxorm_with_sqlite-nginx_reverse_proxy:latest
docker tag qxorm/compose_qxorm_with_sqlite-frontend_html_js_css:%QX_VERSION% qxorm/compose_qxorm_with_sqlite-frontend_html_js_css:latest
docker tag qxorm/compose_qxorm_with_sqlite-backend_qxorm:%QX_VERSION% qxorm/compose_qxorm_with_sqlite-backend_qxorm:latest

pause
