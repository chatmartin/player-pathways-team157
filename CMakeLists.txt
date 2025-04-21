cmake_minimum_required(VERSION 3.29)
project(player_pathways_team157)

set(CMAKE_CXX_STANDARD 14)

add_executable(player_pathways_team157
    src/main.cpp
        src/Player.h
        src/Player.cpp
        src/SoccerPlayer.h
        src/SoccerPlayer.cpp
        src/BasketballPlayer.h
        src/BasketballPlayer.cpp
        src/Graph.h
        src/Graph.cpp)

include_directories("src/Crow-1.2.0-Darwin/include")

include_directories("src/asio-asio-1-18-2/asio/include")

include_directories("src")

target_link_libraries(player_pathways_team157 PRIVATE ws2_32 mswsock)