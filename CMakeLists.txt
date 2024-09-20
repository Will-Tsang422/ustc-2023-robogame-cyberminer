cmake_minimum_required(VERSION 3.12)
project(CyberMiner VERSION 1.0.0 LANGUAGES C CXX)
# add_definitions( -lpthread )
find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
file(GLOB INCS source/Inc/*)
add_library(libs STATIC ${INCS})
set_target_properties(libs PROPERTIES LINKER_LANGUAGE CXX)
include_directories(source/Inc)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(cyberminer launch.cpp
                source/Src/white_balance.cpp
                source/Src/serial_connect.cpp
                source/Src/detect_color.cpp
                source/Src/ranging.cpp
                )
target_link_libraries(cyberminer ${OpenCV_LIBS})
target_link_libraries(cyberminer libs)
target_link_libraries(cyberminer ${WIRINGPI_LIBRARIES}  -lpthread)