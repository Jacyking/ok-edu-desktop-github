# INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/gloox
# project(gloox)

set(CMAKE_MAKE_PROGRAM make)
message(STATUS "目录：" ${CMAKE_CURRENT_SOURCE_DIR})

# include(ExternalProject)
# ExternalProject_Add(gloox
# SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/gloox
# CONFIGURE_COMMAND "cd ${CMAKE_CURRENT_SOURCE_DIR}/gloox && ./configure"
# BUILD_COMMAND "cd ${CMAKE_CURRENT_SOURCE_DIR}/gloox && make"
# INSTALL_COMMAND "cd ${CMAKE_CURRENT_SOURCE_DIR}/gloox && make install"
# )

# add_custom_command(OUTPUT gloox
# COMMAND ${CMAKE_COMMAND} -E echo compile finish
# VERBATIM
# )
add_custom_target(gloox ALL
    DEPENDS rtc

    COMMAND ${CMAKE_MAKE_PROGRAM}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/gloox
    COMMENT "gloox makefile target"
)

# add_library(gloox)

# link_directories(
# "${CMAKE_CURRENT_SOURCE_DIR}/lib"
# )
# set(gloox ${CMAKE_CURRENT_SOURCE_DIR}/gloox/.libs/libgloox.so)