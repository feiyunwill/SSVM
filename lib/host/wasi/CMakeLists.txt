# SPDX-License-Identifier: Apache-2.0

add_library(ssvmHostModuleWasi
  wasienv.cpp
  wasifunc.cpp
  wasimodule.cpp
)

target_include_directories(ssvmHostModuleWasi
  PUBLIC
  ${Boost_INCLUDE_DIR}
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/thirdparty
)

target_link_libraries(ssvmHostModuleWasi
  PUBLIC
  Threads::Threads
)

if(NOT CMAKE_SYSTEM_NAME STREQUAL Darwin)
  target_link_libraries(ssvmHostModuleWasi
    PUBLIC
    rt
  )
endif()
