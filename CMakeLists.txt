cmake_minimum_required(VERSION 3.19)
project(sil-lang LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(sil-lang
    main.cpp
    lexer/lexer.h lexer/lexer.cpp
    lexer/token.h lexer/token.cpp
    parser/parser.h parser/parser.cpp
    interpreter/interpreter.h interpreter/interpreter.cpp
    runtime/environment.h
    examples/hello.sil
    examples/math.sil
    examples/variables.sil

)

target_link_libraries(sil-lang
    PRIVATE
        Qt::Core
)

include(GNUInstallDirs)

install(TARGETS sil-lang
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
