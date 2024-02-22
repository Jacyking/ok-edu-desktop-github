
if(UNIX)
 find_package(ZLIB REQUIRED)
 include_directories(${ZLIB_INCLUDE_DIRS})
 find_package(MINIZIP QUIET)
elseif(WIN32)
 include_directories(${CMAKE_SOURCE_DIR}/build/deps/include)
endif()

set(DEPLIBS
        ${ZLIB_LIBRARIES}
        minizip
        
)


set(PLAIN_HEADERS
        zip.h
)

set(PLAIN_SOURCES
        zip.cpp
)


#set(PLAIN_SOURCES
#        ${PLAIN_SOURCES}
#        minizip/ioapi.c
#                minizip/miniunz.c
#                minizip/minizip.c
#        minizip/crypt.h
#        minizip/unzip.c
#        minizip/ioapi.c
#)
#if(WIN32)
#set(PLAIN_SOURCES
#        ${PLAIN_SOURCES}
#        minizip/iowin32.c
#)
#endif()

add_definitions(-DOK_MINIZIP)


add_library(zip STATIC ${PLAIN_SOURCES} ${PLAIN_HEADERS})

if(MSVC)
    set_property(TARGET zip PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif (MSVC)

target_link_libraries(zip ${QT_LIBRARIES} ${DEPLIBS})
target_include_directories(zip PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} minizip ..)

