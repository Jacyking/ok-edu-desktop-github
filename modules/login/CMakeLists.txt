project(Login)

set(PROJECT_SOURCES
    LoginJwt.cpp
    LoginManager.cpp
)

add_library(${PROJECT_NAME} ${PROJECT_SOURCES})