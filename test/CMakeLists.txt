SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g")
SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O0 -g")

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include/)

LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/)

ADD_EXECUTABLE(unittest 
    test.cc
)

TARGET_LINK_LIBRARIES(unittest 
    lemon_parser
    pthread
    ${CMAKE_SOURCE_DIR}/lib/libgtest.a
)

ADD_EXECUTABLE(perftest 
    performance_test.cc
)

TARGET_LINK_LIBRARIES(perftest 
    lemon_parser
    pthread
    ${CMAKE_SOURCE_DIR}/lib/libgtest.a
)

