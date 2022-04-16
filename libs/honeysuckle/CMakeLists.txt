cmake_minimum_required(VERSION 3.2)
project(honeysuckle
  VERSION 0.1.0
  DESCRIPTION "A C library to make writing lua bindings simple")

find_package(Lua51 REQUIRED)
Include_directories(${LUA_INCLUDE_DIR})

# build and link the library
set(HS_ROOT ${honeysuckle_SOURCE_DIR}/src)
set(HONEYSUCKLE_SOURCES
  ${HS_ROOT}/hs_type_to_string.c
  ${HS_ROOT}/hs_pushstring.c
  ${HS_ROOT}/hs_throw_error.c
  ${HS_ROOT}/hs_parse_args.c
  ${HS_ROOT}/hs_create_table.c
  ${HS_ROOT}/hs_process_table.c
  ${HS_ROOT}/hs_traceback.c
  )
add_library(honeysuckle ${HONEYSUCKLE_SOURCES})
set_target_properties(honeysuckle PROPERTIES
  C_STANDARD 99
  CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wpedantic")
target_link_libraries(honeysuckle ${LUA_LIBRARIES})
set_target_properties(honeysuckle PROPERTIES
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER src/honeysuckle.h)


# optionally build the tests
set(TEST_ROOT ${honeysuckle_SOURCE_DIR}/src/tests)
set(TEST_SOURCES
  ${TEST_ROOT}/tests_main.c
  ${TEST_ROOT}/hs_type_to_string_tests.c
  ${TEST_ROOT}/hs_parse_args_tests.c
  ${TEST_ROOT}/hs_parse_overloaded_tests.c
  ${TEST_ROOT}/hs_create_table_tests.c
  ${TEST_ROOT}/hs_process_table_tests.c
  ${TEST_ROOT}/hs_throw_error_tests.c
  # ${TEST_ROOT}/hs_traceback_tests.c
  # ${TEST_ROOT}/hs_call_tests.c
  # ${TEST_ROOT}/hs_call_args_tests.c
  ${TEST_ROOT}/hs_pushstring_tests.c
  # ${TEST_ROOT}/hs_rxx_tests.c
  )
add_executable(hs-test EXCLUDE_FROM_ALL ${TEST_SOURCES})
set_target_properties(hs-test PROPERTIES
  C_STANDARD 99
  CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wpedantic")
target_link_libraries(hs-test ${LUA_LIBRARIES} honeysuckle)


# optionally build the examples
set(EX_ROOT ${honeysuckle_SOURCE_DIR}/examples)

add_executable(example_table_creation EXCLUDE_FROM_ALL
  ${EX_ROOT}/table_creation/table_creation.c)
set_target_properties(example_table_creation PROPERTIES
  C_STANDARD 99
  CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wpedantic")
target_link_libraries(example_table_creation ${LUA_LIBRARIES} honeysuckle)

add_executable(example_argument_parsing EXCLUDE_FROM_ALL
  ${EX_ROOT}/argument_parsing/argument_parsing.c)
set_target_properties(example_argument_parsing PROPERTIES
  C_STANDARD 99
  CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wpedantic")
target_link_libraries(example_argument_parsing ${LUA_LIBRARIES} honeysuckle)

add_executable(example_table_processing EXCLUDE_FROM_ALL
  ${EX_ROOT}/table_processing/table_processing.c)
set_target_properties(example_table_processing PROPERTIES
  C_STANDARD 99
  CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wpedantic")
target_link_libraries(example_table_processing ${LUA_LIBRARIES} honeysuckle)


add_custom_target(examples)
add_dependencies(examples
  example_table_creation
  example_argument_parsing
  example_table_processing)


include(GNUInstallDirs)

install(TARGETS honeysuckle
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
