set(NETWORK_SOURCES
    NetworkServer.cpp
    NetworkClient.cpp
    Connection.cpp
    AsioImpl.cpp
)

set(NETWORK_HEADERS
    NetworkServer.h
    NetworkClient.h
    Connection.h
    Data.h
)

add_library(NetworkLib ${NETWORK_SOURCES} ${NETWORK_HEADERS})
if(WIN32)
  target_link_libraries(NetworkLib PRIVATE ws2_32 mswsock bcrypt)
endif()
set_target_properties(NetworkLib PROPERTIES PREFIX "")
target_compile_definitions(NetworkLib PRIVATE ASIO_STANDALONE ASIO_SEPARATE_COMPILATION)
target_include_directories(NetworkLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})