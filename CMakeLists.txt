cmake_minimum_required(VERSION 3.0.0)

project(MathLang)
file(GLOB_RECURSE src
	CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

message(${src})

add_executable(ml ${src})
