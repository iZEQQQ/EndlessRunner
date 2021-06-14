
find_package(SDL2 QUIET)
if(NOT SDL2_FOUND)
  set(SDL2_GFX_SDL2_NOT_FOUND "Could NOT find SDL2 (SDL2 is required by SDL2_gfx).")
  if(SDL2_gfx_FIND_REQUIRED)
    message(FATAL_ERROR ${SDL2_GFX_SDL2_NOT_FOUND})
  else()
      if(NOT SDL2_gfx_FIND_QUIETLY)
        message(STATUS ${SDL2_GFX_SDL2_NOT_FOUND})
      endif()
    return()
  endif()
  unset(SDL2_GFX_SDL2_NOT_FOUND)
endif()




set(SDL2_GFX_PATH "" CACHE STRING "Custom SDL2_gfx Library path")

set(_SDL2_GFX_NO_DEFAULT_PATH OFF)
if(SDL2_GFX_PATH)
  set(_SDL2_GFX_NO_DEFAULT_PATH ON)
endif()

set(SDL2_GFX_NO_DEFAULT_PATH ${_SDL2_GFX_NO_DEFAULT_PATH}
    CACHE BOOL "Disable search SDL2_gfx Library in default path")
unset(_SDL2_GFX_NO_DEFAULT_PATH)

set(SDL2_GFX_NO_DEFAULT_PATH_CMD)
if(SDL2_GFX_NO_DEFAULT_PATH)
  set(SDL2_GFX_NO_DEFAULT_PATH_CMD NO_DEFAULT_PATH)
endif()

# Search for the SDL2_gfx include directory
find_path(SDL2_GFX_INCLUDE_DIR SDL2_gfxPrimitives.h
  HINTS
    ENV SDL2GFXDIR
    ENV SDL2DIR
    ${SDL2_GFX_NO_DEFAULT_PATH_CMD}
  PATH_SUFFIXES SDL2
                # path suffixes to search inside ENV{SDL2DIR}
                # and ENV{SDL2GFXDIR}
                include/SDL2 include
  PATHS ${SDL2_GFX_PATH}
  DOC "Where the SDL2_gfx headers can be found"
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(VC_LIB_PATH_SUFFIX lib/x64)
else()
  set(VC_LIB_PATH_SUFFIX lib/x86)
endif()

# Search for the SDL2_gfx library
find_library(SDL2_GFX_LIBRARY
  NAMES SDL2_gfx
  HINTS
    ENV SDL2GFXDIR
    ENV SDL2DIR
    ${SDL2_GFX_NO_DEFAULT_PATH_CMD}
  PATH_SUFFIXES lib ${VC_LIB_PATH_SUFFIX}
  PATHS ${SDL2_GFX_PATH}
  DOC "Where the SDL2_gfx Library can be found"
)

# Read SDL2_gfx version
if(SDL2_GFX_INCLUDE_DIR AND EXISTS "${SDL2_GFX_INCLUDE_DIR}/SDL2_gfxPrimitives.h")
  file(STRINGS "${SDL2_GFX_INCLUDE_DIR}/SDL2_gfxPrimitives.h" SDL2_GFX_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SDL2_GFXPRIMITIVES_MAJOR[ \t]+[0-9]+$")
  file(STRINGS "${SDL2_GFX_INCLUDE_DIR}/SDL2_gfxPrimitives.h" SDL2_GFX_VERSION_MINOR_LINE REGEX "^#define[ \t]+SDL2_GFXPRIMITIVES_MINOR[ \t]+[0-9]+$")
  file(STRINGS "${SDL2_GFX_INCLUDE_DIR}/SDL2_gfxPrimitives.h" SDL2_GFX_VERSION_PATCH_LINE REGEX "^#define[ \t]+SDL2_GFXPRIMITIVES_MICRO[ \t]+[0-9]+$")
  string(REGEX REPLACE "^#define[ \t]+SDL2_GFXPRIMITIVES_MAJOR[ \t]+([0-9]+)$" "\\1" SDL2_GFX_VERSION_MAJOR "${SDL2_GFX_VERSION_MAJOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL2_GFXPRIMITIVES_MINOR[ \t]+([0-9]+)$" "\\1" SDL2_GFX_VERSION_MINOR "${SDL2_GFX_VERSION_MINOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL2_GFXPRIMITIVES_MICRO[ \t]+([0-9]+)$" "\\1" SDL2_GFX_VERSION_PATCH "${SDL2_GFX_VERSION_PATCH_LINE}")
  set(SDL2_GFX_VERSION_STRING ${SDL2_GFX_VERSION_MAJOR}.${SDL2_GFX_VERSION_MINOR}.${SDL2_GFX_VERSION_PATCH})
  unset(SDL2_GFX_VERSION_MAJOR_LINE)
  unset(SDL2_GFX_VERSION_MINOR_LINE)
  unset(SDL2_GFX_VERSION_PATCH_LINE)
  unset(SDL2_GFX_VERSION_MAJOR)
  unset(SDL2_GFX_VERSION_MINOR)
  unset(SDL2_GFX_VERSION_PATCH)
endif()

set(SDL2_GFX_LIBRARIES ${SDL2_GFX_LIBRARY})
set(SDL2_GFX_INCLUDE_DIRS ${SDL2_GFX_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2_gfx
                                  REQUIRED_VARS SDL2_GFX_LIBRARIES SDL2_GFX_INCLUDE_DIRS
                                  VERSION_VAR SDL2_GFX_VERSION_STRING)


mark_as_advanced(SDL2_GFX_PATH
                 SDL2_GFX_NO_DEFAULT_PATH
                 SDL2_GFX_LIBRARY
                 SDL2_GFX_INCLUDE_DIR)


if(SDL2_GFX_FOUND)

  # SDL2::GFX target
  if(SDL2_GFX_LIBRARY AND NOT TARGET SDL2::GFX)
    add_library(SDL2::GFX UNKNOWN IMPORTED)
    set_target_properties(SDL2::GFX PROPERTIES
                          IMPORTED_LOCATION "${SDL2_GFX_LIBRARY}"
                          INTERFACE_INCLUDE_DIRECTORIES "${SDL2_GFX_INCLUDE_DIR}"
                          INTERFACE_LINK_LIBRARIES SDL2::Core)
  endif()
endif()
