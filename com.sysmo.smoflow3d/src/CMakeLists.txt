#######################################
# CoolProp Import
#######################################
SET(COOLPROP_LOCATION ${CMAKE_SOURCE_DIR}/../../coolprop/CoolProp)
message("Coolprop location: ${COOLPROP_LOCATION}")
add_library(CoolProp SHARED IMPORTED)
set_property(TARGET CoolProp PROPERTY IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/bin/libCoolProp.dll")
set_property(TARGET CoolProp PROPERTY IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/bin/libCoolProp.dll.a")
include_directories(${COOLPROP_LOCATION})

#######################################
# SmoFlow
#######################################
add_library(SmoFlow SHARED
    util/CodeTiming.cpp
    util/CachedProperty.cpp
    media/Medium.cpp
    media/MediumState.cpp
    media/MediumStateFluidCoolProp.cpp
    flow/FluidFlow.cpp
    flow/TwoPortValve.cpp
    volumes/FluidChamber.cpp
)

target_link_libraries(SmoFlow CoolProp)

install(TARGETS SmoFlow
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin    
    ARCHIVE DESTINATION bin    
)

#######################################
# SmoFlow Tests
#######################################

add_executable(TestMediaHydrogen
    test/MediaHydrogen.cpp
)

target_link_libraries(TestMediaHydrogen SmoFlow CoolProp)

install(TARGETS 
    TestMediaHydrogen
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin    
)
