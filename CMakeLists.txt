cmake_minimum_required (VERSION 3.21)
project(cplt_template_compilation_exe VERSION 1.0)

include(FetchContent)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if(CMAKE_BUILD_TYPE MATCHES Debug)
     set(TREE_SITTER_EXE_CONFIG "Debug")
else()
     set(TREE_SITTER_EXE_CONFIG "Release")
endif()


# use find package to find the cplt library
FetchContent_Declare(
        tree_sitter_dll
        GIT_REPOSITORY https://github.com/niyuzheno1/tree-sitter-cmake-support.git
        GIT_TAG        58386af38e8e47882db4ac881ab367c0ee4946b7 # release-0.0.1
)
FetchContent_MakeAvailable(tree_sitter_dll)
list(APPEND EXTRA_LIBS tree_sitter_dll)

FetchContent_Declare(
     tree_sitter_cplt
     GIT_REPOSITORY https://github.com/niyuzheno1/tree-sitter-cplt.git
     GIT_TAG        6523991725f7cdcf25e76b1263567664e07b42d0 # release-0.0.1
)


FetchContent_MakeAvailable(tree_sitter_cplt)
list(APPEND EXTRA_LIBS tree_sitter_cplt)

# setting source file directory as src and header file directory as include 
set(CPLT_TEMPLATE_COMPILATION_EXE_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CPLT_TEMPLATE_COMPILATION_EXE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB CPLT_TEMPLATE_COMPILATION_EXE_SRC_FILES ${CPLT_TEMPLATE_COMPILATION_EXE_SRC_DIR}/*.cpp)

add_executable(cplt_template_compilation_exe ${CPLT_TEMPLATE_COMPILATION_EXE_SRC_FILES})
target_include_directories(cplt_template_compilation_exe PUBLIC ${CPLT_TEMPLATE_COMPILATION_EXE_INCLUDE_DIR})
target_link_libraries(cplt_template_compilation_exe PUBLIC ${EXTRA_LIBS})

add_custom_command(TARGET cplt_template_compilation_exe POST_BUILD 
               COMMAND ${CMAKE_COMMAND} -E copy  $<TARGET_FILE:tree_sitter_dll>  ${CMAKE_BINARY_DIR}/${TREE_SITTER_EXE_CONFIG}/tree_sitter_dll.dll  )
