qmake %QXORM_QMAKE_PARAMS% "./qxServiceClient.pro"
nmake release
qmake %QXORM_QMAKE_PARAMS% "./qxServiceServer.pro"
nmake release
