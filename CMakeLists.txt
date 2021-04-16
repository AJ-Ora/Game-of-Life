# CMakeList.txt : CMake project for Game-of-Life, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Game-of-Life")

# Specify the C++ standard
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED True)

# Add include and link directories
include_directories("${PROJECT_SOURCE_DIR}/include")

# Compile definitions required by wxWidgets
add_compile_definitions("UNICODE" "_UNICODE" "wxMSVC_VERSION_AUTO" "WXUSINGDLL")

# Solve operating system differences
set (MainOrWinMain "")

if (WIN32)
	set (MainOrWinMain "WIN32")
	include_directories("${PROJECT_SOURCE_DIR}/include/msvc")
	link_directories("${PROJECT_SOURCE_DIR}/lib/vc142_x64_dll")
elseif(UNIX AND NOT APPLE)
	set (CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -no-pie")
	find_package(wxWidgets REQUIRED COMPONENTS net core base)
	include(${wxWidgets_USE_FILE})
	link_libraries(${wxWidgets_LIBRARIES})
endif()

# Add source to this project's executable.
add_executable (Game-of-Life ${MainOrWinMain} "Game-of-Life.cpp"  "source/LifeBoard.cpp" "source/LifeBoard.h" "source/LifeBoardLogic.cpp" "source/LifeBoardLogic.h" "source/LifeBoardDrawing.cpp" "source/LifeBoardDrawing.h")

# Link OpenMP for parallelization.
find_package(OpenMP)
if (OpenMP_CXX_FOUND)
	target_link_libraries(Game-of-Life PUBLIC OpenMP::OpenMP_CXX)
endif()

# Handle copying Windows DLLs to the executable file's directory.
# The current way of manually copying the files is a very poor way to do this, but I don't know yet how to do it otherwise.
if (CMAKE_BUILD_TYPE STREQUAL "Debug" AND WIN32)
	file(COPY ${PROJECT_SOURCE_DIR}/lib/vc142_x64_dll/wxmsw30ud_core_vc142_x64.dll ${PROJECT_SOURCE_DIR}/lib/vc142_x64_dll/wxbase30ud_vc142_x64.dll DESTINATION ${CMAKE_BINARY_DIR})
endif()

# TODO: Add tests and install targets if needed.
