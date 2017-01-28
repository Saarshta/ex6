cmake_minimum_required(VERSION 3.6)
project(ex6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread")

set(SOURCE_FILES src/ThreadInfo.cpp src/ThreadInfo.h src/Tcp.cpp src/Tcp.h src/DriverOperator.h src/DriverOperator.cpp src/Socket.h src/Socket.cpp  src/AbstractNode.cpp src/AbstractNode.h src/Bfs.cpp src/Bfs.h src/Matrix.cpp src/Matrix.h src/MatrixNode.cpp src/MatrixNode.h src/Point.cpp src/Point.h src/Defines.h  src/Driver.cpp src/Driver.h src/Cab.cpp src/Cab.h src/Map.cpp src/Map.h src/Passenger.cpp src/Passenger.h src/TaxiCenter.cpp src/TaxiCenter.h src/LuxuryCab.cpp src/LuxuryCab.h src/StandardCab.cpp src/StandardCab.h src/Color.h src/Manufacturer.h src/Status.h src/Trip.cpp src/Trip.h  src/MainFlow.cpp src/MainFlow.h src/SearchAlgorithm.h src/AbstractPoint.cpp src/AbstractPoint.h src/MapRestartListener.cpp src/MapRestartListener.h src/SearchAlgorithm.cpp src/InputParser.cpp src/InputParser.h)

add_executable(ex6 ${SOURCE_FILES} main.cpp src/ThreadPool.cpp src/ThreadPool.h src/Job.cpp src/Job.h src/InputParser.cpp src/InputParser.h src/ThreadInfo.cpp src/ThreadInfo.h src/Tcp.cpp src/Tcp.h src/Socket.h src/Socket.cpp  src/Defines.h  src/Driver.cpp src/Driver.h src/Cab.cpp src/Cab.h src/Map.cpp src/Map.h src/Passenger.cpp src/Passenger.h src/TaxiCenter.cpp src/TaxiCenter.h src/LuxuryCab.cpp src/LuxuryCab.h src/StandardCab.cpp src/StandardCab.h src/Color.h src/Manufacturer.h src/Status.h src/Trip.cpp src/Trip.h  src/MainFlow.cpp src/MainFlow.h src/SearchAlgorithm.h src/AbstractPoint.cpp src/AbstractPoint.h src/InputParser.cpp src/InputParser.h)
add_executable(client ${SOURCE_FILES} client.cpp src/InputParser.cpp src/ThreadPool.cpp src/ThreadPool.h src/Job.cpp src/Job.h src/InputParser.h src/DriverOperator.cpp src/InputParser.cpp src/InputParser.h)
set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.57.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(client ${Boost_LIBRARIES})
target_link_libraries(ex6 ${Boost_LIBRARIES})
