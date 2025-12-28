cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 11)
project(initproj LANGUAGES CXX)

add_executable(template)
target_sources(template PRIVATE src/main.cpp)

if(${EMSCRIPTEN})

  file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/Image5.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)

  set(CMAKE_VERBOSE_MAKEFILE ON)
  target_sources(template PRIVATE src/em_main.cpp)
  target_compile_options(template PRIVATE --use-port=sdl2 --use-port=sdl2_image:formats=bmp,png,xpm,jpg)
  target_link_options(template PRIVATE -sALLOW_MEMORY_GROWTH=1 --use-port=sdl2 --use-port=sdl2_image:formats=bmp,png,xpm,jpg --preload-file assets)
  target_link_options(template PRIVATE --shell-file ../shell.html)
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
else()
  find_package(SDL2)
  find_package(SDL2_image)
  target_sources(template PRIVATE src/desktop_main.cpp)
  target_include_directories(template PRIVATE ${SDL2_INCLUDE_DIRS})
  target_link_libraries(template PRIVATE ${SDL2_LIBRARIES})
endif()

