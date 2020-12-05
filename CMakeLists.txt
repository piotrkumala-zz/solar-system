cmake_minimum_required(VERSION 3.17)
project(grafika3D)

set(CMAKE_CXX_STANDARD 14)
set(OpenGlLinkers -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED) # finding sfml directory
file(COPY ${CMAKE_SOURCE_DIR}/Textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


add_executable(grafika3D main.cpp pch.h pch.cpp materials.h config.h)
target_link_libraries(grafika3D ${OpenGlLinkers}) # linking opengl libraries to the project
target_link_libraries(grafika3D sfml-graphics sfml-audio) # linking sfml libraries to the project