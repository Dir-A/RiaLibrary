# Library Name
set(PROJECT_NAME Rut)

# Cpp Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set Source File Path
list(APPEND SRC_FILE 
    "${CMAKE_CURRENT_SOURCE_DIR}/RxBench/Record.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/RxPath/Enum.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/RxPath/Path.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/RxStream/ConsoleStream/AllocConsole.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/RxStream/ConsoleStream/PutConsole.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/RxStream/FileStream/BasicStream.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/RxStream/FileStream/TextStream.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/RxStream/MemoryStream/AutoMem.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/RxString/Convert.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/RxString/Trim.cpp")

# Set Library
add_library(${PROJECT_NAME} "${SRC_FILE}")
