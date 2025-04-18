#include <rsl/static_string.hpp>

#include <catch2/catch_test_macros.hpp>

using namespace std::literals;

TEST_CASE("rsl::StaticString") {
    SECTION("Type traits") {
        STATIC_CHECK(std::is_copy_constructible_v<rsl::StaticString<8>>);
        STATIC_CHECK(std::is_copy_assignable_v<rsl::StaticString<8>>);
        STATIC_CHECK(std::is_nothrow_move_constructible_v<rsl::StaticString<8>>);
        STATIC_CHECK(std::is_nothrow_move_assignable_v<rsl::StaticString<8>>);
    }

    SECTION("Construction") {
        SECTION("Default constructor") {
            auto const static_string = rsl::StaticString<10>();
            CHECK(static_string.begin() == static_string.end());
        }

        SECTION("Collection constructor") {
            auto const string = "Hello, world!"s;
            auto const static_string = rsl::StaticString<14>(string);
            CHECK(static_string.begin() != static_string.end());
            auto begin = static_string.begin();  // NOLINT(readability-qualified-auto)
            CHECK(*begin++ == 'H');
            CHECK(*begin++ == 'e');
            CHECK(*begin++ == 'l');
            CHECK(*begin++ == 'l');
            CHECK(*begin++ == 'o');
            CHECK(*begin++ == ',');
            CHECK(*begin++ == ' ');
            CHECK(*begin++ == 'w');
            CHECK(*begin++ == 'o');
            CHECK(*begin++ == 'r');
            CHECK(*begin++ == 'l');
            CHECK(*begin++ == 'd');
        }
    }

    SECTION("begin()") {
        auto const static_string = rsl::StaticString<5>("foo");
        CHECK(static_string.begin() == std::begin(static_string));
        CHECK(static_string.begin() == std::cbegin(static_string));
        CHECK(*static_string.begin() == 'f');
    }

    SECTION("end()") {
        auto const static_string = rsl::StaticString<5>("bar");
        CHECK(static_string.end() == std::end(static_string));
        CHECK(static_string.end() == std::cend(static_string));
    }

    SECTION("std::string_view()") {
        auto const static_vector = rsl::StaticString<22>("Robot Operating System");
        auto const string_view = std::string_view(static_vector);
        CHECK(string_view[0] == 'R');
        CHECK(string_view[1] == 'o');
        CHECK(string_view[2] == 'b');
        CHECK(string_view[3] == 'o');
        CHECK(string_view[4] == 't');
        CHECK(string_view[5] == ' ');
        CHECK(string_view[6] == 'O');
        CHECK(string_view[7] == 'p');
        CHECK(string_view[8] == 'e');
        CHECK(string_view[9] == 'r');
        CHECK(string_view[10] == 'a');
        CHECK(string_view[11] == 't');
        CHECK(string_view[12] == 'i');
        CHECK(string_view[13] == 'n');
        CHECK(string_view[14] == 'g');
        CHECK(string_view[15] == ' ');
        CHECK(string_view[16] == 'S');
        CHECK(string_view[17] == 'y');
        CHECK(string_view[18] == 's');
        CHECK(string_view[19] == 't');
        CHECK(string_view[20] == 'e');
        CHECK(string_view[21] == 'm');
    }
}

TEST_CASE("rsl::to_string") {
    CHECK(rsl::to_string(rsl::StaticString<0>()).empty());
    CHECK(rsl::to_string(rsl::StaticString<10>("happy"s)) == "happy"s);
}
