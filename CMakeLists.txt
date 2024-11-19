cmake_minimum_required(VERSION 3.14)

project(AERSP_424_HW_2)

set(CMAKE_CXX_STANDARD 11)

# Add the subdirectory for matplotplusplus from the third_party directory
add_subdirectory(third_party/matplotplusplus)

# Add the source directory and the specific source file for the executable
#add_executable(Problem_1 src/Problem_1.cpp "src/Sensor.h" "src/TermperatureSensor.h")

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(Problem_1
    src/Problem_1.cpp
    "include/SensorFactory.cpp"
    "include/AerospaceControlSystem.cpp"
)

# Add the source directory and the specific source file for the executable
add_executable(Problem_2 src/Problem_2.cpp)

# Add the source directory and the specific source file for the executable
add_executable(Problem_3 src/Problem_3.cpp)

# Add the source directory and the specific source file for the executable
add_executable(Problem_4 src/Problem_4.cpp)



# Link the matplot library to your executable
target_link_libraries(Problem_4 PUBLIC matplot)
#test

# Specify the CSV file
set(CSV_FILE "include/polar_data.csv")

# Command to copy the CSV file to the executable's directory
add_custom_command(
    TARGET Problem_4 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/${CSV_FILE}  # Source CSV file
            $<TARGET_FILE_DIR:Problem_4>/   # Destination directory
)