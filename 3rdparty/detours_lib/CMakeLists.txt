# Detours
set(TARGET lib_detours)
set(DETOURS_SOURCE Detours/src)

add_library(${TARGET} STATIC
    ${DETOURS_SOURCE}/creatwth.cpp
    ${DETOURS_SOURCE}/detours.cpp
    ${DETOURS_SOURCE}/detours.h
    ${DETOURS_SOURCE}/detver.h
    ${DETOURS_SOURCE}/disasm.cpp
    ${DETOURS_SOURCE}/disolarm.cpp
    ${DETOURS_SOURCE}/disolarm64.cpp
    ${DETOURS_SOURCE}/disolia64.cpp
    ${DETOURS_SOURCE}/disolx64.cpp
    ${DETOURS_SOURCE}/disolx86.cpp
    ${DETOURS_SOURCE}/image.cpp
    ${DETOURS_SOURCE}/modules.cpp
    ${DETOURS_SOURCE}/uimports.cpp)

# This file is included and not compiled on its own
set_property (
    SOURCE ${DETOURS_SOURCE}/uimports.cpp
    APPEND PROPERTY HEADER_FILE_ONLY true)

target_compile_options(${TARGET} PRIVATE /W4 /WX /Zi /MT /Gy /Gm- /Zl /Od)
target_include_directories(${TARGET} PUBLIC ${DETOURS_SOURCE})

# withdll
add_executable(withdll Detours/samples/withdll/withdll.cpp)
target_link_libraries(withdll lib_detours)

# Static library for the syelog components
add_library(syelog STATIC Detours/samples/syelog/syelog.cpp
                          Detours/samples/syelog/syelog.h)
target_include_directories(syelog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Detours/samples/syelog)
target_link_libraries(syelog PUBLIC lib_detours ws2_32 secur32)


# syelogd
add_executable(syelogd Detours/samples/syelog/syelogd.cpp 
                       Detours/samples/syelog/syelog.h)
target_link_libraries(syelogd PRIVATE lib_detours)

# traceapi example
add_library(traceapi SHARED Detours/samples/traceapi/trcapi.cpp 
                            Detours/samples/traceapi/trcapi.rc)
target_link_libraries(traceapi PRIVATE syelog)
set_target_properties(traceapi PROPERTIES LINK_FLAGS /EXPORT:DetourFinishHelperProcess,@1,NONAME)


# tracemem example
add_library(tracemem SHARED Detours/samples/tracemem/trcmem.cpp 
                            Detours/samples/tracemem/trcmem.rc)
target_link_libraries(tracemem PRIVATE syelog)
set_target_properties(tracemem PROPERTIES LINK_FLAGS /EXPORT:DetourFinishHelperProcess,@1,NONAME)

# tracessl example
add_library(tracessl SHARED Detours/samples/tracessl/trcssl.cpp Detours/samples/tracessl/trcssl.rc)
target_link_libraries(tracessl PRIVATE syelog)
set_target_properties(tracessl PROPERTIES LINK_FLAGS /EXPORT:DetourFinishHelperProcess,@1,NONAME)

# traceser example
add_library(traceser SHARED Detours/samples/traceser/trcser.cpp 
                            Detours/samples/traceser/trcser.rc)
target_link_libraries(traceser PRIVATE syelog)
set_target_properties(traceser PROPERTIES LINK_FLAGS /EXPORT:DetourFinishHelperProcess,@1,NONAME)

# tracereg example
add_library(tracereg SHARED Detours/samples/tracereg/trcreg.cpp 
                            Detours/samples/tracereg/trcreg.rc)
target_link_libraries(tracereg PRIVATE syelog)
set_target_properties(tracereg PROPERTIES LINK_FLAGS /EXPORT:DetourFinishHelperProcess,@1,NONAME)


# dumpe example
add_executable(dumpe Detours/samples/dumpe/dumpe.cpp )
target_link_libraries(dumpe PRIVATE lib_detours)
set_target_properties(dumpe PROPERTIES LINK_FLAGS /EXPORT:DetourFinishHelperProcess,@1,NONAME)

# dumpi example
add_executable(dumpi Detours/samples/dumpi/dumpi.cpp )
target_link_libraries(dumpi PRIVATE lib_detours)
set_target_properties(dumpi PROPERTIES LINK_FLAGS /EXPORT:DetourFinishHelperProcess,@1,NONAME)

# trcbld.cpp example
add_library(trcbld SHARED Detours/samples/tracebld/trcbld.cpp )
target_link_libraries(trcbld PRIVATE syelog)
set_target_properties(trcbld PROPERTIES LINK_FLAGS /EXPORT:DetourFinishHelperProcess,@1,NONAME)


add_executable(tracebld Detours/samples/tracebld/tracebld.cpp )
target_link_libraries(tracebld PRIVATE lib_detours)
set_target_properties(tracebld PROPERTIES LINK_FLAGS /EXPORT:DetourFinishHelperProcess,@1,NONAME)

