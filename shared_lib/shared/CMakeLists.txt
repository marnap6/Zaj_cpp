cmake_minimum_required(VERSION 3.16)
project(untitled9 VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Tworzenie shared library
add_library(library SHARED library.cpp)

# Eksport symboli na Windows
if(WIN32)
    target_compile_definitions(library PRIVATE LIBRARY_EXPORTS)
endif()

# Instalowanie biblioteki i nagłówków
include(GNUInstallDirs)

install(TARGETS library
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}  # .dll, .so, .dylib
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})  # nagłówki
set_target_properties(library PROPERTIES PUBLIC_HEADER "library.h")
