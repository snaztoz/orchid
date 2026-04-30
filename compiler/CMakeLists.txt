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


# Tests

add_executable(parser_tests parser_tests.cpp)

target_link_libraries(parser_tests PRIVATE orchidc)

# Copy tests/ directory
add_custom_command(TARGET parser_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/tests"
            "$<TARGET_FILE_DIR:parser_tests>/tests"
)

add_test(NAME ParserTests COMMAND parser_tests)
