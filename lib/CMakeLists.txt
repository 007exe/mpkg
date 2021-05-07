cmake_minimum_required(VERSION 3.0)

project(mpkg-core)

add_definitions(-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -DLARGEFILE64_SOURCE -DDL_CLEANUP -I. -I/usr/include/libxml2 -Wall -W -DNEW_INSTALL_SYSTEM -DUSE_SYSTEM_SED -DDEP_NORMALIZE -DLINUX_DEFINED)

# проверка для какой архитектуры собирается библиотека
if (CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(X86_64 OFF)
else (CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(X86_64 ON)
    add_definitions(-DX86_64)
endif(CMAKE_SIZEOF_VOID_P EQUAL 4)

set(SRC_FILES
    "bus.cpp"
    "bus.h"
    "checklibdeps.cpp"
    "checklibdeps.h"
    "conditions.cpp"
    "conditions.h"
    "config.cpp"
    "config.h"
    "console-help.cpp"
    "console-help.h"
    "converter.cpp"
    "converter.h"
    "core.cpp"
    "core.h"
    "dataunits.cpp"
    "dataunits.h"
    "dbstruct.cpp"
    "dbstruct.h"
    "debug.cpp"
    "debug.h"
    "deltas.cpp"
    "deltas.h"
    "dependencies.cpp"
    "dependencies.h"
    "depreactor.cpp"
    "depreactor.h"
    "DownloadManager.cpp"
    "DownloadManager.h"
    "errorcodes.cpp"
    "errorcodes.h"
    "errorhandler.cpp"
    "errorhandler.h"
    "HttpDownload.cpp"
    "HttpDownload.h"
    "libmpkg.cpp"
    "libmpkg.h"
    "local_package.cpp"
    "local_package.h"
    "menu.cpp"
    "menu.h"
    "metaframe.cpp"
    "metaframe.h"
    "mpkg.cpp"
    "mpkg.h"
    "mpkgsys.cpp"
    "mpkgsys.h"
    "package.cpp"
    "package.h"
    "PackageConfig.cpp"
    "PackageConfig.h"
    "repository.cpp"
    "repository.h"
    "spkgsupport.cpp"
    "spkgsupport.h"
    "sql_pool.cpp"
    "sql_pool.h"
    "syscommands.cpp"
    "syscommands.h"
    "terminal.cpp"
    "terminal.h"
    "tests.cpp"
    "tests.h"
    "transactions.cpp"
    "transactions.h"
    "xml2pkglist.cpp"
    "xml2pkglist.h"
    "xmlParser.cpp"
    "xmlParser.h"
)

add_library(mpkg SHARED ${SRC_FILES})

target_link_libraries(mpkg xml2 curl sqlite3 nwidgets)

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

install(FILES ${files} DESTINATION include/mpkg)

install(TARGETS mpkg LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)
