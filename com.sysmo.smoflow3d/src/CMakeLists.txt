#######################################
# CoolProp Import
#######################################
set(COOLPROP_LOCATION ${CMAKE_SOURCE_DIR}/../../coolprop)
message("Coolprop location: ${COOLPROP_LOCATION}")
add_library(CoolProp STATIC IMPORTED)
set_property(TARGET CoolProp PROPERTY IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/bin/libCoolProp.a")
#set_property(TARGET CoolProp PROPERTY IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/bin/libCoolProp.dll.a")
include_directories(${COOLPROP_LOCATION})

#######################################
# Other external libraries compiled 
# in source
#######################################

set(MU_PARSER_FILES
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

set(SMO_FILE_RADER
	file_reader/containers/DataTable.cpp
	file_reader/containers/HeadingDataTable.cpp
	file_reader/containers/TimeDataTable.cpp
	file_reader/FileReader.cpp
)

#######################################
# SmoFlow
#######################################
add_library(SmoFlow SHARED
    util/CodeTiming.cpp
    util/CachedProperty.cpp
    util/SmoComponent.cpp
    util/SimulationEnvironment.cpp
    util/DynamicLoader.cpp
    util/String.cpp
    math/Functors.cpp
    math/Interpolators.cpp
    io_control/CSVProcessor.cpp
    io_control/DriveCycleReader.cpp
    io_control/StateMachineController.cpp
    media/Medium.cpp
    media/SolidRegistryClass.cpp
    media/MediumState.cpp
    media/MediumStateFluidCoolProp.cpp
    media/MediumStateSolid.cpp
    media/definitions/SolidDefinitions.cpp
    flow/FlowBase.cpp    
    flow/Valve.cpp
    flow/MechanicalCompressor.cpp
    flow/CryopumpHeatExch.cpp
    flow/ThermalConduction2Node.cpp
    flow/ThermalConductionElement.cpp
    flow/Convection.cpp
    flow/FreeConvection.cpp
    flow/ForcedConvection.cpp
    flow/FrictionFlowPipe.cpp
    flow/FrictionFlowValve.cpp
    flow/PhaseSeparator.cpp
    flow/Radiation.cpp
    flow/RadiationWallFluid.cpp
    flow/RadiationTwoSurfaces.cpp
    flow_R/Component_R.cpp
    flow_R/FlowComponent_R.cpp
    flow_R/Pipe_R.cpp
    flow_R/PipeHeatExchanger_R.cpp
    flow_R/Valve_R.cpp
    flow_R/Adaptor_R.cpp
    flow_R/ManagerComponents_R.cpp
    volumes/FluidChamber.cpp
    volumes/ThermalNode.cpp
    volumes/PipeHeatExchNoPrDropMassAcc_C.cpp
    volumes/PipeHeatExchPrDropMassAcc_RC.cpp
    volumes/PipeHeatExchPrDropMassAcc_RCR.cpp
    volumes/HeatExchNoPrDropNoMassAcc_RC.cpp
    volumes/HeatExchNoPrDropNoMassAcc_CR.cpp
    volumes/TPipeJunction.cpp
    ${MU_PARSER_FILES}
    ${SMO_FILE_RADER}
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
#add_smo_test(CoolPropTest "test/CoolProp.cpp;")
#add_smo_test(MediaHydrogenTest "test/MediaHydrogen.cpp;")
#add_smo_test(FunctorsTest "test/Functors.cpp;")
#add_smo_test(MediumSolidTest "test/MediumSolid.cpp;")
#add_smo_test(IOControlTest "test/IOControl.cpp;")
