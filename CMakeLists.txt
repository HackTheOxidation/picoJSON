cmake_minimum_required(VERSION 3.28)

project(picoJSON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(picoJSON)

target_include_directories(picoJSON 
  PUBLIC include/
  PRIVATE src/
)

target_sources(picoJSON
  PRIVATE
    src/Content.cpp
    src/Errors.cpp
    src/JSON.cpp
    src/JSONArray.cpp
    src/JSONObject.cpp
    src/Lexer.cpp
    src/Parser.cpp
    src/Reader.cpp

  PUBLIC
    FILE_SET headers
    TYPE HEADERS
    BASE_DIRS
      include
    FILES
      include/picoJSON/Content.hpp
      include/picoJSON/Errors.hpp
      include/picoJSON/JSON.hpp
      include/picoJSON/JSONArray.hpp
      include/picoJSON/JSONObject.hpp
      include/picoJSON/Lexer.hpp
      include/picoJSON/Parser.hpp
      include/picoJSON/picoJSON.hpp
      include/picoJSON/Reader.hpp
      include/picoJSON/Token.hpp
)

enable_testing()
add_subdirectory("deps")
add_subdirectory("test")

install(TARGETS picoJSON)

set(CPACK_PACKAGE_NAME picoJSON)
set(CPACK_PACKAGE_VENDOR HackTheOxidation)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A minimalist parser for JSON")

set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})
set(CPACK_VERBATIM_VARIABLES TRUE)

include(CPack)

if(WIN32)
  set(CPACK_GENERATOR ZIP WIX)
elseif(APPLE)
  set(CPACK_GENERATOR TGZ productbuild)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(CPACK_GENERATOR TGZ RPM APT)
else()
  set(CPACK_GENERATOR TGZ)
endif()
