# The hook library

add_executable(dummy dummy.cpp)

add_library(dllsample SHARED dllsample.cpp)
target_link_libraries(dllsample PRIVATE lib_detours)
set_target_properties(dllsample PROPERTIES LINK_FLAGS /EXPORT:DetourFinishHelperProcess,@1,NONAME)


# With dll that runs the dummy executable with the dllsample (hook) injected
add_executable(runwithdll runwithdll.cpp pipe.cpp)
target_link_libraries(runwithdll lib_detours)
