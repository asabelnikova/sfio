file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
include_directories(${CMAKE_BINARY_DIR}/proto)
include_directories(${WEBSOCKETPP_INCLUDE_DIR})
add_executable(sfio ${SRC_LIST})
set_property(TARGET sfio  PROPERTY CXX_STANDARD 14)
set (libs ${Boost_LIBRARIES} ${WEBSOCKETPP_LIB} ssl crypto)
target_link_libraries(sfio proto ${libs})
install(TARGETS ${EXEC_NAME} DESTINATION bin)
