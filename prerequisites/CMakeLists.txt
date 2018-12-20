cmake_minimum_required(VERSION 2.8)

# c-ipfs section
# liblmdb
project(lmdb)
set(SRC "lmbd/libraries/liblmdb/mdb.c"
    "lmbd/libraries/liblmdb/midl.c"
)
add_library(lmdb SHARED ${SRC})
if(WIN32 AND ${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    target_link_libraries(${PROJECT_NAME} ntdll)
endif()
if(UNIX AND ${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    target_link_libraries(${PROJECT_NAME})
endif()
add_custom_command(TARGET ${PROJECT_NAME} 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> "../../bin")

# protobuf_reader
project(protobuf_reader)
set(SRC "c-protobuf/protobuf.c"
    "c-protobuf/varint.c"
    "c-protobuf/main.c"
)

set(GCC_COVERAGE_COMPILE_FLAGS "-O0 -g3 -Wall -std=c99")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
add_executable(${PROJECT_NAME} ${SRC})
add_custom_command(TARGET ${PROJECT_NAME} 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> "../../bin")

# LibQtWebApp
project(QtWebApp)

if(WIN32 AND ${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    # Hardcode a location for a QT toolkit compiled for Win64.  By overriding QT_QMAKE, all the rest is found
    # Choose any version of QT found in the 64-bit tools area
    file(GLOB QTROOTS C:/msys64)     # */
    find_program(QT_QMAKE_EXECUTABLE NAMES qmake qmake4 qmake-qt4 qmake-mac PATHS ${QTROOTS})
    find_program(MAKE_EXECUTABLE NAMES mingw32-make.exe PATHS ${QTROOTS})
    set(MKSPEC win32-g++)
    set(FILENAME ${PROJECT_NAME}d1.dll)
endif()
if(UNIX AND ${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    # Hardcode a location for a QT toolkit compiled for Win64.  By overriding QT_QMAKE, all the rest is found
    # Choose any version of QT found in the 64-bit tools area
    set(QT_QMAKE_EXECUTABLE qmake)
    set(MAKE_EXECUTABLE make)
    set(MKSPEC linux-g++-64)
    set(FILENAME lib${PROJECT_NAME}d.so)
endif()
find_package(Qt5)

set(LIB_FILE ${CMAKE_CURRENT_BINARY_DIR}/QtWebApp/${FILENAME})
set(LIB_HEADER_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/QtWebApp/QtWebApp)
# how to build the result of the library
set(EXTRA_QMAKE_FLAGS -spec ${MKSPEC} "CONFIG+=debug" "QMAKE_CXXFLAGS+=-fpermissive -Wno-attributes -Wno-unused-parameter -Wno-implicit-fallthrough" "DEFINES+=QT_BUILD_WEBSOCKETS_LIB QT_NO_DEBUG_OUTPUT QT_NO_WARNING_OUTPUT" DESTDIR=${CMAKE_CURRENT_BINARY_DIR}/QtWebApp OBJECTS_DIR=.objs MOC_DIR=.moc RCC_DIR=.rcc UI_DIR=.ui)
add_custom_command(OUTPUT  ${LIB_FILE} 
    COMMAND ${QT_QMAKE_EXECUTABLE}
    ARGS ${CMAKE_CURRENT_SOURCE_DIR}/QtWebApp/QtWebApp/QtWebApp.pro ${EXTRA_QMAKE_FLAGS}
    COMMAND cd
    ARGS ${CMAKE_CURRENT_SOURCE_DIR}/build
    COMMAND ${MAKE_EXECUTABLE}
    ARGS -j4
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

#string(TOLOWER ${FILENAME} LOW_PROJECT_NAME)
# create a target out of the library compilation result
add_custom_target(${PROJECT_NAME}_target ALL
    COMMAND cp -f ${CMAKE_CURRENT_BINARY_DIR}/QtWebApp/${FILENAME}* ${CMAKE_CURRENT_BINARY_DIR}/../../bin
    DEPENDS ${LIB_FILE})

# create an library target out of the library compilation result
add_library(${PROJECT_NAME} SHARED IMPORTED GLOBAL)
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_target)

# specify where the library is and where to find the headers
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    IMPORTED_LOCATION ${LIB_FILE}
    INTERFACE_INCLUDE_DIRECTORIES ${LIB_HEADER_FOLDER})

