cmake_minimum_required(VERSION 3.1)

project(QxOrmAllTests LANGUAGES CXX)

add_subdirectory(../ ./QxOrm)

add_subdirectory(qxBlog)
add_subdirectory(qxBlogCompositeKey)
add_subdirectory(qxBlogCpp11)
add_subdirectory(qxBlogModelView)
add_subdirectory(qxDllSample)
add_subdirectory(qxClientServer)
