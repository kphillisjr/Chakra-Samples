if(MSVC OR WIN32 OR CYGWIN)
  #TODO: Add support for windows.
else()
  add_subdirectory(Linux_OSX)
endif()
