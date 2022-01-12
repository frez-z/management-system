cmake_minimum_required(VERSION 3.22)
project(management_system C)

set(CMAKE_C_STANDARD 11)

include_directories(includes)
# set(HEADER_FILES includes/console.h)

add_executable(
        ${PROJECT_NAME}
        main.c includes/sql/sqlite3.c
)
