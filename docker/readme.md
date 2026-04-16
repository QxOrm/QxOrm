## Try QxOrm with Docker
Run QxOrm in a few seconds with [Docker](https://www.docker.com/) (no build required).
Prerequisites :
- Docker
- Docker Compose

### Quick demo (pre-built images)
This demo runs a complete [C++ backend with QxOrm library and MariaDB database](https://github.com/QxOrm/QxOrm/tree/master/docker/demo/compose_qxorm_with_mariadb) :
```
curl -L -O https://raw.githubusercontent.com/QxOrm/QxOrm/master/docker/demo/compose_qxorm_with_mariadb/compose_demo_qxorm_with_mariadb.yaml
docker compose -f compose_demo_qxorm_with_mariadb.yaml up -d
```
This starts a ready-to-use backend with a connected database. Check the [demo README](https://github.com/QxOrm/QxOrm/tree/master/docker/demo/compose_qxorm_with_mariadb) for detailed results, executed queries, and expected output.

Other database demos :
- [MongoDB](https://github.com/QxOrm/QxOrm/tree/master/docker/demo/compose_qxorm_with_mongodb)
- [PostgreSQL](https://github.com/QxOrm/QxOrm/tree/master/docker/demo/compose_qxorm_with_postgresql)
- [MySQL](https://github.com/QxOrm/QxOrm/tree/master/docker/demo/compose_qxorm_with_mysql)
- [SQLite](https://github.com/QxOrm/QxOrm/tree/master/docker/demo/compose_qxorm_with_sqlite)

### Advanced (full C++ development environment)
Go further with a complete development setup :
- Debug-ready backend
- VS Code Remote / Dev Containers support

Example with [MariaDB database](https://github.com/QxOrm/QxOrm/tree/master/docker/dev/compose_qxorm_with_mariadb) :
```
git clone https://github.com/QxOrm/QxOrm.git
cd QxOrm/docker/dev/compose_qxorm_with_mariadb/
docker compose up -d
```
Check the [demo README](https://github.com/QxOrm/QxOrm/tree/master/docker/dev/compose_qxorm_with_mariadb) for details, including how to connect using Visual Studio Code, as well as executed queries and expected output.

Other C++ development environments are available for :
- [MongoDB](https://github.com/QxOrm/QxOrm/tree/master/docker/dev/compose_qxorm_with_mongodb)
- [PostgreSQL](https://github.com/QxOrm/QxOrm/tree/master/docker/dev/compose_qxorm_with_postgresql)
- [MySQL](https://github.com/QxOrm/QxOrm/tree/master/docker/dev/compose_qxorm_with_mysql)
- [SQLite](https://github.com/QxOrm/QxOrm/tree/master/docker/dev/compose_qxorm_with_sqlite)
