#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "parser.hpp"

std::string read_fixture(const char *path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr << "error: could not open " << path << std::endl;
        std::exit(1);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string contents = buffer.str();

    file.close();

    return contents;
}

#define TEST_PARSE(name, fixture_path)                                         \
    do                                                                         \
    {                                                                          \
        std::cerr << "test " << name << " parsing... ";                        \
        auto fixture { read_fixture(fixture_path) };                           \
        orchid::compiler::Parser parser { fixture };                           \
        if (auto res = parser.parse(); !res)                                   \
        {                                                                      \
            std::cerr << "failed (" << res.error() << ")" << std::endl;        \
            std::exit(1);                                                      \
        }                                                                      \
        std::cerr << "ok" << std::endl;                                        \
    } while (0);

int main()
{
    TEST_PARSE("namespace", "./tests/parser/namespace.orchid");
    TEST_PARSE("use", "./tests/parser/use.orchid");

    std::cerr << "all tests passed!" << std::endl;

    return 0;
}
