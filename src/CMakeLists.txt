set(TARGET qt_directory_hook)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(QT_DEPENDENCIES Core Widgets)
find_package(Qt5 REQUIRED ${QT_DEPENDENCIES})

if(${MSVC_VERSION} EQUAL 1600)
add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
endif()

file(GLOB SOURCE *.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../include/${TARGET}/*.h)
set(QT_LIBRARIES Qt5::Widgets Qt5::Core)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_executable(${TARGET} WIN32 ${SOURCE})
target_link_libraries(${TARGET} ${QT_LIBRARIES})
