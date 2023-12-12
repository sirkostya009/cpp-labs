cmake_minimum_required(VERSION 3.26)
project(lab1)
project(lab2)
project(lab3)
project(lab4)
project(lab5)

set(CMAKE_CXX_STANDARD 23)

add_executable(lab1 lab1/main.cpp)
add_executable(lab2 lab2/main.cpp)
add_executable(lab3 lab3/main.cpp)
add_executable(lab4 lab4/main.cpp
                    lab4/App.cpp
                    lab4/App.h
                    lab4/Event.h
                    lab4/EventDispatch.cpp
                    lab4/EventDispatch.h
                    lab4/handlers.cpp
                    lab4/handlers.h
                    lab4/List.h
                    lab4/Worker.cpp
                    lab4/Worker.h)
add_executable(lab5 lab5/main.cpp)
