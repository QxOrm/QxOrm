# QxOrm Demo Stack (C++ / Qt / ORM / HTTP Web Server / REST API / SQLite)
This demo environment runs a complete C++ backend stack using:
- QxOrm (C++ ORM based on Qt)
- REST API server (C++ backend)
- SQLite database
- Nginx reverse proxy
- Optional frontend UI

## Goal
   Run a complete C++ backend stack in one command

## Requirements
- Docker
- Docker Compose

## Quick start
```
curl -L -O https://raw.githubusercontent.com/QxOrm/QxOrm/master/docker/demo/compose_qxorm_with_sqlite/compose_demo_qxorm_with_sqlite.yaml
docker compose -f compose_demo_qxorm_with_sqlite.yaml up -d
```

## URL web access
```
http://localhost:8080
```

## API test

### ping
```
curl -X POST http://localhost:8080/ping -H "Content-Type: application/json" -d "{ \"request_id\":\"random_request_id\", \"action\":\"ping\" }"
```

### list of entities
```
curl -X POST http://localhost:8080/qx -H "Content-Type: application/json" -d "{ \"request_id\":\"random_request_id\", \"action\":\"get_meta_data\", \"entity\":\"*\" }"
```

### database access
```
curl -X POST http://localhost:8080/qx -H "Content-Type: application/json" -d "{ \"request_id\":\"random_request_id\", \"action\":\"fetch_all\", \"entity\":\"blog\" }"
```

## Images are pulled automatically from Docker Hub
https://hub.docker.com/u/qxorm

## Notes
This is a demo setup:
- No build required
- No local dependencies
- Designed for quick evaluation

## Advanced (full development environment with Docker)
A complete C++ development setup is also available, including:
- Debug-ready backend environment
- VS Code Remote / Dev Containers support

See documentation for details:
https://github.com/QxOrm/QxOrm/tree/master/docker/dev/compose_qxorm_with_sqlite

![compose_qxorm_with_sqlite](https://www.qxorm.com/qxorm_en/resource/docker_compose_schema.png)
