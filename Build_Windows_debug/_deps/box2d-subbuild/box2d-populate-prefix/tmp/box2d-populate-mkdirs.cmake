# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/lightyears_fix/Build_Windows_debug/_deps/box2d-src")
  file(MAKE_DIRECTORY "C:/lightyears_fix/Build_Windows_debug/_deps/box2d-src")
endif()
file(MAKE_DIRECTORY
  "C:/lightyears_fix/Build_Windows_debug/_deps/box2d-build"
  "C:/lightyears_fix/Build_Windows_debug/_deps/box2d-subbuild/box2d-populate-prefix"
  "C:/lightyears_fix/Build_Windows_debug/_deps/box2d-subbuild/box2d-populate-prefix/tmp"
  "C:/lightyears_fix/Build_Windows_debug/_deps/box2d-subbuild/box2d-populate-prefix/src/box2d-populate-stamp"
  "C:/lightyears_fix/Build_Windows_debug/_deps/box2d-subbuild/box2d-populate-prefix/src"
  "C:/lightyears_fix/Build_Windows_debug/_deps/box2d-subbuild/box2d-populate-prefix/src/box2d-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/lightyears_fix/Build_Windows_debug/_deps/box2d-subbuild/box2d-populate-prefix/src/box2d-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/lightyears_fix/Build_Windows_debug/_deps/box2d-subbuild/box2d-populate-prefix/src/box2d-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
