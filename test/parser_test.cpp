#include <gtest/gtest.h>
#include "../src/Parser.hpp" // private header
#include <fstream>
#include <array>
#include <sstream>

class ParserTest : public ::testing::Test {
protected:
    static const std::array<sjpp::Entry, 7> expected_entries;


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

const std::array<sjpp::Entry, 7> ParserTest::expected_entries{
        sjpp::Entry{ "kruk", "wszystkożerny ptak z rodziny krukowatych, o czarnym upierzeniu", true },
        sjpp::Entry{ "kruk", "przenośnie: (głównie w l.mn.) człowiek zły, żerujący na ludzkiej tragedii", true },
        sjpp::Entry{ "kruk", "przenośnie: zwiastun nieszczęścia", true },
        sjpp::Entry{ "kruk", "biały kruk - unikat", true },
        sjpp::Entry{ "kruk", "dawniej: strażnik strzegący domostwa pracodawców", true },
        sjpp::Entry{ "Kruk", "nazwisko", false },
        sjpp::Entry{ "Kruk", "łac. Corvus; gwiazdozbiór", false }
};


TEST_F(ParserTest, ShouldParseHTML) {
    auto [entries, code] = parser.parse();

    ASSERT_EQ(code, sjpp::Code::ok);
    for(std::size_t i = 0; i < entries.size(); ++i) {
        EXPECT_EQ(entries[i].word, expected_entries[i].word);
        EXPECT_EQ(entries[i].meaning, expected_entries[i].meaning);
        EXPECT_EQ(entries[i].allowed_in_games, expected_entries[i].allowed_in_games);
    }
}

