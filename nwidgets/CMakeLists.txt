cmake_minimum_required(VERSION 3.0)

PROJECT(mpkg-nwidgets)

add_definitions(-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -DLARGEFILE64_SOURCE -DDL_CLEANUP -Wall -W -DNEW_INSTALL_SYSTEM -DUSE_SYSTEM_SED -DDEP_NORMALIZE -DLINUX_DEFINED)
add_definitions(${CXXFLAGS})
add_library(nwidgets SHARED ncurses_if.cpp)
target_link_libraries(nwidgets ncursesw mpkgsupport)

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${files} DESTINATION include/nwidgets)

install(TARGETS nwidgets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)
