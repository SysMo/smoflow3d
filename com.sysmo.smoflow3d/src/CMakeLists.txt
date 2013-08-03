#######################################
# CoolProp Import
#######################################
SET(COOLPROP_LOCATION ${CMAKE_SOURCE_DIR}/../../coolprop)
message("Coolprop location: ${COOLPROP_LOCATION}")
add_library(CoolProp SHARED IMPORTED)
set_property(TARGET CoolProp PROPERTY IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/bin/libCoolProp.dll")
set_property(TARGET CoolProp PROPERTY IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/bin/libCoolProp.dll.a")
include_directories(${COOLPROP_LOCATION})

#######################################
# Other external libraries compiled 
# in source
#######################################

SET (MU_PARSER_FILES
third-party/mu-parser/muParser.cpp
third-party/mu-parser/muParserBase.cpp
third-party/mu-parser/muParserBytecode.cpp
third-party/mu-parser/muParserCallback.cpp
third-party/mu-parser/muParserDLL.cpp
third-party/mu-parser/muParserError.cpp
third-party/mu-parser/muParserInt.cpp
third-party/mu-parser/muParserTest.cpp
third-party/mu-parser/muParserTokenReader.cpp
)

#######################################
# SmoFlow
#######################################
add_library(SmoFlow SHARED
    util/CodeTiming.cpp
    util/CachedProperty.cpp
    util/Functors.cpp
    media/Medium.cpp
    media/MediumState.cpp
    media/MediumStateFluidCoolProp.cpp
    flow/FluidFlow.cpp    
    flow/FlowRComponent.cpp
    flow/TwoPortValve.cpp
    flow/MechanicalCompressor.cpp  
    volumes/FluidChamber.cpp
    ${MU_PARSER_FILES}
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
