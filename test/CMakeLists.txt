cmake_minimum_required(VERSION 3.15)

project(QxOrmAllTests LANGUAGES CXX)

add_subdirectory(../ ./QxOrm)

option(_QX_TEST_QXBLOGRESTAPI "If you enable _QX_TEST_QXBLOGRESTAPI option, then only 'qxBlogRestApi' example project will be built (used to create Docker images)" OFF)

if(_QX_TEST_QXBLOGRESTAPI)

add_subdirectory(qxBlogRestApi)

else() # _QX_TEST_QXBLOGRESTAPI

add_subdirectory(qxBlog)
add_subdirectory(qxBlogCompositeKey)
add_subdirectory(qxBlogCpp11)
add_subdirectory(qxBlogModelView)
add_subdirectory(qxDllSample)
add_subdirectory(qxClientServer)
add_subdirectory(qxBlogMongoDB)
add_subdirectory(qxBlogPImpl)
add_subdirectory(qxBlogRestApi)

endif() # _QX_TEST_QXBLOGRESTAPI
