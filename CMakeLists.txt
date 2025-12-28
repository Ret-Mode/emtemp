cmake_minimum_required(VERSION 3.18)
set (CMAKE_CXX_STANDARD 11)

project(initproj LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
if (WIN32)
  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}")
endif()

add_executable(template)
target_sources(template PRIVATE src/main.cpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/Image5.png
      DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)

      
if(${EMSCRIPTEN})

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

  #target_include_directories(template PRIVATE ${SDL2_INCLUDE_DIRS})
  #target_link_libraries(template PRIVATE ${SDL2_LIBRARIES})

  target_include_directories(template PRIVATE SDL2::SDL2)
  target_include_directories(template PRIVATE SDL2_image::SDL2_image)
  target_link_libraries(template PRIVATE SDL2_image::SDL2_image)
  target_link_libraries(template PRIVATE  SDL2::SDL2 SDL2::SDL2main)

  if (WIN32)
    add_custom_command(TARGET template POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:template> $<TARGET_RUNTIME_DLLS:template>
      COMMAND_EXPAND_LISTS
    )
  endif()
endif()

