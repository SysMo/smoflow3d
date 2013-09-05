cmake_minimum_required(VERSION 2.6)
enable_testing()


project(com.sysmo.smoflow3d)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}")
#message("Boost root: $ENV{BOOST_ROOT}")

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
    if(WIN32)
        message("Configured for Windows")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gstabs")
        set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -DWINDOWS -DWIN32")
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DWINDOWS -DWIN32 -std=c99")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--enable-auto-import")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")
    elseif(UNIX)
        message("Configured for Linux, Windows: ${WINDOWS}")
        set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -DLINUX -fPIC")
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall") # -m32 for 32 bit compilation
endif()

##########################################
# User functions
##########################################
function (add_smo_test TEST_NAME TEST_SOURCES)
    add_executable(${TEST_NAME} ${TEST_SOURCES})
    target_link_libraries(${TEST_NAME} SmoFlow CoolProp ${CMAKE_DL_LIBS})
    install(
    TARGETS ${TEST_NAME}
    RUNTIME DESTINATION bin/tests
    LIBRARY DESTINATION bin/tests
    )
endfunction()



include_directories(src)
include_directories(src/third-party/eigen)
add_subdirectory(src)

include_directories(src_c)
add_subdirectory(src_c)
