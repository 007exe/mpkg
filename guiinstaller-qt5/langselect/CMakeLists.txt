# AgiliaLinux GUI installer: lang setup

cmake_minimum_required(VERSION 2.6)
    if(COMMAND cmake_policy)
      cmake_policy(SET CMP0003 NEW)
      cmake_policy(SET CMP0005 NEW)
    endif(COMMAND cmake_policy)
# Project name
PROJECT(GUISETUP)

# Enabling building of shared libs
SET(BUILD_SHARED_LIBS ON)
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
)
# headers for MOC
SET(guisetup_MOC_HDR
	mainwindow.h
)

# UI
SET(guisetup_UI
	mainwindow.ui
)
#SET(guisetup_QRC
#)
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE (Qt5Widgets)
set(CMAKE_AUTOMOC ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
### из include_directories нужно выкенуть не нужные модули
include_directories(${Qt5Widgets_INCLUDES} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Widgets_LIBRARIES} ${Qt5Declarative_INCLUDE_DIRS} ${Qt5Declarative_LIBRARIES})
add_definitions(${Qt5Widgets_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_AUTOUIC ON)
QT5_WRAP_UI(guisetup_UI_HDR ${guisetup_UI})
QT5_WRAP_CPP(guisetup_MOC_SRC ${guisetup_MOC_HDR})
#QT4_ADD_RESOURCES(guisetup_RCC_SRCS ${guisetup_QRC})
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})
#ADD_EXECUTABLE(guisetup ${guisetup_SRC} ${guisetup_MOC_SRC} ${guisetup_UI_HDR} ${guisetup_RCC_SRCS})
ADD_EXECUTABLE(guisetup_lang ${guisetup_SRC} ${guisetup_MOC_SRC} ${guisetup_UI_HDR} )
####
TARGET_LINK_LIBRARIES(guisetup_lang ${QT_LIBRARIES} mpkgsupport agiliasetup Qt5::Gui Qt5::Widgets)


# Installation
 
INSTALL(TARGETS guisetup_lang
		RUNTIME DESTINATION bin
)

