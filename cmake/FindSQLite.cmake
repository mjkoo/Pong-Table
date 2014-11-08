# - Try to find libsqlite
# Once done this will define
#  SQLITE_FOUND - System has libsqlite
#  SQLITE_INCLUDE_DIRS - The libsqlite include directories
#  SQLITE_RARIES - The libraries needed to use libsqlite
#  SQLITE_DEFINITIONS - Compiler switches required for using libsqlite

find_package(PkgConfig)
pkg_check_modules(PC_SQLITE QUIET sqlite)
set(SQLITE_DEFINITIONS ${PC_SQLITE_CFLAGS_OTHER})

find_path(SQLITE_INCLUDE_DIR sqlite.h
          HINTS ${PC_SQLITE_INCLUDEDIR} ${PC_SQLITE_INCLUDE_DIRS}
          PATH_SUFFIXES libsqlite)

find_library(SQLITE_LIBRARY NAMES sqlite libsqlite
             HINTS ${PC_SQLITE_DIR} ${PC_SQLITE_LIBRARY_DIRS})

set(SQLITE_LIBRARIES ${SQLITE_LIBRARY})
set(SQLITE_INCLUDE_DIRS ${SQLITE_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set SQLITE_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(libsqlite DEFAULT_MSG
                                  SQLITE_LIBRARY SQLITE_INCLUDE_DIR)

mark_as_advanced(SQLITE_INCLUDE_DIR SQLITE_LIBRARY)
