#include <gtest/gtest.h>
#include "../src/Parser.hpp" // private header
#include <fstream>
#include <sstream>

class ParserTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::ifstream fstr{ "kruk.html" };
        if(!fstr) {
            throw std::runtime_error{ "Failed opening test file" };
        }
        std::stringstream buffer;
        buffer << fstr.rdbuf();

        parser = sjpp::Parser{ buffer.str() };
    }

    void TearDown() override {

    }

    sjpp::Parser parser{};
};


// TODO: Implement
TEST_F(ParserTest, ShouldParseNameTags) {
//    auto [entries, code] = parser.parse();

}

