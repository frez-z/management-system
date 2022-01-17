cmake_minimum_required(VERSION 3.21)
project(management_system C)

set(CMAKE_C_STANDARD 11)

include_directories(includes)

add_executable(
        ${PROJECT_NAME}
        src/main.c  # main event
        src/resource/sqlite3.c   # sqlite library
        src/resource/database.c  # handle database query
        src/resource/file_checker.c # checks file/directory existent
)