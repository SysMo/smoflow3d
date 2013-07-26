cmake_minimum_required(VERSION 2.6)
enable_testing()


project(com.sysmo.smoflow3d)

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}")
#message("Boost root: $ENV{BOOST_ROOT}")

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
    if(WIN32)
        message("Configured for Windows")
        set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -DWINDOWS -DWIN32")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--enable-auto-import")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")
    elseif(UNIX)
        message("Configured for Linux")
        set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -DLINUX -fPIC")
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall") # -m32 for 32 bit compilation
endif()

include_directories(src)
add_subdirectory(src)
    
