# QxOrm library - Official repository
[QxOrm library](https://www.qxorm.com/) is an **Object Relational Mapping (ORM)** and **Object Document Mapper (ODM)** database library for C++ Qt developers. Main features are :
- [Persistence](https://www.qxorm.com/qxorm_en/manual.html#manual_30) : support most common databases like SQLite, MySQL, PostgreSQL, Oracle, MS SQL Server, [MongoDB](https://www.qxorm.com/qxorm_en/manual.html#manual_95) (with 1-1, 1-n, n-1 and n-n relationships) ;
- [Serialization](https://www.qxorm.com/qxorm_en/manual.html#manual_60) : JSON, binary and XML format ;
- [Reflection](https://www.qxorm.com/qxorm_en/manual.html#manual_70) (or [Introspection](https://www.qxorm.com/qxorm_en/manual.html#manual_70)) : access dynamically to classes definitions, retrieve properties and call classes methods ;
- [HTTP web server](https://www.qxorm.com/qxorm_en/manual.html#manual_96) : standalone multi-threaded HTTP 1.1 web server (support SSL/TLS, persistent connections, cookies, sessions, chunked responses, URL dispatcher/routing) ;
- [JSON API](https://www.qxorm.com/qxorm_en/manual.html#manual_97) : interoperability with other technology than C++/Qt (REST web services, QML applications, scripting language).

## Documentation
QxOrm website provides a [user manual](https://www.qxorm.com/qxorm_en/manual.html).

The goal of this documentation is to provide a user guide to learn how to work with QxOrm library features. This manual is intended for developers and software architects who are looking for a solution to manage a persistent data layer in C++/Qt. Technical skills in C++ and databases are required to understand this document.

**Note :** all features described in this manual/user guide can be defined quickly and easily with **QxEntityEditor application** (the graphic editor for QxOrm library, data model designer and source code generator). Another [documentation dedicated to QxEntityEditor application](https://www.qxorm.com/qxorm_en/manual_qxee.html) is available on QxOrm website.

## QxEntityEditor application
[QxEntityEditor](https://www.qxorm.com/qxorm_en/manual_qxee.html) is a graphic editor for QxOrm library : **QxEntityEditor provides a graphic way to manage the data model**.
QxEntityEditor is multi-platform (available for Windows, Linux and Mac OS X) and generates native code for all environments : desktop (Windows, Linux, Mac OS X), embedded and mobile (Android, iOS, Windows Phone, Raspberry Pi, etc.).
[A user manual (documentation) for QxEntityEditor application](https://www.qxorm.com/qxorm_en/manual_qxee.html) is available on QxOrm website.

QxEntityEditor is based on plugins and provides many ways to import/export your data model :
- [generate C++ persistent classes](https://www.qxorm.com/qxorm_en/manual_qxee.html#cpp_export_settings) automatically (registered in QxOrm context) ;
- [generate DDL SQL script](https://www.qxorm.com/qxorm_en/manual_qxee.html#ddl_export_settings) automatically (database schema) for SQLite, MySQL, PostgreSQL, Oracle and MS SQL Server ;
- manage schema evolution for each project version (ALTER TABLE, ADD COLUMN, DROP INDEX, etc.) ;
- transfer your data model over network and [create quickly client/server applications](https://www.qxorm.com/qxorm_en/manual_qxee.html#cpp_services_export_settings), using [QxService module](https://www.qxorm.com/doxygen/html/group___qx_service.html) ;
- [import existing database structure](https://www.qxorm.com/qxorm_en/manual_qxee.html#wnd_mysql_import) (using ODBC connection or native drivers) for SQLite, MySQL, PostgreSQL, Oracle and MS SQL Server databases ;
- because each project is different, QxEntityEditor provides several ways to customize generated files (especially a [javascript engine and an integrated debugger](https://www.qxorm.com/qxorm_en/manual_qxee.html#js_engine)).

![QxEntityEditor application](https://www.qxorm.com/qxentityeditor/resource/qxee_sample_small.png)

## Dependencies
By default, QxOrm library depends only on [QtCore](https://doc.qt.io/qt-5/qtcore-index.html) and [QtSql](https://doc.qt.io/qt-5/qtsql-index.html) libraries from [Qt framework](https://www.qt.io/).
If you enable [QxOrm HTTP web server](https://www.qxorm.com/qxorm_en/manual.html#manual_96) feature, then QxOrm library will depend also on [QtNetwork](https://doc.qt.io/qt-5/qtnetwork-index.html) library.
Some features require [boost](https://www.boost.org/) dependency (disabled by default).

## Authors
QxOrm is developed by Lionel Marty, a software development engineer since 2003.

## License
QxOrm is a C++ library available under a dual license :
- [GNU/GPLv3 license](https://www.qxorm.com/qxorm_en/resource/license.gpl3.txt) : open-source and free (to develop an open-source project or to evaluate QxOrm library) ;
- [Proprietary license](https://www.qxorm.com/qxorm_en/download_details.php) to distribute an application based on QxOrm library without any restrictions of GNU/GPLv3 license.
