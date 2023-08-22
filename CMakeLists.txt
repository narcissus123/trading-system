cmake_minimum_required(VERSION 3.5)

project(tradingsystemGUI VERSION 0.1 LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Charts REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        broker.cpp
        broker.h
        momentum_trading_strategy.cpp
        momentum_trading_strategy.h
        portfolio.cpp
        portfolio.h
        pricefetcher.cpp
        pricefetcher.h
        riskmanager.cpp
        riskmanager.h
        trade.cpp
        trade.h
        tradingstrategy.cpp
        tradingstrategy.h
        authentication.cpp
        authentication.h

        regression_trading_strategy.cpp regression_trading_strategy.h)

include_directories(./yahoo-finance-master/src)
include_directories(/usr/local/include)
include_directories(/usr/local/lib)

add_subdirectory(./yahoo-finance-master)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(tradingsystemGUI
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET tradingsystemGUI APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(tradingsystemGUI SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(tradingsystemGUI
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(tradingsystemGUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets curl yahoo-finance Qt${QT_VERSION_MAJOR}::Charts)

set_target_properties(tradingsystemGUI PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(tradingsystemGUI)
endif()
