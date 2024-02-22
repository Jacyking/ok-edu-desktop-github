project(IMCore)

include_directories(${WebRTC_DIR}/include)
include_directories(${GLOOX_DIR}/include)

set(${PROJECT_NAME}_SOURCES
        IM.h
        IM.cpp
        IMRoomHelper.cpp
        IMMessage.h
        IMMessage.cpp
#        IMConference.h
#        IMConference.cpp
        IMJingle.h
        IMJingle.cpp
        IMJingleSession.h
        IMJingleSession.cpp
        IMFile.h
        IMFile.cpp
        messenger.h
        messenger.cpp
        )



add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

if(MSVC)
    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif (MSVC)