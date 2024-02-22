project(OkPlayer)

set(PROJECT_SOURCES
    playerwindow.cpp
)

add_library(${PROJECT_NAME} ${PROJECT_SOURCES})

# link_directories(${CMAKE_SOURCE_DIR}/3rdparty/QtAV)
# target_link_libraries(${PROJECT_NAME} QtAV)
