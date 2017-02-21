cmake_minimum_required(VERSION 2.8.7)
project(test_playready C CXX)

if($ENV{ARCH} MATCHES "x86")
    MESSAGE(FATAL_ERROR "it's working on only ARM target")
    RETURN()
endif($ENV{ARCH} MATCHES "x86")

# ---
# add include files
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include)

# ---
# find required packages
include(FindPkgConfig)

pkg_check_modules(PLAYREADY REQUIRED playready-2.5-ree)
include_directories(${PLAYREADY_INCLUDE_DIRS})


MESSAGE( "CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR})

# ---
# create executable file

ADD_DEFINITIONS( -DDRM_BUILD_PROFILE=DRM_BUILD_PROFILE_OEMPLAYONLY )

set(BIN_NAME test_playready)

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)
set(SRC_LIST
    ${SOURCES}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/pkg_$ENV{ARCH}/")
add_executable(${BIN_NAME} ${SRC_LIST})
set_target_properties(${BIN_NAME} PROPERTIES LINKER_LANGUAGE C)

target_link_libraries (${BIN_NAME}
        ${PLAYREADY_LDFLAGS}
)

