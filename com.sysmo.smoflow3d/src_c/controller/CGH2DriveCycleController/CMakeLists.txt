#######################################
# DriveCycleController Lib
#######################################
SET(CMAKE_SHARED_LIBRARY_PREFIX "")

add_library(CGH2DriveCycleController SHARED
    CGH2DriveCycleController.c
)

install(TARGETS CGH2DriveCycleController
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin    
    ARCHIVE DESTINATION bin    
)
