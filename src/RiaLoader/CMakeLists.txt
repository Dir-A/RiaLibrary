# Value Define
set(CMAKE_WIN32_EXECUTABLE ON)
set(PROJECT_NAME RiaLoader)

# Cpp Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add Library
link_libraries(Rut RxHook RxINI)

# Current Project
project("${PROJECT_NAME}")
add_executable(${PROJECT_NAME} "RiaLoader.cpp")
