cmake_minimum_required(VERSION 3.19)
project(ChessAnalyzePlayerQtWidgets)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6Widgets REQUIRED)


set(CMAKE_PREFIX_PATH "C:\\Qt\\6.9.0\\mingw_64\\lib\\cmake\\")

qt_standard_project_setup()

qt_add_executable(ChessAnalyzePlayerQtWidgets
        WIN32 MACOSX_BUNDLE
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        logindialog.cpp
        logindialog.h
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
