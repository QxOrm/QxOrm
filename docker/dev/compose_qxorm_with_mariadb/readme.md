# C++ development environment with QxOrm library and MariaDB database
[This Docker compose file](https://github.com/QxOrm/QxOrm/blob/master/docker/dev/compose_qxorm_with_mariadb/compose.yaml) builds a development environment to create web applications with very efficient C++ backend based on [Qt framework](https://www.qt.io/) and [QxOrm library](https://www.qxorm.com/).

## Project structure
[This Docker compose file](https://github.com/QxOrm/QxOrm/blob/master/docker/dev/compose_qxorm_with_mariadb/compose.yaml) defines an application with 4 services :
- **nginx_reverse_proxy** : based on latest [nginx](https://nginx.org/en/) official image, this service is the entrypoint for the user to access to the application.
- **frontend_html_js_css** : this is where you can develop great UI using famous HTML/JS/CSS frameworks like [Angular](https://angular.dev/), [React](https://react.dev/), etc...
- **backend_qxorm** : C++ backend based on [Qt framework](https://www.qt.io/) and [QxOrm library](https://www.qxorm.com/).
- **db_mariadb** : [MariaDB database](https://mariadb.org/) to store application data.

![compose_qxorm_with_mariadb](https://www.qxorm.com/qxorm_en/resource/docker_compose_schema.png)

## Deploy with docker compose
```
cd <path_to_this_docker_compose_file>
docker compose up -d
```
```
[+] Running 8/8
 ✔ Network compose_qxorm_with_mariadb_compose_qxorm_with_mariadb_frontnet  Created                                                                                                                  0.1s
 ✔ Network compose_qxorm_with_mariadb_compose_qxorm_with_mariadb_backnet   Created                                                                                                                  0.0s
 ✔ Volume "compose_qxorm_with_mariadb_qxorm_backend_src"                   Created                                                                                                                  0.0s
 ✔ Volume "compose_qxorm_with_mariadb_mariadb_db_data"                     Created                                                                                                                  0.0s
 ✔ Container compose_qxorm_with_mariadb-db_mariadb-1                       Started                                                                                                                  1.7s
 ✔ Container compose_qxorm_with_mariadb-frontend_html_js_css-1             Started                                                                                                                  1.7s
 ✔ Container compose_qxorm_with_mariadb-backend_qxorm-1                    Started                                                                                                                  1.9s
 ✔ Container compose_qxorm_with_mariadb-nginx_reverse_proxy-1              Started                                                                                                                  1.2s
```

## Expected result
Listing containers should show 4 containers running and the port mapping as below :
```
docker compose ps
```
```
NAME                                                IMAGE                                                          COMMAND                  SERVICE                CREATED              STATUS                        PORTS
compose_qxorm_with_mariadb-backend_qxorm-1          qxorm/compose_qxorm_with_mariadb-backend_qxorm:latest          "./entrypoint.sh ssh…"   backend_qxorm          About a minute ago   Up About a minute             9642-9643/tcp, 0.0.0.0:2222->22/tcp
compose_qxorm_with_mariadb-db_mariadb-1             qxorm/compose_qxorm_with_mariadb-db_mariadb:latest             "docker-entrypoint.s…"   db_mariadb             About a minute ago   Up About a minute             3306/tcp
compose_qxorm_with_mariadb-frontend_html_js_css-1   qxorm/compose_qxorm_with_mariadb-frontend_html_js_css:latest   "./entrypoint.sh"        frontend_html_js_css   About a minute ago   Up About a minute             80/tcp
compose_qxorm_with_mariadb-nginx_reverse_proxy-1    qxorm/compose_qxorm_with_mariadb-nginx_reverse_proxy:latest    "./entrypoint.sh"        nginx_reverse_proxy    About a minute ago   Up About a minute (healthy)   80/tcp, 0.0.0.0:8080-8081->8080-8081/tcp
```

### Test application
Once Docker containers are running, on the host machine open a web-browser and go to :
```
http://localhost:8080
```

![qxBlogRestApi web application](https://www.qxorm.com/qxorm_en/resource/qx_blog_rest_api_http_01.png)

The sample application is [qxBlogRestApi](https://github.com/QxOrm/QxOrm/tree/master/test/qxBlogRestApi) based on [QxOrm library](https://www.qxorm.com/).
You can select a pre-defined request to send to the C++ backend in JSON format, or you can write your own JSON request.
The [JSON API](https://www.qxorm.com/qxorm_en/manual.html#manual_97) is explained in [QxOrm documentation](https://www.qxorm.com/qxorm_en/manual.html).

## Build and debug C++ Qt QxOrm backend in container
The C++ Qt QxOrm backend is based on [this Docker file](https://github.com/QxOrm/QxOrm/tree/master/docker/test/qxBlogRestApi).
A full C++ development environment (to build and debug) is available, you can connect to this dev environment with [Visual Studio Code](https://code.visualstudio.com/).
Visual Studio Code provides 2 extensions : [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension and [Remote SSH](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-ssh) extension (choose one of them).

### Connect to the container with VSCode 'Dev Containers' extension
To connect to the C++ development environment with the [Dev Containers](https://code.visualstudio.com/docs/devcontainers/tutorial) extension :
- On the host machine, open [Visual Studio Code](https://code.visualstudio.com/)
- Install the [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension
- Select workspace (open directory) : path to this docker compose file (which includes a sub-directory named '.devcontainer')
- Visual Studio Code detects automatically the '.devcontainer' sub-directory and provides the action 'Reopen in Container'
- Execute 'Reopen in Container' ==> a new Visual Studio Code instance is created, this new instance is connected to the running Docker container

### Connect to the container with VSCode 'Remote SSH' extension
To connect to the C++ development environment with the [Remote SSH](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-ssh) extension :
- On the host machine, open [Visual Studio Code](https://code.visualstudio.com/)
- Install the [Remote SSH](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-ssh) extension
- From the Remote SSH extension, execute :
```
ssh qxorm@localhost -p 2222
```
- When asked, enter password : _qxorm_
- A new Visual Studio Code instance is created, this new instance is connected to the running Docker container
- On the remote Visual Studio Code instance, select workspace (open directory) :
```
/home/qxorm/src/QxOrm/
```

### Build and debug project in container
Once connected to the remote C++ development environment (with [Dev Containers](https://code.visualstudio.com/docs/devcontainers/tutorial) extension or [Remote SSH](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-ssh) extension) :
```
- Press 'CTRL+SHIFT+B' to build the project in debug mode
- Press 'F5' to execute the project in debug mode
```

After the application starts in **DEBUG mode**, on the host machine open a web-browser and go to :
```
http://localhost:8081
```

## Stop and remove the containers
```
docker compose down
```

## About QxOrm library
[QxOrm library](https://www.qxorm.com/) is a C++ library based on Qt framework, its main features are : [ORM persistence](https://www.qxorm.com/qxorm_en/manual.html#manual_30), [serialization](https://www.qxorm.com/qxorm_en/manual.html#manual_60), [reflection](https://www.qxorm.com/qxorm_en/manual.html#manual_70), [introspection](https://www.qxorm.com/qxorm_en/manual.html#manual_70), [JSON API](https://www.qxorm.com/qxorm_en/manual.html#manual_97), [HTTP web server](https://www.qxorm.com/qxorm_en/manual.html#manual_96).
QxOrm library supports most common databases like **SQLite**, **MySQL**, **PostgreSQL**, **Oracle**, **MS SQL Server**, **MongoDB**, **MariaDB**.
QxOrm library documentation : https://www.qxorm.com/qxorm_en/manual.html

## About QxEntityEditor application
[QxEntityEditor application](https://www.qxorm.com/qxorm_en/manual_qxee.html) (available on Windows, Linux and macOS) is a graphic editor for QxOrm library.
QxEntityEditor provides a graphic way to manage the data model, and generates native source code for all environments.
QxEntityEditor is based on plugins and provides many ways to import/export your data model :
- [generate C++ persistent classes](https://www.qxorm.com/qxorm_en/manual_qxee.html#cpp_export_settings) automatically (registered in QxOrm context).
- [import existing database structure](https://www.qxorm.com/qxorm_en/manual_qxee.html#wnd_mysql_import) (using ODBC connection or native drivers) for SQLite, MySQL, PostgreSQL, Oracle and MS SQL Server databases.
- [generate DDL SQL script](https://www.qxorm.com/qxorm_en/manual_qxee.html#ddl_export_settings) automatically (database schema) for SQLite, MySQL, PostgreSQL, Oracle and MS SQL Server.

![QxOrm library and QxEntityEditor application](https://www.qxorm.com/qxorm_en/resource/logo_qxorm_and_qxee.png)

## Authors
QxOrm is developed by Lionel Marty, a software development engineer since 2003.

## License
QxOrm is a C++ library available under a dual license :
- [GNU/GPLv3 license](https://www.qxorm.com/qxorm_en/resource/license.gpl3.txt) : open-source and free (to develop an open-source project or to evaluate QxOrm library) ;
- [Proprietary license](https://www.qxorm.com/qxorm_en/download_details.php) to distribute an application based on QxOrm library without any restrictions of GNU/GPLv3 license.
