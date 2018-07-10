cmake_minimum_required(VERSION 3.1)

project(qxClientServer LANGUAGES CXX)

include(../../QxOrm.cmake)

if(_QX_ENABLE_QT_NETWORK)

add_subdirectory(qxService/qxServiceClient)
add_subdirectory(qxService/qxServiceServer)
add_subdirectory(qxClient)
add_subdirectory(qxServer)

else() # _QX_ENABLE_QT_NETWORK

message(STATUS "qxClientServer project not loaded because _QX_ENABLE_QT_NETWORK option not enabled (QxOrm QxService module is disabled)")

endif() # _QX_ENABLE_QT_NETWORK
