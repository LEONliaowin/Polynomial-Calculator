cmake_minimum_required(VERSION 3.28)
project(Calculator_GUI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/APP/Qt/5.12.12/mingw73_64")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        UiTools
        REQUIRED)

add_executable(Calculator_GUI WIN32 src/main.cpp
        src/Polynomial.cpp
        src/Polynomial.h
        src/Normal.cpp
        src/Normal.h
        src/Normal_GUI.cpp
        src/Normal_GUI.h
        src/Polynomial_GUI.cpp
        src/Polynomial_GUI.h
        src/History.cpp
        src/History.h
        src/StartupDialog.cpp
        src/StartupDialog.h
)
target_link_libraries(Calculator_GUI
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::UiTools
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()

add_executable(test src/test.cpp
        src/Polynomial.cpp
        src/Polynomial.h
        src/Normal.cpp
        src/Normal.h
        src/History.cpp
        src/History.h
)
target_link_libraries(test
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::UiTools
)