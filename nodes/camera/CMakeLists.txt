cmake_minimum_required(VERSION 3.14)

find_package(catkin REQUIRED COMPONENTS roscpp cv_bridge image_transport)
find_package(OpenCV)

add_executable(camera camera.cc)

target_include_directories(camera PRIVATE
	${roscpp_INCLUDE_DIRS}
	${cv_bridge_INCLUDE_DIRS}
	${image_transport_INCLUDE_DIRS}
	${OpenCV_INCLUDE_DIRS})
target_link_libraries(camera PRIVATE
	${roscpp_LIBRARIES}
	${cv_bridge_LIBRARIES}
	${image_transport_LIBRARIES}
	${OpenCV_LIBRARIES})
