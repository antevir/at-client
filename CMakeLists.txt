cmake_minimum_required(VERSION 3.4)
project(at_client)
string(TOLOWER  ${CMAKE_SYSTEM_NAME} OS_NAME)
file(REAL_PATH "~" HOME EXPAND_TILDE)

if (DEFINED ENV{UBXLIB_DIR})
  set(APP_NAME_UBXLIB at_client)
  # This application
  add_executable(${APP_NAME_UBXLIB} u_cx_at_client.c u_cx_at_util.c u_ubxlib_main.c)

  # Get and build the ubxlib library
  set(UBXLIB_BASE $ENV{UBXLIB_DIR})
  include(${UBXLIB_BASE}/port/platform/${OS_NAME}/${OS_NAME}.cmake)
  target_link_libraries(${APP_NAME_UBXLIB} ubxlib ${UBXLIB_REQUIRED_LINK_LIBS})
  target_include_directories(${APP_NAME_UBXLIB} PUBLIC ${UBXLIB_INC} ${UBXLIB_PUBLIC_INC_PORT})
else()
  message(WARNING "Ubxlib location not defined (UBXLIB_BASE) - not building ubxlib app")
endif()


set(APP_NAME_TEST at_client_test)
# This application
add_executable(${APP_NAME_TEST} u_cx_at_client.c u_cx_at_util.c u_main_test.c)
