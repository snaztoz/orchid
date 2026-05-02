#include <cassert>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <print>
#include <sstream>
#include <string>

#include "parser.hpp"

std::string read_fixture(std::filesystem::path path)
{
    std::ifstream file(path.make_preferred());

    if (!file.is_open())
    {
        std::println(stderr, "failed (could not open {})",
                     path.generic_string());
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
        std::print(stderr, "test {} parsing...", name);                        \
        auto fixture { read_fixture(fixture_path) };                           \
        orchid::compiler::Parser parser { fixture };                           \
        if (auto res = parser.parse(); !res)                                   \
        {                                                                      \
            std::println(stderr, "failed ({})", res.error());                  \
            std::exit(1);                                                      \
        }                                                                      \
        std::println(stderr, "ok");                                            \
    } while (0);

int main()
{
    std::println(stderr, "current working directory: {}",
                 std::filesystem::current_path().generic_string());

    try
    {
        for (const auto &entry : std::filesystem::directory_iterator(
                 std::filesystem::current_path()))
        {
            std::println(stderr, "cwd entry: {}",
                         entry.path().filename().generic_string());
        }
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::println(stderr, "error: {}", e.what());
    }

    try
    {
        for (const auto &entry :
             std::filesystem::directory_iterator("tests/parser"))
        {
            std::println(stderr, "{}",
                         entry.path().filename().generic_string());
        }
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::println(stderr, "error: {}", e.what());
    }

    TEST_PARSE("namespace", "tests/parser/namespace.orchid");
    TEST_PARSE("use", "tests/parser/use.orchid");

    std::println(stderr, "all tests passed!");

    return 0;
}
