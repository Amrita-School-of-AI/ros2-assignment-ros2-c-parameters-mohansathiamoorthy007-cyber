cmake_minimum_required(VERSION 3.8)
project(ros2_parameters)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

# 1. Add executable using src/param_node.cpp
add_executable(param_node src/param_node.cpp)

# 2. Add dependencies (ament_target_dependencies) for rclcpp
# This handles the include directories and linking for the ROS2 libraries
ament_target_dependencies(param_node rclcpp)

# 3. Install the target to the DESTINATION lib/${PROJECT_NAME}
# This allows 'ros2 run ros2_parameters param_node' to find your binary
install(TARGETS
  param_node
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
