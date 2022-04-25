set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(APPLE AND EXISTS /usr/local/opt/qt6)
	list(APPEND CMAKE_PREFIX_PATH "/usr/local/opt/qt6")
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(AngleTester main.cpp angletester.cpp)

target_link_libraries(AngleTester PRIVATE TactonPlayer Qt6::Core Qt6::Gui Qt6::Widgets)
