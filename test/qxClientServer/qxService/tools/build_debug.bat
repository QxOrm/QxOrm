qmake %QXORM_QMAKE_PARAMS% "./qxServiceClient.pro"
nmake debug
qmake %QXORM_QMAKE_PARAMS% "./qxServiceServer.pro"
nmake debug
