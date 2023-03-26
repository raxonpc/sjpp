#include <gtest/gtest.h>
#include "sjpp/sjpp.hpp"
#include <fstream>
#include <array>
#include <sstream>

class SJPApiTest : public ::testing::Test {
  protected:
    sjpp::SjpAPI api{};


    void SetUp() override {

    }

    void TearDown() override {

    }
};

TEST_F(SJPApiTest, ShouldFindValidEntries) {
    static const std::array<sjpp::Entry, 7> expected_entries{
        sjpp::Entry{ "kruk", "wszystkożerny ptak z rodziny krukowatych, o czarnym upierzeniu", true },
        sjpp::Entry{ "kruk", "przenośnie: (głównie w l.mn.) człowiek zły, żerujący na ludzkiej tragedii", true },
        sjpp::Entry{ "kruk", "przenośnie: zwiastun nieszczęścia", true },
        sjpp::Entry{ "kruk", "biały kruk - unikat", true },
        sjpp::Entry{ "kruk", "dawniej: strażnik strzegący domostwa pracodawców", true },
        sjpp::Entry{ "Kruk", "nazwisko", false },
        sjpp::Entry{ "Kruk", "łac. Corvus; gwiazdozbiór", false }
    };

    auto [entries, code] = api.get_entries("kruk");
    ASSERT_EQ(code, sjpp::Code::ok);
    for(std::size_t i = 0; i < expected_entries.size(); ++i) {
        EXPECT_EQ(entries.at(i).word, expected_entries.at(i).word);
        EXPECT_EQ(entries.at(i).meaning, expected_entries.at(i).meaning);
        EXPECT_EQ(entries.at(i).allowed_in_games, expected_entries.at(i).allowed_in_games);
    }
}

TEST_F(SJPApiTest, ShouldIDetectMissingWord) {
    auto [entries, code] = api.get_entries("abacaba");
    EXPECT_EQ(code, sjpp::Code::wordNotFound);
}

TEST_F(SJPApiTest, ShouldDetectMissingEntries) {
    auto [entries, code] = api.get_entries("wypasa");
    EXPECT_EQ(code, sjpp::Code::missingEntries);
}

TEST_F(SJPApiTest, ShouldIndicateMissingWord) {
    auto [entries, code] = api.get_entries("abacaba");
    EXPECT_EQ(code, sjpp::Code::wordNotFound);
}
