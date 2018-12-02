#################################################################################################
## File created by QxEntityEditor 1.2.3 (2018/11/30 09:04) : please, do NOT modify this file ! ##
#################################################################################################

!contains(DEFINES, _QX_NO_PRECOMPILED_HEADER) {
PRECOMPILED_HEADER += $$PWD/include/KPI_precompiled_header.gen.h
} # !contains(DEFINES, _QX_NO_PRECOMPILED_HEADER)

HEADERS += $$PWD/include/KPI_precompiled_header.gen.h
HEADERS += $$PWD/include/KPI_export.gen.h

HEADERS += $$PWD/include/kpi_KPI.gen.h
HEADERS += $$PWD/include/kpi_MetaData.gen.h
HEADERS += $$PWD/include/kpi_MetaDataKey.gen.h
HEADERS += $$PWD/include/kpi_Type.gen.h

HEADERS += $$PWD/custom/include/kpi_KPI.h
HEADERS += $$PWD/custom/include/kpi_MetaData.h
HEADERS += $$PWD/custom/include/kpi_MetaDataKey.h
HEADERS += $$PWD/custom/include/kpi_Type.h

contains(DEFINES, _QX_UNITY_BUILD) {

SOURCES += $$PWD/src/KPI_all.gen.cpp

} else {

SOURCES += $$PWD/src/kpi_KPI.gen.cpp
SOURCES += $$PWD/src/kpi_MetaData.gen.cpp
SOURCES += $$PWD/src/kpi_MetaDataKey.gen.cpp
SOURCES += $$PWD/src/kpi_Type.gen.cpp

SOURCES += $$PWD/custom/src/kpi_KPI.cpp
SOURCES += $$PWD/custom/src/kpi_MetaData.cpp
SOURCES += $$PWD/custom/src/kpi_MetaDataKey.cpp
SOURCES += $$PWD/custom/src/kpi_Type.cpp

} # contains(DEFINES, _QX_UNITY_BUILD)

include($$PWD/custom/KPI.pri)
