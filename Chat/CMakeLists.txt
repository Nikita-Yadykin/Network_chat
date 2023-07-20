cmake_minimum_required(VERSION 3.22)
project(Chat)
add_executable(Chat main.cpp sha1.h sha1.cpp User.h User.cpp Message.h Message.cpp ConsoleChat.h ConsoleChat.cpp NetWorkStream.h NetWorkStream.cpp)