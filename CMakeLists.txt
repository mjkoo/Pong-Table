cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(pongtable)

set(HDRS
    ./ButtonFrame.h
    ./Database.h
    ./Display.h
    ./ErrorFrame.h
    ./Frame.h
    ./IdleFrame.h
    ./ListFrame.h
    ./LoginFrame.h
    ./PasswordFrame.h
    ./Player.h
    ./TextFrame.h
    ./ViewFrame.h
)

set(SRCS
    ./main.cpp
    ./ButtonFrame.cpp
    ./Database.cpp
    ./Display.cpp
    ./ErrorFrame.cpp
    ./Frame.cpp
    ./IdleFrame.cpp
    ./ListFrame.cpp
    ./LoginFrame.cpp
    ./PasswordFrame.cpp
    ./Player.cpp
    ./TextFrame.cpp
    ./ViewFrame.cpp
)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.42.0 COMPONENTS thread REQUIRED)
find_package(MPDClient REQUIRED)
find_package(SQLite REQUIRED)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${MPDCLIENT_INCLUDE_DIRS}
    ${SQLITE_INCLUDE_DIRS}
)

add_executable(pongtable ${HDRS} ${SRCS})

target_link_libraries(pongtable
    ${Boost_LIBRARIES}
    ${MPDCLIENT_LIBRARIES}
    ${SQLITE_LIBRARIES}
)

