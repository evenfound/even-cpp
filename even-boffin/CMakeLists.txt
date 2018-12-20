cmake_minimum_required(VERSION 2.8)

# even-boffin
project(even-boffin)

if(WIN32 AND ${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    # Hardcode a location for a QT toolkit compiled for Win64.  By overriding QT_QMAKE, all the rest is found
    # Choose any version of QT found in the 64-bit tools area
    file(GLOB QTROOTS C:/msys64)     # */
    find_program(QT_QMAKE_EXECUTABLE NAMES qmake qmake4 qmake-qt4 qmake-mac PATHS ${QTROOTS})
    find_program(MAKE_EXECUTABLE NAMES mingw32-make.exe PATHS ${QTROOTS})
    set(MKSPEC win32-g++)
    set(FILENAME ${PROJECT_NAME}.exe)
endif()
if(UNIX AND ${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    # Hardcode a location for a QT toolkit compiled for Win64.  By overriding QT_QMAKE, all the rest is found
    # Choose any version of QT found in the 64-bit tools area
    set(QT_QMAKE_EXECUTABLE qmake)
    set(MAKE_EXECUTABLE make)
    set(MKSPEC linux-g++-64)
    set(FILENAME ${PROJECT_NAME})
endif()
find_package(Qt5)

set(EXEC_FILE ${CMAKE_CURRENT_BINARY_DIR}/QtEvenBoffin/${FILENAME})
#SET(LIB_HEADER_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/QtWebApp/QtWebApp)
# how to build the result of the library
set(EXTRA_QMAKE_FLAGS -spec ${MKSPEC} "CONFIG+=debug" "QMAKE_CXXFLAGS=-Wno-switch -Wno-attributes -Wno-ignored-qualifiers -fpermissive -std=c++14" DESTDIR=${CMAKE_CURRENT_BINARY_DIR}/QtEvenBoffin OBJECTS_DIR=QtEvenBoffin/.objs MOC_DIR=QtEvenBoffin/.moc RCC_DIR=QtEvenBoffin/.rcc UI_DIR=QtEvenBoffin/.ui)
add_custom_command(OUTPUT  ${EXEC_FILE} 
    COMMAND ${QT_QMAKE_EXECUTABLE}
    ARGS ${CMAKE_CURRENT_SOURCE_DIR}/even-boffin.pro ${EXTRA_QMAKE_FLAGS}
    COMMAND cd
    ARGS ${CMAKE_CURRENT_BINARY_DIR}/QtEvenBoffin
    COMMAND ${MAKE_EXECUTABLE}
    ARGS -j4
    WORKING_DIRECTORY  ${CMAKE_CURRENT_BINARY_DIR}
)

# create a target out of the library compilation result
add_custom_target(${PROJECT_NAME}_target ALL
    COMMAND cp -f ${CMAKE_CURRENT_BINARY_DIR}/QtEvenBoffin/${FILENAME} ${CMAKE_CURRENT_BINARY_DIR}/../../bin
    DEPENDS ${EXEC_FILE})

# create an library target out of the library compilation result
add_executable(${PROJECT_NAME} IMPORTED GLOBAL)
#target_link_libraries(${PROJECT_NAME} INTERFACE qtwebapp)
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_target)

# specify where the library is and where to find the headers
#set_target_properties(${PROJECT_NAME}
#    PROPERTIES
#    IMPORTED_LOCATION ${EXEC_FILE}
#    INTERFACE_INCLUDE_DIRECTORIES ${LIB_HEADER_FOLDER})


