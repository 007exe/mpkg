#
# MOPSLinux packaging system
#
#
cmake_minimum_required(VERSION 2.6)
    if(COMMAND cmake_policy)
      cmake_policy(SET CMP0003 NEW)
      cmake_policy(SET CMP0005 NEW)
    endif(COMMAND cmake_policy)
# Project name
PROJECT(GUISETUP)

# Enabling building of shared libs
SET(BUILD_SHARED_LIBS ON)
# If you want to build a standalone server app, set SERVERAPP to ON
SET(SERVERAPP OFF)
SET(MAXSTATIC OFF)
# Check 64 bit
if (CMAKE_SIZEOF_VOID_P EQUAL 4)
	SET(X86_64 OFF)
else (CMAKE_SIZEOF_VOID_P EQUAL 4)
	SET(X86_64 ON)
	ADD_DEFINITIONS(-DX86_64)
endif(CMAKE_SIZEOF_VOID_P EQUAL 4)

ADD_DEFINITIONS(-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -DLARGEFILE64_SOURCE -DDL_CLEANUP -I. -I/usr/include/libxml2 -Wall -W -DNEW_INSTALL_SYSTEM -DUSE_SYSTEM_SED -DDEP_NORMALIZE -DLINUX_DEFINED)
ADD_DEFINITIONS(-DINSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}")

ADD_DEFINITIONS(${CXXFLAGS})
# Main part
# c++ sources
SET(guisetup_SRC
	main.cpp
	mainwindow.cpp
	thread.cpp
)
# headers for MOC
SET(guisetup_MOC_HDR
	mainwindow.h
	thread.h
)
SET(guisetup_QRC
	mainwindow.qrc
)
# UI
SET(guisetup_UI
	mainwindow.ui
)
##########FIND_PACKAGE(Qt5 REQUIRED)
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE (Qt5Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
##########INCLUDE( ${QT_USE_FILE} )
### из include_directories нужно выкенуть не нужные модули
include_directories(${Qt5Widgets_INCLUDES} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Widgets_LIBRARIES} ${Qt5Declarative_INCLUDE_DIRS} ${Qt5Declarative_LIBRARIES})
add_definitions(${Qt5Widgets_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_AUTOUIC ON)
QT5_WRAP_UI(guisetup_UI_HDR ${guisetup_UI})
QT5_WRAP_CPP(guisetup_MOC_SRC ${guisetup_MOC_HDR})
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})
ADD_EXECUTABLE(guisetup_exec ${guisetup_SRC} ${guisetup_MOC_SRC} ${guisetup_UI_HDR} ${guisetup_RCC_SRCS} )
TARGET_LINK_LIBRARIES(guisetup_exec ${QT_LIBRARIES} mpkg mpkg-parted mpkgsupport agiliasetup Qt5::Gui Qt5::Widgets)

FILE(GLOB icons "${CMAKE_CURRENT_SOURCE_DIR}/icons/*.png")
FILE(GLOB l10n "${CMAKE_CURRENT_SOURCE_DIR}/*.qm")
# Installation
 
INSTALL(TARGETS guisetup_exec
		RUNTIME DESTINATION bin
)
INSTALL(FILES ${icons} DESTINATION share/setup/icons)
INSTALL(FILES ${l10n} DESTINATION share/setup/l10n)

