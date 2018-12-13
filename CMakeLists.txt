cmake_minimum_required(VERSION 3.5)
project(libawesome_ecs VERSION 1.0.0 LANGUAGES CXX)

#Make sure that custom modules like FindRapidJSON are found
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

##############################################
# Create target and set properties

add_library(awesome_ecs
    src/entity.cpp
)

#Add an alias so that library can be used inside the build tree, e.g. when testing
add_library(AwesomeECS::awesome_ecs ALIAS awesome_ecs)

#Set target properties
target_include_directories(awesome_ecs
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(awesome_ecs PRIVATE cxx_auto_type)
target_compile_options(awesome_ecs PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

##############################################
# Installation instructions

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/AwesomeECS)

install(TARGETS awesome_ecs
    EXPORT awesome_ecs-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

#This is required so that the exported target has the name AwesomeECS and not awesome_ecs
set_target_properties(awesome_ecs PROPERTIES EXPORT_NAME AwesomeECS)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#Export the targets to a script
install(EXPORT awesome_ecs-targets
  FILE
    AwesomeECSTargets.cmake
  NAMESPACE
    AwesomeECS::
  DESTINATION
    ${INSTALL_CONFIGDIR}
)

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/AwesomeECSConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/AwesomeECSConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/AwesomeECSConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/cmake/FindRapidJSON.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/AwesomeECSConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/AwesomeECSConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

export(EXPORT awesome_ecs-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/AwesomeECSTargets.cmake NAMESPACE AwesomeECS::)

#Register package in user's package registry
export(PACKAGE AwesomeECS)

add_subdirectory(test)
