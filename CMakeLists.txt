cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        "${CMAKE_SOURCE_DIR}/cmake"
        "${CMAKE_SOURCE_DIR}/cmake/modules"
)

project(pongtable)

set(HDRS
    ./src/ButtonFrame.h
    ./src/CreateFrame.h
    ./src/Database.h
    ./src/Display.h
    ./src/ErrorFrame.h
    ./src/Frame.h
    ./src/IdleFrame.h
    ./src/ListFrame.h
    ./src/LoginFrame.h
    ./src/PasswordFrame.h
    ./src/Player.h
    ./src/TextFrame.h
    ./src/ViewFrame.h
)

set(SRCS
    ./src/main.cpp
    ./src/ButtonFrame.cpp
    ./src/CreateFrame.cpp
    ./src/Database.cpp
    ./src/Display.cpp
    ./src/ErrorFrame.cpp
    ./src/Frame.cpp
    ./src/IdleFrame.cpp
    ./src/ListFrame.cpp
    ./src/LoginFrame.cpp
    ./src/PasswordFrame.cpp
    ./src/Player.cpp
    ./src/TextFrame.cpp
    ./src/ViewFrame.cpp
)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.42.0 COMPONENTS thread system REQUIRED)
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

