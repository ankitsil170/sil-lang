# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\sil-lang_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\sil-lang_autogen.dir\\ParseCache.txt"
  "sil-lang_autogen"
  )
endif()
