cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 11)

project(initproj LANGUAGES C CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
if (WIN32)
  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}")
endif()

add_executable(template)
target_sources(template PRIVATE src/main.cpp src/main.hpp src/pch.h)
target_include_directories(template PRIVATE external/rapidjson external/rapidxml)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/assets/Image5.png)
  file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/Image5.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)
endif()
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/assets/testfont.ttf)
  file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/testfont.ttf
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/assets/test.xm)
  file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/test.xm
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)
endif()

if(${EMSCRIPTEN})

  set(CMAKE_VERBOSE_MAKEFILE ON)
  
  
  target_include_directories(template PRIVATE gles3/include gles3/include/glad)
  
  target_sources(template PRIVATE gles3/src/glad.c)
  target_sources(template PRIVATE gles3/include/glad/glad.h)
  target_sources(template PRIVATE gles3/include/KHR/khrplatform.h)
  
  target_precompile_headers(template PRIVATE src/pch.h)

  target_sources(template PRIVATE src/em_main.cpp)
  
  if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")

    target_compile_options(template PRIVATE -gsource-map)
    
    target_link_options(template PRIVATE -v)
    target_link_options(template PRIVATE -sASSERTIONS=2)
    target_link_options(template PRIVATE -sSTACK_OVERFLOW_CHECK=2)
    target_link_options(template PRIVATE -sCHECK_NULL_WRITES=1)
    target_link_options(template PRIVATE -sVERBOSE=1)
    target_link_options(template PRIVATE -sRUNTIME_DEBUG=1)
    target_link_options(template PRIVATE -gsource-map)

  elseif(${CMAKE_BUILD_TYPE} IN_LIST "Release")

    message("release")

  endif()

  target_compile_options(template PRIVATE --use-port=sdl2)
  target_compile_options(template PRIVATE --use-port=sdl2_image:formats=bmp,gif,lbm,pcx,png,pnm,tga,xcf,xpm,xv)
  
  target_compile_options(template PRIVATE --use-port=sdl2_mixer:formats=ogg,mod,mid)
  target_compile_options(template PRIVATE --use-port=sdl2_ttf)
  target_compile_options(template PRIVATE --use-port=freetype)
  target_compile_options(template PRIVATE --use-port=harfbuzz)
  target_compile_options(template PRIVATE --use-port=sqlite3)
  
  target_link_options(template PRIVATE -sALLOW_MEMORY_GROWTH=1)
  target_link_options(template PRIVATE --use-port=sdl2)
  target_link_options(template PRIVATE --use-port=sdl2_image:formats=bmp,gif,lbm,pcx,png,pnm,tga,xcf,xpm,xv)
  target_link_options(template PRIVATE --use-port=sdl2_mixer:formats=ogg,mod,mid)
  target_link_options(template PRIVATE --use-port=sdl2_ttf)
  target_link_options(template PRIVATE --use-port=freetype)
  target_link_options(template PRIVATE --use-port=harfbuzz)
  target_link_options(template PRIVATE --use-port=sqlite3)
  
  target_link_options(template PRIVATE -sFULL_ES3=1 -sMIN_WEBGL_VERSION=2)
  target_link_options(template PRIVATE --preload-file assets)
  target_link_options(template PRIVATE --shell-file ../shell.html)
  
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  
else()

  find_package(SDL2)
  find_package(SDL2_image)
  find_package(SDL2_mixer)
  find_package(SDL2_ttf)
  
  target_include_directories(template PRIVATE gl46/include gl46/include/glad)
  
  target_sources(template PRIVATE gl46/include/glad/glad.h)
  target_sources(template PRIVATE gl46/include/KHR/khrplatform.h) 
  target_sources(template PRIVATE gl46/src/glad.c)
  
  target_include_directories(template PRIVATE external/sqlite3)
  target_sources(template PRIVATE external/sqlite3/sqlite3.c external/sqlite3/sqlite3.h external/sqlite3/sqlite3ext.h)
  
  target_sources(template PRIVATE src/desktop_main.cpp)

  target_precompile_headers(template PRIVATE src/pch.h)

  target_link_libraries(template PRIVATE SDL2_mixer::SDL2_mixer)
  target_link_libraries(template PRIVATE SDL2_image::SDL2_image)
  target_link_libraries(template PRIVATE SDL2_ttf::SDL2_ttf)
  target_link_libraries(template PRIVATE SDL2::SDL2 SDL2::SDL2main)
  

  if (WIN32)
    add_custom_command(TARGET template POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:template> $<TARGET_RUNTIME_DLLS:template>
      COMMAND_EXPAND_LISTS
    )
  endif()
endif()
