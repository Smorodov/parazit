
    #target.dll
    add_library(target SHARED target.cpp)   
    set_target_properties(target PROPERTIES LINK_FLAGS /EXPORT:Target)


   #extend.dll 
    add_library(extend SHARED extend.cpp) 
    set_target_properties(extend PROPERTIES LINK_FLAGS /export:DetourFinishHelperProcess,@1,NONAME) 
    target_link_libraries(extend PRIVATE  lib_detours)
    

    add_executable(findfunc_example findfunc.cpp)
    target_link_libraries(findfunc_example PRIVATE  lib_detours)
