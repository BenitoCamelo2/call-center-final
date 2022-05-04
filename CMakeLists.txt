cmake_minimum_required(VERSION 3.21)
project(call-center)

set(CMAKE_CXX_STANDARD 14)

add_executable(call-center main.cpp
        ./src/agent.cpp
        ./src/agentlist.cpp
        ./src/agentmenu.cpp
        ./src/agentnode.cpp
        ./src/agentnodeexception.cpp
        ./src/client.cpp
        ./src/clientlist.cpp
        ./src/clientmenu.cpp
        ./src/clientnode.cpp
        ./src/date.cpp
        ./src/mainmenu.cpp
        ./src/name.cpp
        src/times.cpp
        ./src/util.cpp
        ./include/agent.h
        ./include/agentlist.h
        ./include/agentmenu.h
        ./include/agentnode.h
        ./include/agentnodeexception.h
        ./include/client.h
        ./include/clientlist.h
        ./include/clientmenu.h
        ./include/clientnode.h
        ./include/date.h
        ./include/listexception.h
        ./include/mainmenu.h
        ./include/name.h
        include/times.h
        ./include/util.h)

target_include_directories(call-center PRIVATE ./include)
