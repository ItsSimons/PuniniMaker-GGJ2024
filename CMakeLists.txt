cmake_minimum_required(VERSION 3.14)
project(GGJ2024)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/modules")

#------------------------------------------------------------------------------
# TMX getting imported inside this project
#------------------------------------------------------------------------------
message(STATUS  "TMXLITE:")
list(APPEND CMAKE_MESSAGE_INDENT "  ")
message(STATUS "+ FETCHING TMXLITE TILED IMPORTER....")

if(BUILD_SHARED_LIBS)
    set (TMXLITE_STATIC_LIB "OFF" CACHE INTERNAL "OFF")
else()
    set (TMXLITE_STATIC_LIB "ON"  CACHE INTERNAL "ON")
endif()

include(FetchContent)
FetchContent_Declare(
        tmxlite
        GIT_REPOSITORY https://github.com/fallahn/tmxlite.git
        GIT_TAG        origin/master)

message(STATUS "+ CONFIGURING TMXLITE....")
list(APPEND CMAKE_MESSAGE_INDENT "  ")

FetchContent_GetProperties(tmxlite)
if(NOT tmxlite_POPULATED)
    # Fetch the content using previously declared details
    FetchContent_Populate(tmxlite)
    add_subdirectory(${tmxlite_SOURCE_DIR}/tmxlite ${tmxlite_BINARY_DIR})
endif()

list(POP_BACK CMAKE_MESSAGE_INDENT)

set_target_properties(tmxlite PROPERTIES CXX_CLANG_TIDY "")
set_target_properties(tmxlite PROPERTIES CXX_CPPCHECK   "")
set_target_properties(tmxlite PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES $<TARGET_PROPERTY:tmxlite,INTERFACE_INCLUDE_DIRECTORIES>)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" AND ("x${CMAKE_CXX_SIMULATE_ID}" STREQUAL "xMSVC"))
    target_compile_options(tmxlite PRIVATE /EHsc)
endif()

message(STATUS "+ DONE")
list(POP_BACK CMAKE_MESSAGE_INDENT)
#------------------------------------------------------------------------------
# END of the TMX cmake section
#------------------------------------------------------------------------------

if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
set(SOURCE_FILES src/main.cpp src/GameInstance.cpp src/GameInstance.h src/Addons/ImageResizer.cpp src/Addons/ImageResizer.h
        src/Components/GameData.h src/Interfaces/StateTemplate.h src/GameStates/GameStart.cpp src/GameStates/GameStart.h
        src/GameStates/GamePlay.cpp src/GameStates/GamePlay.h src/GameStates/GameEnd.cpp src/GameStates/GameEnd.h
        src/GameStates/Test/TestEnvironment.cpp src/GameStates/Test/TestEnvironment.h src/Components/Helper.h
        src/GameStates/GameStart.cpp src/Components/ResourceManager.hpp
        src/Cards/BaseCard.cpp
        src/Cards/BaseCard.h
        src/Cards/BaseCard.h)

add_executable(GGJ2024 ${SOURCE_FILES})

target_link_libraries (GGJ2024 sfml-graphics sfml-window sfml-system sfml-network sfml-audio)

#Links TMX with the compiler
target_link_libraries (GGJ2024 tmxlite)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)