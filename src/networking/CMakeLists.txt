set(NETWORK_SOURCES
    NetworkServer.cpp
    NetworkClient.cpp
    Connection.cpp
)

set(NETWORK_HEADERS
    NetworkServer.h
    NetworkClient.h
    Connection.h
    Data.h
)

add_library(NetworkLib ${NETWORK_SOURCES} ${NETWORK_HEADERS})
set_target_properties(NetworkLib PROPERTIES PREFIX "")
target_link_libraries(NetworkLib PRIVATE SDL3::SDL3 SDL3_net::SDL3_net)
target_include_directories(NetworkLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})