#######################################
# DriveCycleController Lib
#######################################
SET(CMAKE_C_FLAGS "-std=c99")
SET(CMAKE_SHARED_LIBRARY_PREFIX "")

add_library(DriveCycleController SHARED
    DriveCycleController.c
)

install(TARGETS DriveCycleController
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin    
    ARCHIVE DESTINATION bin    
)
