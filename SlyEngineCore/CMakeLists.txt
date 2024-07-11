cmake_minimum_required(VERSION 3.12)

set(ENGINE_PROJECT_NAME SlyEngineCore)

include(FetchContent)

FetchContent_Declare(
  sfml
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG        2.6.1
)
FetchContent_MakeAvailable(sfml)

set(ENGINE_PUBLIC_INCLUDES
	includes/SlyEngineCore/test.h
)
set(ENGINE_PUBLIC_SOURCES
	src/SlyEngineCore/test.cpp
)
set(ENGINE_ALL_SOURCES
	${ENGINE_PUBLIC_INCLUDES}
	${ENGINE_PUBLIC_SOURCES}
)

add_library(${ENGINE_PROJECT_NAME} STATIC ${ENGINE_ALL_SOURCES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_ALL_SOURCES})

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC
	includes
)

target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${ENGINE_PROJECT_NAME} sfml-graphics sfml-audio sfml-system)

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC ${sfml_SOURCE_DIR}/include)