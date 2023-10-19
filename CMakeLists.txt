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

# Set the destination folder for all binaries in bin/configuration/*
#foreach(cfg IN LISTS CMAKE_CONFIGURATION_TYPES)
#    string(TOUPPER ${cfg} cfg)
#	foreach (trgt simple dllsample dummy runwithdll withdll traceapi syelogd tracessl)
#		set_target_properties(${trgt} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${cfg} ${CMAKE_CURRENT_BINARY_DIR}/bin/${cfg})
#	endforeach()
#endforeach()
