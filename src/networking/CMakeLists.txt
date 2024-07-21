set(NETWORK_SOURCES
    NetworkServer.cpp
    NetworkClient.cpp
)

set(NETWORK_HEADERS
    NetworkServer.h
    NetworkClient.h
)

add_library(NetworkLib ${NETWORK_SOURCES} ${NETWORK_HEADERS})
set_target_properties(NetworkLib PROPERTIES PREFIX "")
target_include_directories(NetworkLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})