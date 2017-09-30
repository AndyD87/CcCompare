# @Author Andreas Dirmeier
# @brief Main CMakeList.txt for CcDirectoryExport
#############
cmake_minimum_required (VERSION 2.8)

################################################################################
# Setup Globals
################################################################################
include( ${CMAKE_CURRENT_SOURCE_DIR}/VERSION.cmake )
include( ${CMAKE_CURRENT_SOURCE_DIR}/CMakeConfig/CcMacros.cmake )
include( ${CMAKE_CURRENT_SOURCE_DIR}/CMakeConfig/CcDirectoryExportMacros.cmake )

if(WINDOWS)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/CcDirectoryExport")
endif()

################################################################################
# Configuration is done, setup Project
################################################################################
project("CcDirectoryExport")

#add_definitions(-DMEMORYMONITOR_ENABLED)

################################################################################
# Setup Debug
################################################################################
if(CMAKE_BUILD_TYPE MATCHES "[Dd][Ee][Bb][Uu][Gg]")
  message("Build-Type set to ${CMAKE_BUILD_TYPE}")
  set(CCDIRECTORYEXPORT_BUILD_TYPE "DEBUG" )
  set(CMAKE_VERBOSE_MAKEFILE          ON)
else()
  message("Build-Type set to release")
  set(CCDIRECTORYEXPORT_BUILD_TYPE "RELEASE" )
endif()

################################################################################
# Setup Output Paths
################################################################################
# To be able to overwrite global output root use -DCCDIRECTORYEXPORT_OUTPUT_DIR=/path on configuration
if(NOT CCDIRECTORYEXPORT_OUTPUT_DIR)
  set(CCDIRECTORYEXPORT_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Output")
endif()

# Set runtime output dir to root/output if no other location was defined
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CCDIRECTORYEXPORT_OUTPUT_DIR}/bin")
endif()

# Set library output dir to root/output if no other location was defined
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CCDIRECTORYEXPORT_OUTPUT_DIR}/lib")
endif()

# Set archive output dir to root/output if no other location was defined
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CCDIRECTORYEXPORT_OUTPUT_DIR}/lib/static")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

CcNoConfigurationDirs()

################################################################################
# Import CcOS
################################################################################
include(CcOSImport.cmake)

ADD_SUBDIRECTORY(CcDirectoryExport)
