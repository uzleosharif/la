


cmake_minimum_required(VERSION 3.31)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
set(CMAKE_CXX_FLAGS "-stdlib=libc++")

project(la CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_MODULE_STD ON)

add_library(la SHARED)
target_compile_features(la PRIVATE cxx_std_26)
target_sources(la PUBLIC
  FILE_SET modules
    TYPE CXX_MODULES
    FILES la.cppm
)

install(TARGETS la
  EXPORT laTargets
  FILE_SET modules
    DESTINATION lib/la/miu
  LIBRARY
    DESTINATION lib
  ARCHIVE
    DESTINATION lib/static
  CXX_MODULES_BMI
    DESTINATION lib/la/bmi
)
install(EXPORT laTargets
  FILE laTargets.cmake
  NAMESPACE uzleo::
  DESTINATION lib/cmake/la
  CXX_MODULES_DIRECTORY modules
)
install(FILES cmake/laConfig.cmake
  DESTINATION lib/cmake/la
)

