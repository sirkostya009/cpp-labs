cmake_minimum_required(VERSION 3.26)
project(operating_systems_labs)

set(CMAKE_CXX_STANDARD 23)

# Закоментуйте рядок, щоб запустити іншу лабораторну роботу
add_executable(operating_systems_labs
        lab4/main.cpp
        lab4/App.h
        lab4/App.cpp
        lab4/EventDispatch.cpp
        lab4/EventDispatch.h
        lab4/handlers.cpp
        lab4/handlers.h
        lab4/Worker.cpp
        lab4/Worker.h
        lab4/Event.h
        lab4/List.h)

# Розкоментуйте рядок, щоб запустити іншу лабораторну роботу
# add_executable(operating_systems_labs lab1.cpp)
# add_executable(operating_systems_labs lab2.cpp)
# add_executable(operating_systems_labs lab3.cpp)
# add_executable(operating_systems_labs lab5.cpp)
