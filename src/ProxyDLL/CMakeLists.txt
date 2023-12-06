# Check Is x32
if (NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
	return()
endif()

# Value Define
set(PROJECT_NAME ProxyDLL)

# Cpp Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Current Project
project("${PROJECT_NAME}")
add_library(${PROJECT_NAME} MODULE "dllmain.cpp")
