cmake_minimum_required(VERSION 3.5)

project(DSSS_CMake VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Network)
find_package(Qt5 REQUIRED COMPONENTS Network)

set(PROJECT_SOURCES
        main.cpp
        dsss_window.cpp
        dsss_window.h
        dsss_window.ui

        TCP_Server/tcp_server.cpp
        TCP_Server/tcp_server.h

        DSS_Protocol/packets/BasePacket.h

        DSS_Protocol/packets/BootstrapPacket.cpp
        DSS_Protocol/packets/BootstrapPacket.h

        DSS_Protocol/packets/AliveNodeResponsePacket.cpp
        DSS_Protocol/packets/AliveNodeResponsePacket.h

        DSS_Protocol/packets/AliveNodeRequestPacket.cpp
        DSS_Protocol/packets/AliveNodeRequestPacket.h

        DSS_Protocol/utils/ConvertPacket.cpp
        DSS_Protocol/utils/ConvertPacket.h

        DSS_Protocol/DSS_Protocol.cpp
        DSS_Protocol/DSS_Protocol.h
)

add_subdirectory(DataProcessingManager/)

add_executable(DSSS_CMake
    ${PROJECT_SOURCES}
)

target_link_libraries(DSSS_CMake PRIVATE Qt5::Widgets)
target_link_libraries(DSSS_CMake PRIVATE Qt5::Network)

