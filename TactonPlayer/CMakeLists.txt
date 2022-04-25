add_subdirectory(ArduinoSerial)

set(source_files 
  Tacton.cpp 
  TactonPlayer.cpp
)
add_library(TactonPlayer ${source_files})

target_link_libraries(TactonPlayer PUBLIC ArduinoSerial)

target_include_directories(TactonPlayer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

