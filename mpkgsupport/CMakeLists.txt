cmake_minimum_required(VERSION 3.0)

project(mpkgsupport)

set(BUILD_SHARED_LIBS ON)

if (CMAKE_SIZEOF_VOID_P EQUAL 4)
  set(X86_64 OFF)
else (CMAKE_SIZEOF_VOID_P EQUAL 4)
  set(X86_64 ON)
  add_definitions(-DX86_64)
endif(CMAKE_SIZEOF_VOID_P EQUAL 4)

add_definitions(-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -DLARGEFILE64_SOURCE -DDL_CLEANUP -Wall -W -DNEW_INSTALL_SYSTEM -DUSE_SYSTEM_SED -DDEP_NORMALIZE -DLINUX_DEFINED)

add_definitions(${CXXFLAGS})

#add_definitions(-O0 -DDEBUG -g)

set(SRC_FILES
    "colors.h"
    "constants.h"
    "file_routines.cpp"
    "file_routines.h"
    "fsystem.cpp"
    "fsystem.h"
    "globals.cpp"
    "globals.h"
    "mpkgsupport.h"
    "string_operations.cpp"
    "string_operations.h"
    "test.cpp"
)

add_library(mpkgsupport SHARED ${SRC_FILES} file_routines string_operations globals fsystem)

target_link_libraries(mpkgsupport pthread)

add_executable(test test)

target_link_libraries(test mpkgsupport)

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

install(FILES ${files} DESTINATION include/mpkgsupport)

install(TARGETS mpkgsupport LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)

