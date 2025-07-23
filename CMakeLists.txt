# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.18)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set name of project (as PROJECT_NAME) and C/C++ standards
project(displaylib_LED_PICO C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

# turn on all compiler warnings 
add_compile_options(-Wall -Wextra)

# Tell CMake where to find the executable source file
add_executable(${PROJECT_NAME} 
  examples/tm1638/MODEL1/main.cpp
  #examples/tm1638/MODEL2/main.cpp
  #examples/tm1638/MODEL3/main.cpp

  #examples/tm1637/semi_colon/main.cpp
  #examples/tm1637/decimal_point/main.cpp

  #examples/max7219/tests/main.cpp
  #examples/max7219/cascade_demo/main.cpp
  #examples/max7219/bcdmode/main.cpp
  
  #examples/ht16k33/7_segment/main.cpp
  #examples/ht16k33/14_segment/main.cpp
)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

add_library(pico_displaylib_LED_PICO INTERFACE)

target_sources(pico_displaylib_LED_PICO INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/src/${PROJECT_NAME}/seven_segment_font_data.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/${PROJECT_NAME}/nine_segment_font_data.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/${PROJECT_NAME}/fourteen_segment_font_data.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/${PROJECT_NAME}/sixteen_segment_font_data.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/${PROJECT_NAME}/tm1638plus_model1.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/${PROJECT_NAME}/tm1638plus_model2.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/${PROJECT_NAME}/tm1638plus_model3.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/${PROJECT_NAME}/tm1638plus_common.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/${PROJECT_NAME}/tm1637.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/${PROJECT_NAME}/max7219.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/${PROJECT_NAME}/ht16k33.cpp
)

target_include_directories(pico_displaylib_LED_PICO INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

# Pull in pico libraries that we need
target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_i2c hardware_spi pico_displaylib_LED_PICO )

# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

