set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(APPLE AND EXISTS /usr/local/opt/qt6)
	list(APPEND CMAKE_PREFIX_PATH "/usr/local/opt/qt6")
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(MagicCircle main.cpp magiccircle.cpp)

target_link_libraries(MagicCircle PUBLIC TactonPlayer Qt6::Core Qt6::Gui Qt6::Widgets)
