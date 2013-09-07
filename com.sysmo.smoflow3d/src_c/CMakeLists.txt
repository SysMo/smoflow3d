#######################################
# SmoFlowC Lib
#######################################
add_library(SmoFlowC SHARED
    util/SmoObject.c 
    util/Common.c 
    util/String.c 
    util/Arrays.c 
    util/Table.c 
    util/DynamicLoader.c
    controller/StateMachineController.c
)

install(TARGETS SmoFlowC
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin    
    ARCHIVE DESTINATION bin    
)

add_subdirectory(controller/CcH2DriveCycleController)
add_subdirectory(controller/CGH2DriveCycleController)
add_subdirectory(controller/LLNLDriveCycleController)