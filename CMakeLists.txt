cmake_minimum_required(VERSION 3.0.0)
project(PROJECT VERSION 0.1.0)

#Год плюсов
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -lGL -lGLU -lglut -lgtest")
#set(CMAKE_CXX_STANDARD 17) 

#Ищем все исполняемые файлы
file(GLOB _SOURSCES "*.cpp")
file(GLOB _HEADERS "*.h")

find_package(OpenGL)
find_package(GLUT)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

link_libraries(stdc++fs)

#Добавляем в сборку исполняемые файлы
add_executable(${PROJECT_NAME} ${_SOURSCES})

set(Directories Scene Geometry)

#Добавляем поддиректорию для поиска подфайла Cmake
foreach(directory IN LISTS Directories)
	add_subdirectory(${directory})
endforeach()

#Линкуем
target_link_libraries(${PROJECT_NAME}
                      ${OPENGL_gl_LIBRARY}
                      ${GLUT_LIBRARIES}
                       Scene Geometry)