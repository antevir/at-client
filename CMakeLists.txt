cmake_minimum_required(VERSION 3.4)
set(APP_NAME at_client)
project(${APP_NAME})
string(TOLOWER  ${CMAKE_SYSTEM_NAME} OS_NAME)
file(REAL_PATH "~" HOME EXPAND_TILDE)

# This application
add_executable(${APP_NAME} u_cx_at_client.c u_cx_at_util.c main.c)

if (USE_UBXLIB)
  # Get and build the ubxlib library
  #set(UBXLIB_BASE ${CMAKE_CURRENT_LIST_DIR}/ubxlib)
  set(UBXLIB_BASE "${HOME}/Dropbox/ublox/dev/libs/ubxlib_priv_dev")
  include(${UBXLIB_BASE}/port/platform/${OS_NAME}/${OS_NAME}.cmake)
  target_link_libraries(${APP_NAME} ubxlib ${UBXLIB_REQUIRED_LINK_LIBS})
  target_include_directories(${APP_NAME} PUBLIC ${UBXLIB_INC} ${UBXLIB_PUBLIC_INC_PORT})
endif()

