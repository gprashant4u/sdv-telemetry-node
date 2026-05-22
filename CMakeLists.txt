cmake_minimum_required(VERSION 3.10)
project(SDV_Telemetry_Node)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(paho-mqtt-cpp REQUIRED)
add_executable(telemetry_node src/main.cpp)
target_link_libraries(telemetry_node PahoMqttCpp::paho-mqtt-cpp)
