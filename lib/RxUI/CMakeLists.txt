# Library Name
set(USER_PROJECT_NAME RxUI)

# Cpp Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set Source File Path
list(APPEND SRC_FILE 
    "${CMAKE_CURRENT_SOURCE_DIR}/Win32/Dialog/OpenFileDialog.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Win32/UI/Tools.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Win32/UI/UI_Basic.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Win32/Window/MainWindow.cpp" 
)

# Set Current Library
add_library(${USER_PROJECT_NAME} "${SRC_FILE}")
