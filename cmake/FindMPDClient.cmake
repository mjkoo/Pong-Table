# - Try to find libmpdclient
# Once done this will define
#  MPDCLIENT_FOUND - System has libmpdclient
#  MPDCLIENT_INCLUDE_DIRS - The libmpdclient include directories
#  MPDCLIENT_LIBRARIES - The libraries needed to use libmpdclient
#  MPDCLIENT_DEFINITIONS - Compiler switches required for using libmpdclient

find_package(PkgConfig)
pkg_check_modules(PC_MPDCLIENT QUIET libmpdclient)
set(MPDCLIENT_DEFINITIONS ${PC_MPDCLIENT_CFLAGS_OTHER})

find_path(MPDCLIENT_INCLUDE_DIR mpd/client.h
          HINTS ${PC_MPDCLIENT_INCLUDEDIR} ${PC_MPDCLIENT_INCLUDE_DIRS}
          PATH_SUFFIXES libmpdclient)

find_library(MPDCLIENT_LIBRARY NAMES mpdclient libmpdclient
             HINTS ${PC_MPDCLIENT_LIBDIR} ${PC_MPDCLIENT_LIBRARY_DIRS})

set(MPDCLIENT_LIBRARIES ${MPDCLIENT_LIBRARY})
set(MPDCLIENT_INCLUDE_DIRS ${MPDCLIENT_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBMPDCLIENT_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(libmpdclient DEFAULT_MSG
                                  MPDCLIENT_LIBRARY MPDCLIENT_INCLUDE_DIR)

mark_as_advanced(MPDCLIENT_INCLUDE_DIR MPDCLIENT_LIBRARY)
