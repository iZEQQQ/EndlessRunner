

set(SDL2_PATH "" CACHE STRING "Custom SDL2 Library path")

set(_SDL2_NO_DEFAULT_PATH OFF)
if(SDL2_PATH)
  set(_SDL2_NO_DEFAULT_PATH ON)
endif()

set(SDL2_NO_DEFAULT_PATH ${_SDL2_NO_DEFAULT_PATH}
    CACHE BOOL "Disable search SDL2 Library in default path")
unset(_SDL2_NO_DEFAULT_PATH)

set(SDL2_NO_DEFAULT_PATH_CMD)
if(SDL2_NO_DEFAULT_PATH)
  set(SDL2_NO_DEFAULT_PATH_CMD NO_DEFAULT_PATH)
endif()


find_path(SDL2_INCLUDE_DIR SDL.h
  HINTS
    ENV SDL2DIR
    ${SDL2_NO_DEFAULT_PATH_CMD}
  PATH_SUFFIXES SDL2

                include/SDL2 include
  PATHS ${SDL2_PATH}
  DOC "Where the SDL2 headers can be found"
)

set(SDL2_INCLUDE_DIRS "${SDL2_INCLUDE_DIR}")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(VC_LIB_PATH_SUFFIX lib/x64)
else()
  set(VC_LIB_PATH_SUFFIX lib/x86)
endif()


find_library(SDL2_LIBRARY
  NAMES SDL2 SDL-2.0
  HINTS
    ENV SDL2DIR
    ${SDL2_NO_DEFAULT_PATH_CMD}
  PATH_SUFFIXES lib ${VC_LIB_PATH_SUFFIX}
  PATHS ${SDL2_PATH}
  DOC "Where the SDL2 Library can be found"
)

set(SDL2_LIBRARIES "${SDL2_LIBRARY}")

if(NOT SDL2_BUILDING_LIBRARY)
  if(NOT SDL2_INCLUDE_DIR MATCHES ".framework")


    if(SDL2_PATH)
      set(SDL2MAIN_LIBRARY_PATHS "${SDL2_PATH}")
    endif()

    if(NOT SDL2_NO_DEFAULT_PATH)
      set(SDL2MAIN_LIBRARY_PATHS
            /sw
            /opt/local
            /opt/csw
            /opt
            "${SDL2MAIN_LIBRARY_PATHS}"
      )
    endif()

    find_library(SDL2MAIN_LIBRARY
      NAMES SDL2main
      HINTS
        ENV SDL2DIR
        ${SDL2_NO_DEFAULT_PATH_CMD}
      PATH_SUFFIXES lib ${VC_LIB_PATH_SUFFIX}
      PATHS ${SDL2MAIN_LIBRARY_PATHS}
      DOC "Where the SDL2main library can be found"
    )
    unset(SDL2MAIN_LIBRARY_PATHS)
  endif()
endif()


if(NOT APPLE)
  find_package(Threads QUIET)
  if(NOT Threads_FOUND)
    set(SDL2_THREADS_NOT_FOUND "Could NOT find Threads (Threads is required by SDL2).")
    if(SDL2_FIND_REQUIRED)
      message(FATAL_ERROR ${SDL2_THREADS_NOT_FOUND})
    else()
        if(NOT SDL2_FIND_QUIETLY)
          message(STATUS ${SDL2_THREADS_NOT_FOUND})
        endif()
      return()
    endif()
    unset(SDL2_THREADS_NOT_FOUND)
  endif()
endif()


if(MINGW)
  set(MINGW32_LIBRARY mingw32 "-mwindows" CACHE STRING "link flags for MinGW")
endif()

