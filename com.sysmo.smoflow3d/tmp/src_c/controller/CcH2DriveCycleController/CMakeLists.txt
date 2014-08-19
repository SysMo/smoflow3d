#######################################
# DriveCycleController Lib
#######################################
SET(CMAKE_SHARED_LIBRARY_PREFIX "")

add_library(CcH2DriveCycleController SHARED
    CcH2DriveCycleController.c
)

install(TARGETS CcH2DriveCycleController
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin    
    ARCHIVE DESTINATION bin    
)
