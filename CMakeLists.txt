cmake_minimum_required(VERSION 3.4)
set(APP_NAME at_client)
project(${APP_NAME})
string(TOLOWER  ${CMAKE_SYSTEM_NAME} OS_NAME)
file(REAL_PATH "~" HOME EXPAND_TILDE)

# This application
add_executable(${APP_NAME} u_cx_at_client.c u_cx_at_util.c main.c)

if (DEFINED ENV{UBXLIB_DIR})
  # Get and build the ubxlib library
  set(UBXLIB_BASE $ENV{UBXLIB_DIR})
  include(${UBXLIB_BASE}/port/platform/${OS_NAME}/${OS_NAME}.cmake)
  target_link_libraries(${APP_NAME} ubxlib ${UBXLIB_REQUIRED_LINK_LIBS})
  target_include_directories(${APP_NAME} PUBLIC ${UBXLIB_INC} ${UBXLIB_PUBLIC_INC_PORT})
else()
  message(FATAL_ERROR "Ubxlib location not defined")
endif()
