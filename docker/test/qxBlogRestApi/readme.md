# QxOrm library - Docker file for C++ and Qt development environment - Project qxBlogRestApi
[This Docker file](https://github.com/QxOrm/QxOrm/blob/master/docker/test/qxBlogRestApi/Dockerfile) creates a Docker image based on Ubuntu (latest version by default).
[This Docker file](https://github.com/QxOrm/QxOrm/blob/master/docker/test/qxBlogRestApi/Dockerfile) installs a C++ development environment with gcc, cmake, Qt and builds [QxOrm library](https://www.qxorm.com/) from latest QxOrm source code.

## About QxOrm library
[QxOrm library](https://www.qxorm.com/) is a C++ library based on Qt framework, its main features are : [ORM persistence](https://www.qxorm.com/qxorm_en/manual.html#manual_30), [serialization](https://www.qxorm.com/qxorm_en/manual.html#manual_60), [reflection](https://www.qxorm.com/qxorm_en/manual.html#manual_70), [introspection](https://www.qxorm.com/qxorm_en/manual.html#manual_70), [JSON API](https://www.qxorm.com/qxorm_en/manual.html#manual_97), [HTTP web server](https://www.qxorm.com/qxorm_en/manual.html#manual_96).
QxOrm library supports most common databases like **SQLite**, **MySQL**, **PostgreSQL**, **Oracle**, **MS SQL Server**, **MongoDB**, **MariaDB**.
QxOrm library documentation : https://www.qxorm.com/qxorm_en/manual.html

## About this Docker file
The generated Docker image will execute a container based on a QxOrm library project example.
The QxOrm project example is a simple [HTTP web server](https://www.qxorm.com/qxorm_en/manual.html#manual_96) and uses [QxOrm JSON API](https://www.qxorm.com/qxorm_en/manual.html#manual_97) to send requests to a SQLite database.
More details about the project 'qxBlogRestApi' : https://github.com/QxOrm/QxOrm/tree/master/test/qxBlogRestApi

The built Docker image can be pulled from **Docker Hub** and provides 2 modes :
- [Minimal size, just QxOrm library and all dependencies](https://hub.docker.com/r/qxorm/ubuntu-with-qxorm-test-qxblogrestapi)
- [Full C++ development environment with QxOrm library](https://hub.docker.com/r/qxorm/ubuntu-with-qxorm-dev-qxblogrestapi)

## Build Docker image and run Docker container
### Mode minimal size (by default)
To test [this Docker file](https://github.com/QxOrm/QxOrm/blob/master/docker/test/qxBlogRestApi/Dockerfile) and build/run the Docker container, execute the following commands :
```
cd <path_to_this_docker_file>
docker build -t qxorm/ubuntu-with-qxorm-test-qxblogrestapi .
docker run --rm -itd -p 9642:9642 qxorm/ubuntu-with-qxorm-test-qxblogrestapi
```
By default, Docker build generates a minimal image size, with just the QxOrm test application and all dependencies.

### Mode C++ development environment
To build a Docker image with full C++ development environment, execute the following commands :
```
cd <path_to_this_docker_file>
docker build --target dev -t qxorm/ubuntu-with-qxorm-dev-qxblogrestapi .
docker run --rm -itd -p 9642:9642 -p 9643:9643 -p 2222:22 qxorm/ubuntu-with-qxorm-dev-qxblogrestapi
```
Then access to the remote C++ development environment via [Visual Studio Code](https://code.visualstudio.com/) with the [Dev Containers](https://code.visualstudio.com/docs/devcontainers/tutorial) extension or via [Remote SSH](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-ssh) extension.

#### Connect to the container with VSCode 'Dev Containers' extension
To connect to the C++ development environment with the [Dev Containers](https://code.visualstudio.com/docs/devcontainers/tutorial) extension :
- On the host machine, open [Visual Studio Code](https://code.visualstudio.com/)
- Install the [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension
- Select workspace (open directory) : path to this docker file (which includes a sub-directory named '.devcontainer')
- Visual Studio Code detects automatically the '.devcontainer' sub-directory and provides the action 'Reopen in Container'
- Execute 'Reopen in Container' ==> a new Visual Studio Code instance is created, this new instance is connected to the running Docker container

#### Connect to the container with VSCode 'Remote SSH' extension
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

#### Build and debug project in container
Once connected to the remote C++ development environment (with [Dev Containers](https://code.visualstudio.com/docs/devcontainers/tutorial) extension or [Remote SSH](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-ssh) extension) :
```
Press 'CTRL+SHIFT+B' to build the project in debug mode
Press 'F5' to execute the project in debug mode
```

## Check QxOrm test application web-page
Once Docker container is running, to check if the QxOrm test application is started, on your host machine, open a web browser and go to URL :
```
http://localhost:9642/files/test_http_server.html
```
![qxBlogRestApi web application](https://www.qxorm.com/qxorm_en/resource/qx_blog_rest_api_http_01.png)

**Note :** when the test application is executed in debug mode, the port number is changed to '9643', so the URL becomes :
```
http://localhost:9643/files/test_http_server.html
```

## Authors
QxOrm is developed by Lionel Marty, a software development engineer since 2003.

## License
QxOrm is a C++ library available under a dual license :
- [GNU/GPLv3 license](https://www.qxorm.com/qxorm_en/resource/license.gpl3.txt) : open-source and free (to develop an open-source project or to evaluate QxOrm library) ;
- [Proprietary license](https://www.qxorm.com/qxorm_en/download_details.php) to distribute an application based on QxOrm library without any restrictions of GNU/GPLv3 license.
