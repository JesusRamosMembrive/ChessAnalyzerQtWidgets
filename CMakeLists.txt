cmake_minimum_required(VERSION 3.19)
project(ChessAnalyzePlayerQtWidgets)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(ChessAnalyzePlayerQtWidgets
        WIN32 MACOSX_BUNDLE
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        cardwidget.cpp
        cardwidget.h
        metricscard.cpp
        metricscard.h
        riskfactorscard.cpp
        riskfactorscard.h
        trendscard.cpp
        trendscard.h
        roianalysiscard.cpp
        roianalysiscard.h
        openingpatternscard.cpp
        openingpatternscard.h
        gamephasequalitycard.cpp
        gamephasequalitycard.h
        timemanagementcard.cpp
        timemanagementcard.h
        clutchperformancecard.cpp
        clutchperformancecard.h
        benchmarkingcard.cpp
        benchmarkingcard.h
        tacticalanalysiscard.cpp
        tacticalanalysiscard.h
        endgameanalysiscard.cpp
        endgameanalysiscard.h
        resumenanalisiscard.cpp
        resumenanalisiscard.h
)

target_link_libraries(ChessAnalyzePlayerQtWidgets
        PRIVATE
        Qt6::Core
        Qt6::Widgets
)

include(GNUInstallDirs)

install(TARGETS ChessAnalyzePlayerQtWidgets
        BUNDLE  DESTINATION .
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
