add_library(orchidc
    ast.hpp
    compiler.cpp
    compiler.hpp
    lexer.cpp
    lexer.hpp
    parser.cpp
    parser.hpp
    token.hpp
)

if(MSVC)
    target_compile_options(orchidc PRIVATE /W4)
else()
    target_compile_options(orchidc PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_include_directories(orchidc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()

add_executable(parser_tests
    parser_tests.cpp
)

target_link_libraries(parser_tests PRIVATE orchidc)

add_test(NAME ParserTests COMMAND parser_tests)
