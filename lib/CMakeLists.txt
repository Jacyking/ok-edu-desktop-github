add_subdirectory(messenger)
add_subdirectory(network )
add_subdirectory(ortc)
add_subdirectory(session)
add_subdirectory(settings)


if(ENABLE_PLUGINS)
add_subdirectory(plugin)
endif()

if(ENABLE_MODULE_PAINTER)
add_subdirectory(smartboard)
endif()