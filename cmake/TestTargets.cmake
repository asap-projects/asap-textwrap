# ===-----------------------------------------------------------------------===#
# Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
# copy at https://opensource.org/licenses/BSD-3-Clause).
# SPDX-License-Identifier: BSD-3-Clause
# ===-----------------------------------------------------------------------===#

include(common/TestTargets)

macro(asap_add_test target)
  swift_add_test("${target}" ${ARGN})
  # Set some common private compiler defines
  asap_set_compile_definitions(${target})
  # Set some common compiler options
  asap_set_compile_options(${target})
  if(TARGET gtest AND BUILD_SHARED_LIBS)
    target_compile_definitions(${target} PRIVATE GTEST_LINKED_AS_SHARED_LIBRARY)
    if(MSVC)
      target_compile_options(${target} PRIVATE /wd4251)
    endif()
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
      asap_set_compile_options(
        ${target} ADD "-Wno-used-but-marked-unused" "-Wno-global-constructors"
        "-Wno-unused-member-function")
    endif()
  endif()
  set_target_properties(${target} PROPERTIES FOLDER "Unit Tests")
endmacro()

macro(asap_add_test_runner target)
  swift_add_test_runner("${target}" ${ARGN})
endmacro()

function(asap_add_test_library target)
  swift_add_test_library("${target}" ${ARGN})
  # Set some common private compiler defines
  asap_set_compile_definitions(${target})
  # Set some common compiler options
  asap_set_compile_options(${target})
  set_target_properties(
    ${target}
    PROPERTIES FOLDER "Test Libraries"
               VERSION ${META_MODULE_VERSION}
               SOVERSION ${META_MODULE_VERSION_MAJOR}
               DEBUG_POSTFIX "d")
endfunction()
