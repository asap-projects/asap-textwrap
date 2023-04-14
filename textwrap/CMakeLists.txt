# ===-----------------------------------------------------------------------===#
# Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
# copy at https://opensource.org/licenses/BSD-3-Clause).
# SPDX-License-Identifier: BSD-3-Clause
# ===-----------------------------------------------------------------------===#

set(my_name "textwrap")
asap_push_module("${my_name}")

# ------------------------------------------------------------------------------
# Meta information about the this module
# ------------------------------------------------------------------------------

asap_declare_module(
  MODULE_NAME
  "${my_name}"
  DESCRIPTION
  "Text wrapping and column layout utilities"
  GITHUB_REPO
  "https://github.com/asap-projects/textwrap"
  AUTHOR_MAINTAINER
  "Abdessattar Sassi"
  VERSION_MAJOR
  "1"
  VERSION_MINOR
  "0"
  VERSION_PATCH
  "2")

# ==============================================================================
# Build instructions
# ==============================================================================

# ------------------------------------------------------------------------------
# Main module target
# ------------------------------------------------------------------------------

set(MODULE_TARGET_NAME "asap_textwrap")

asap_add_library(
  ${MODULE_TARGET_NAME}
  STATIC
  SHARED
  WARNING
  SOURCES
  # Headers
  "include/textwrap/textwrap.h"
  # Sources
  "src/tokenizer.h"
  "src/tokenizer.cpp"
  "src/textwrap.cpp")

target_link_libraries(${MODULE_TARGET_NAME}
                      PRIVATE asap::common magic_enum::magic_enum asap::fsm)

target_include_directories(
  ${MODULE_TARGET_NAME}
  PUBLIC $<INSTALL_INTERFACE:include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(${MODULE_TARGET_NAME} PUBLIC cxx_std_17)

# common comes directly from asap and is usually kept as is. It is more
# convenient to simply use it as asap::common
add_library(asap::${META_MODULE_NAME} ALIAS ${MODULE_TARGET_NAME})

# Generate module config files for cmake and pkgconfig
asap_create_module_config_files()

# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------

if(ASAP_BUILD_TESTS)
  # Add support for (optional) code quality tools
  asap_add_sanitizers(${MODULE_TARGET_NAME})
  add_subdirectory(test)
endif()

# ------------------------------------------------------------------------------
# Examples
# ------------------------------------------------------------------------------
if(ASAP_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

# ------------------------------------------------------------------------------
# API Documentation
# ------------------------------------------------------------------------------

asap_with_doxygen(
  MODULE_NAME
  ${MODULE_TARGET_NAME}
  VERSION
  ${META_MODULE_VERSION}
  TITLE
  "\"Text Wrapping and Layout Module\""
  BRIEF
  "\"Provides utilities to wrap text and create column layouts.\""
  INPUT_PATH
  "${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/include")

asap_with_sphinx(${MODULE_TARGET_NAME})

# ==============================================================================
# Deployment instructions
# ==============================================================================

if(${META_PROJECT_ID}_INSTALL)
  set(TARGETS_EXPORT_NAME "${MODULE_TARGET_NAME}Targets")
  set(runtime "${MODULE_TARGET_NAME}_runtime")
  set(dev "${MODULE_TARGET_NAME}_dev")

  # Library
  install(
    TARGETS ${MODULE_TARGET_NAME}
    EXPORT "${TARGETS_EXPORT_NAME}"
    COMPONENT dev
    RUNTIME DESTINATION ${ASAP_INSTALL_BIN} COMPONENT ${runtime}
    LIBRARY DESTINATION ${ASAP_INSTALL_SHARED} COMPONENT ${runtime}
    ARCHIVE DESTINATION ${ASAP_INSTALL_LIB} COMPONENT ${dev})

  # Header files
  install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${META_MODULE_NAME}
    DESTINATION ${ASAP_INSTALL_INCLUDE}
    COMPONENT ${dev}
    FILES_MATCHING
    PATTERN "*.h")

  # Generated header files
  install(
    DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/${META_MODULE_NAME}
    DESTINATION ${ASAP_INSTALL_INCLUDE}
    COMPONENT ${dev})

  # Target config
  install(
    EXPORT ${TARGETS_EXPORT_NAME}
    NAMESPACE ${META_PROJECT_NAME}::
    DESTINATION ${ASAP_INSTALL_CMAKE}/${META_MODULE_NAME}
    COMPONENT ${dev})

  # Package configuration files
  install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${MODULE_TARGET_NAME}Config.cmake
          ${CMAKE_CURRENT_BINARY_DIR}/${MODULE_TARGET_NAME}ConfigVersion.cmake
    DESTINATION ${ASAP_INSTALL_CMAKE}/${META_MODULE_NAME})

  # Docs
  if(EXISTS ${SPHINX_BUILD_DIR}/${MODULE_TARGET_NAME})
    install(
      DIRECTORY ${SPHINX_BUILD_DIR}/${MODULE_TARGET_NAME}
      DESTINATION ${ASAP_INSTALL_DOC}
      COMPONENT ${MODULE_TARGET_NAME}_docs)
  endif()
endif()

asap_pop_module("${my_name}")