if(SDL2_LIBRARY)
  # For SDL2main
  if(SDL2MAIN_LIBRARY AND NOT SDL2_BUILDING_LIBRARY)
    list(FIND SDL2_LIBRARIES "${SDL2MAIN_LIBRARY}" _SDL2_MAIN_INDEX)
    if(_SDL2_MAIN_INDEX EQUAL -1)
      set(SDL2_LIBRARIES "${SDL2MAIN_LIBRARY}" ${SDL2_LIBRARIES})
    endif()
    unset(_SDL2_MAIN_INDEX)
  endif()


  if(APPLE)
    set(SDL2_LIBRARIES ${SDL2_LIBRARIES} -framework Cocoa)
  endif()

  if(NOT APPLE)
    set(SDL2_LIBRARIES ${SDL2_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
  endif()


  if(MINGW)
    set(SDL2_LIBRARIES ${MINGW32_LIBRARY} ${SDL2_LIBRARIES})
  endif()

endif()


if(SDL2_INCLUDE_DIR AND EXISTS "${SDL2_INCLUDE_DIR}/SDL_version.h")
  file(STRINGS "${SDL2_INCLUDE_DIR}/SDL_version.h" SDL2_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SDL_MAJOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL2_INCLUDE_DIR}/SDL_version.h" SDL2_VERSION_MINOR_LINE REGEX "^#define[ \t]+SDL_MINOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL2_INCLUDE_DIR}/SDL_version.h" SDL2_VERSION_PATCH_LINE REGEX "^#define[ \t]+SDL_PATCHLEVEL[ \t]+[0-9]+$")
  string(REGEX REPLACE "^#define[ \t]+SDL_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_VERSION_MAJOR "${SDL2_VERSION_MAJOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_VERSION_MINOR "${SDL2_VERSION_MINOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" SDL2_VERSION_PATCH "${SDL2_VERSION_PATCH_LINE}")
  set(SDL2_VERSION_STRING ${SDL2_VERSION_MAJOR}.${SDL2_VERSION_MINOR}.${SDL2_VERSION_PATCH})
  unset(SDL2_VERSION_MAJOR_LINE)
  unset(SDL2_VERSION_MINOR_LINE)
  unset(SDL2_VERSION_PATCH_LINE)
  unset(SDL2_VERSION_MAJOR)
  unset(SDL2_VERSION_MINOR)
  unset(SDL2_VERSION_PATCH)
endif()

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2
                                  REQUIRED_VARS SDL2_LIBRARY SDL2_INCLUDE_DIR
                                  VERSION_VAR SDL2_VERSION_STRING)

if(SDL2MAIN_LIBRARY)
  FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2main
                                    REQUIRED_VARS SDL2MAIN_LIBRARY SDL2_INCLUDE_DIR
                                    VERSION_VAR SDL2_VERSION_STRING)
endif()


mark_as_advanced(SDL2_PATH
                 SDL2_NO_DEFAULT_PATH
                 SDL2_LIBRARY
                 SDL2MAIN_LIBRARY
                 SDL2_INCLUDE_DIR
                 SDL2_BUILDING_LIBRARY)



if(SDL2_FOUND)

  # SDL2::Core target
  if(SDL2_LIBRARY AND NOT TARGET SDL2::Core)
    add_library(SDL2::Core UNKNOWN IMPORTED)
    set_target_properties(SDL2::Core PROPERTIES
                          IMPORTED_LOCATION "${SDL2_LIBRARY}"
                          INTERFACE_INCLUDE_DIRECTORIES "${SDL2_INCLUDE_DIR}")

    if(APPLE)

      set_property(TARGET SDL2::Core APPEND PROPERTY
                   INTERFACE_LINK_OPTIONS -framework Cocoa)
    else()

      set_property(TARGET SDL2::Core APPEND PROPERTY
                   INTERFACE_LINK_LIBRARIES Threads::Threads)
    endif()
  endif()


  if(NOT SDL2_BUILDING_LIBRARY AND NOT TARGET SDL2::Main)

    if(SDL2_INCLUDE_DIR MATCHES ".framework" OR NOT SDL2MAIN_LIBRARY)
      add_library(SDL2::Main INTERFACE IMPORTED)
      set_property(TARGET SDL2::Main PROPERTY
                   INTERFACE_LINK_LIBRARIES SDL2::Core)
    elseif(SDL2MAIN_LIBRARY)

      add_library(SDL2::MainInternal UNKNOWN IMPORTED)
      set_property(TARGET SDL2::MainInternal PROPERTY
                   IMPORTED_LOCATION "${SDL2MAIN_LIBRARY}")
      set_property(TARGET SDL2::MainInternal PROPERTY
                   INTERFACE_LINK_LIBRARIES SDL2::Core)

      add_library(SDL2::Main INTERFACE IMPORTED)

      if(MINGW)

        set_property(TARGET SDL2::Main PROPERTY
                     INTERFACE_LINK_LIBRARIES "mingw32" "-mwindows")
      endif()

      set_property(TARGET SDL2::Main APPEND PROPERTY
                   INTERFACE_LINK_LIBRARIES SDL2::MainInternal)
    endif()

  endif()
endif()
