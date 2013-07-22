#######################################
# CoolProp Import
#######################################
SET(COOLPROP_LOCATION ${CMAKE_SOURCE_DIR}/../../coolprop/CoolProp)
message("Coolprop location: ${COOLPROP_LOCATION}")
add_library(CoolProp SHARED IMPORTED)
set_property(TARGET CoolProp PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/bin/CoolProp.dll)
include_directories(${COOLPROP_LOCATION})
#######################################
# SmoFlow
#######################################
add_library(SmoFlow SHARED
    media/MediaState.cpp
)

target_link_libraries(SmoFlow CoolProp)

install(TARGETS SmoFlow
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin    
)

#######################################
# SmoFlow Tests
#######################################

add_executable(TestMediaHydrogen 
    test/MediaHydrogen.cpp
)

target_link_libraries(TestMediaHydrogen SmoFlow)

install(TARGETS 
    TestMediaHydrogen
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin    
)
