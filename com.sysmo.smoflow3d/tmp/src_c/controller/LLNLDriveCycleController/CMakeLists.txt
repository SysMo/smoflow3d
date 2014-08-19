#######################################
# DriveCycleController Lib
#######################################
SET(CMAKE_SHARED_LIBRARY_PREFIX "")

add_library(LLNLDriveCycleController SHARED
    LLNLDriveCycleController.c
)

install(TARGETS LLNLDriveCycleController
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin    
    ARCHIVE DESTINATION bin    
)
