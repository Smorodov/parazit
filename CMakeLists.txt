cmake_minimum_required(VERSION 3.27)

project(parazit)


set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
# updated microsoft detours library
add_subdirectory(3rdparty)
# simple hooking
add_subdirectory(simple)
# hooking with injection and pipes interprocess communication
add_subdirectory(dllsample)



	foreach (trgt simple dllsample dummy runwithdll withdll traceapi syelogd tracessl)		
		set_target_properties( ${trgt} PROPERTIES  VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${trgt}>")
	endforeach()

