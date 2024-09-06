#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "DCMTK::dcmtk" for configuration "RelWithDebInfo"
set_property(TARGET DCMTK::dcmtk APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(DCMTK::dcmtk PROPERTIES
  IMPORTED_IMPLIB_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/dcmtk.lib"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/bin/dcmtk.dll"
  )

list(APPEND _cmake_import_check_targets DCMTK::dcmtk )
list(APPEND _cmake_import_check_files_for_DCMTK::dcmtk "${_IMPORT_PREFIX}/lib/dcmtk.lib" "${_IMPORT_PREFIX}/bin/dcmtk.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
