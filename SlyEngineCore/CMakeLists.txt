cmake_minimum_required(VERSION 3.12)

#project(SlyEngineCore)

set(ENGINE_PROJECT_NAME SlyEngineCore)

# Установка статической сборки SFML
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(
  sfml
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG        2.6.x
)
FetchContent_MakeAvailable(sfml)

set(ENGINE_PUBLIC_INCLUDES
	includes/SlyEngineCore/test.h
)
set(ENGINE_PRIVATE_SOURCES
	src/SlyEngineCore/test.cpp
)
set(ENGINE_ALL_SOURCES
	${ENGINE_PUBLIC_INCLUDES}
	${ENGINE_PRIVATE_SOURCES}
)

add_library(${ENGINE_PROJECT_NAME} STATIC ${ENGINE_ALL_SOURCES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_ALL_SOURCES})

target_include_directories(${ENGINE_PROJECT_NAME}
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/includes
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)

# Линковка с библиотеками SFML
target_link_libraries(${ENGINE_PROJECT_NAME} sfml-graphics sfml-audio sfml-system)

# Копирование DLL, если SFML собрана как динамическая библиотека
if(WIN32 AND NOT BUILD_SHARED_LIBS)
    add_custom_command(
        TARGET ${ENGINE_PROJECT_NAME} POST_BUILD
        COMMENT "Copy SFML DLLs"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SFML_BINARY_DIR}/lib $<TARGET_FILE_DIR:${ENGINE_PROJECT_NAME}>
        VERBATIM)
endif()

# Установка цели
install(TARGETS ${ENGINE_PROJECT_NAME} DESTINATION lib)
