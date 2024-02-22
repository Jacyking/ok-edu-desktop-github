project(Backend)

set(PROJECT_Sources
        BaseService.cpp
        ChatService.cpp
        HttpService.cpp
        UserService.cpp
        BookedService.cpp
        PassportService.h
        PassportService.cpp
        PushService.cpp
        User.h
        User.cpp
)

add_library(${PROJECT_NAME} ${PROJECT_Sources})

if (MSVC)
    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif (MSVC)