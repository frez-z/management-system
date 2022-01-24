cmake_minimum_required(VERSION 3.21)
project(management_system C)

set(CMAKE_C_STANDARD 11)

include_directories(includes)
include_directories(includes/screens)
include_directories(includes/resource)

set(    COMMON_SOURCES
        resource/sqlite3.c   # sqlite library
        resource/database.c  # handle database query
        resource/file_checker.c # checks file/directory existent
        resource/console.c
)

set(TARGET_SOURCES
        src/main.c # main entry

        # screen  functionality
        src/screens/admin.c
        src/screens/setupApp.c
        )

set(TEST_SOURCES
        test/main_test.c
        resource/test.c
        )

add_executable(application ${COMMON_SOURCES} ${TARGET_SOURCES})
add_executable(tests ${COMMON_SOURCES} ${TEST_SOURCES})