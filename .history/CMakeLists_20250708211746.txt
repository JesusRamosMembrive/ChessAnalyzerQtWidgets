cmake_minimum_required(VERSION 3.19)
project(ChessAnalyzePlayerQtWidgets)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)


set(CMAKE_PREFIX_PATH "C:\\Qt\\6.9.0\\mingw_64\\lib\\cmake\\")

qt_standard_project_setup()

qt_add_resources(APP_RESOURCES assets.qrc)

qt6_add_executable(ChessAnalyzePlayerQtWidgets
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
        formmainpagewidget.h formmainpagewidget.cpp formmainpagewidget.ui
        assets.qrc
        ${APP_RESOURCES}
)

target_link_libraries(ChessAnalyzePlayerQtWidgets
        PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS ChessAnalyzePlayerQtWidgets
        BUNDLE  DESTINATION .
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
        TARGET ChessAnalyzePlayerQtWidgets
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
