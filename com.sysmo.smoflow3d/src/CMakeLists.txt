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
    util/SmoComponent.cpp
    math/Functors.cpp
    math/Interpolators.cpp
    media/Medium.cpp
    media/SolidRegistryClass.cpp
    media/MediumState.cpp
    media/MediumStateFluidCoolProp.cpp
    media/MediumStateSolid.cpp
    media/definitions/SolidDefinitions.cpp
    flow/FlowBase.cpp    
    flow/FlowRComponent.cpp
    flow/TwoPortValve.cpp
    flow/Orifice.cpp
    flow/MechanicalCompressor.cpp
    flow/ThermalConductionElement.cpp
    flow/Convection.cpp
    flow/FreeConvection.cpp
    flow/ForcedConvection.cpp
    volumes/FluidChamber.cpp
    volumes/ThermalNode.cpp
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
add_smo_test(MediaHydrogenTest "test/MediaHydrogen.cpp;")
add_smo_test(FunctorsTest "test/Functors.cpp;")
add_smo_test(MediumSolidTest "test/MediumSolid.cpp;")
