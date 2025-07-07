include("H:/Git_Overture/ChessAnalyzePlayerQtWidgets/build/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/ChessAnalyzePlayerQtWidgets-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE H:/Git_Overture/ChessAnalyzePlayerQtWidgets/build/ChessAnalyzePlayerQtWidgets.exe
    GENERATE_QT_CONF
)
