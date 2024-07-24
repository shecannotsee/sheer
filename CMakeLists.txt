########################################################################################################################
# project init                                                                                                         #
########################################################################################################################
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
set(project_name "sheer")
PROJECT(${project_name} VERSION 0.0.1 LANGUAGES CXX)

if (NOT DEFINED project_type)
    # project_type: [library] or [application]
    set(project_type "library")
endif ()

########################################################################################################################
# external settings                                                                                                    #
########################################################################################################################
if (NOT DEFINED CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX "/")
endif ()
option(build_release "build release" OFF)
option(build_tests "build with test target" ON)
option(build_shared_libs "enable shared libs" ON)

########################################################################################################################
# compilation options                                                                                                  #
########################################################################################################################
# set cpp standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall")
if (build_release STREQUAL ON)
    set(CMAKE_BUILD_TYPE "Release")
    set(CMAKE_CXX_FLAGS "-O2")
else ()
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        # do nothing
    else ()
        set(CMAKE_BUILD_TYPE "Debug")
        set(CMAKE_CXX_FLAGS "-g") # debug symbol
        set(CMAKE_CXX_FLAGS "-O0")
    endif ()
endif ()

########################################################################################################################
# common targets name settings                                                                                         #
########################################################################################################################
# src target
set(library_static_name "${project_name}_static")
if (build_shared_libs STREQUAL ON)
    set(library_dynamic_name "${project_name}_dynamic")
endif ()

# project_type set
if (project_type STREQUAL "library")
    # do nothing
elseif (project_type STREQUAL "application")
    set(application_name "application")
else ()
    message(FATAL_ERROR "Unknown project type:${project_type}")
endif ()

# set test
if (build_tests STREQUAL ON)
    set(test_name "${project_name}_test")
else ()
    message(STATUS "Not building test cases")
endif ()

########################################################################################################################
# import lib                                                                                                           #
########################################################################################################################
# import she_test
set(SHE_TEST_ROOT_DIR "/usr/local" CACHE STRING "default path")
set(_she_test_path ${SHE_TEST_ROOT_DIR})
set(she_test_include_dir "${_she_test_path}/include")
set(she_test_lib_dir)
set(she_test_link_libs)
########################################################################################################################

# include
include_directories(${she_test_include_dir})

# lib
link_directories()

# internal project
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/test)

# link dependency
set(src_link_dependency "-pthread")
set(test_link_dependency ${src_link_dependency})
set(application_link_dependency ${src_link_dependency})

########################################################################################################################
# src build                                                                                                            #
########################################################################################################################
file(GLOB_RECURSE src "${CMAKE_SOURCE_DIR}/src/*")
# Exclude specific files
# list(REMOVE_ITEM src "${CMAKE_SOURCE_DIR}/src/add.cpp")

add_library(${library_static_name} STATIC ${src})
# Rename the generated static library
set_target_properties(${library_static_name} PROPERTIES OUTPUT_NAME ${project_name})
target_link_libraries(${library_static_name} PRIVATE ${src_link_dependency})

if (build_shared_libs STREQUAL ON)
    add_library(${library_dynamic_name} SHARED ${src})
    # Rename the generated dynamic library
    set_target_properties(${library_dynamic_name} PROPERTIES OUTPUT_NAME ${project_name})
    target_link_libraries(${library_dynamic_name} PRIVATE ${src_link_dependency})
endif ()

########################################################################################################################
# test target build                                                                                                    #
########################################################################################################################
if (build_tests STREQUAL ON)
    file(GLOB_RECURSE test_src "${CMAKE_SOURCE_DIR}/test/*")
    add_executable(${test_name} ${src} ${test_src})
    target_link_libraries(${test_name} ${test_link_dependency})
endif ()

########################################################################################################################
# application target build                                                                                             #
########################################################################################################################
if (project_type STREQUAL "application")
    file(GLOB_RECURSE application_src "${CMAKE_SOURCE_DIR}/application/*")
    add_executable(${application_name} ${src} ${application_src})
    target_link_libraries(${application_name} ${application_link_dependency})
endif ()


########################################################################################################################
# Install module                                                                                                       #
########################################################################################################################
# test install
if (build_tests STREQUAL ON)
    install(TARGETS
            ${test_name}
            DESTINATION
            ${project_name}/bin # install path
    )
endif ()

# application install
if (project_type STREQUAL "application")
    install(TARGETS
            ${application_name}
            DESTINATION
            ${project_name}/bin
    )
endif ()

# include install
install(FILES
        ${CMAKE_SOURCE_DIR}/src/sheer.h # source file
        ${CMAKE_SOURCE_DIR}/src/timed_cache_queue.h
        DESTINATION # to
        ${project_name}/include # install path
)
# lib install
install(TARGETS
        ${library_static_name}
        DESTINATION
        ${project_name}/lib
)
# shared libs install
if (build_shared_libs STREQUAL ON)
    install(TARGETS
            ${library_dynamic_name}
            DESTINATION
            ${project_name}/lib
    )
endif ()

# cmake install
#install(FILES
#        ${CMAKE_SOURCE_DIR}/cmake/${project_name}-config.cmake
#        DESTINATION
#        ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/cmake
#)