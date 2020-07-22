// Let Catch provide main():
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "mercury.hpp"

/**
 * TEST LOGGER CLASS
 */


TEST_CASE( "The singleton instance of the logger can be retrived", "[get]" ) {
    // Get the singleton instance of the logger
    mercury::Logger &mercury = mercury::Logger::get();
    SUCCEED("Not sure how to check type of object yet");
};

TEST_CASE( "A Level has a corosponding Level Name", "[getLevelName]" ) {
    mercury::Logger &mercury = mercury::Logger::get();

    for (int i = 0; i < 7; i++) {
        mercury::Level l = static_cast<mercury::Level>(i);
        REQUIRE( mercury.getLevelName(l) == mercury::level_names[i] );
    };
}

TEST_CASE( "The current level can be retrieved", "[getLevel]" ) {
    mercury::Logger &mercury = mercury::Logger::get();
    // The default level is dbeug
    REQUIRE( mercury.getLevel() == mercury::Level::debug );
};

TEST_CASE( "The logger can be set to 6 levels", "[setLevel]" ) {
    mercury::Logger &mercury = mercury::Logger::get();

    for (int i = 0; i < 7; i++) {
        mercury::Level l = static_cast<mercury::Level>(i);
        mercury.setLevel(l);
        REQUIRE( mercury.getLevel() == i );
    };
};

TEST_CASE( "The Logger theme memeber can be retrieved as a pointer", "[getTheme]") {
    mercury::Logger &mercury = mercury::Logger::get();
    // Get the pointer to the theme used by mercury
    mercury::Theme *t = mercury.getTheme();
    REQUIRE(t != NULL);
};

TEST_CASE( "Every level has a funcrion to log at that level", "[level]" ) {
    mercury::Logger &mercury = mercury::Logger::get();

    mercury.trace("Turning the fan on");
    SUCCEED("Not sure how to for stdout");
    mercury.info("Fan on");
    SUCCEED("Not sure how to for stdout");
    mercury.debug("Is there somthing wrong with the fan?");
    SUCCEED("Not sure how to for stdout");
    mercury.warn("Yo $#%& may be hitting the fan");
    SUCCEED("Not sure how to for stdout");
    mercury.critical("$#%& JUST HIT THE FAN");
    SUCCEED("Not sure how to for stdout");
};

/**
 * TEST THEME CLASS
 */

TEST_CASE( "The sperator can be retrieved from the theme", "[getSeperator]" ) {
    mercury::Logger &mercury = mercury::Logger::get();
    mercury::Theme *t = mercury.getTheme();
    REQUIRE(t -> getSeperator() == " - ");
};

TEST_CASE( "The sperator can be changed", "[setSeperator]" ) {
    mercury::Logger &mercury = mercury::Logger::get();
    mercury::Theme *t = mercury.getTheme();

    t -> setSeperator("---");
    REQUIRE(t -> getSeperator() == "---");
    // set back to default 
    t -> setSeperator(" - ");
};

TEST_CASE( "The Vector2 stuct can be found for any level", "[getLevelTheme]" ) {
    mercury::Logger &mercury = mercury::Logger::get();
    mercury::Theme *t = mercury.getTheme();
    mercury::Vector2 crit {35, 1};
    
    REQUIRE(  t -> getLevelTheme(mercury::Level::critical).color ==  crit.color );
};

TEST_CASE( "The timestamp visibility can retrieved", "[getIsTimestampVisibile]" ) {
    mercury::Logger &mercury = mercury::Logger::get();
    mercury::Theme *t = mercury.getTheme();
    REQUIRE(  t -> getIsTimestampVisibile() == true );
};

TEST_CASE( "The timestamp visibility can set", "[setIsTimestampVisibile]" ) {
    mercury::Logger &mercury = mercury::Logger::get();
    mercury::Theme *t = mercury.getTheme();
    t -> setIsTimestampVisibile(false);
    REQUIRE(  t -> getIsTimestampVisibile() == false );
};

TEST_CASE( "The length of the level names can be retrieved", "[getLevelNameLen]" ) {
    mercury::Logger &mercury = mercury::Logger::get();
    mercury::Theme *t = mercury.getTheme();
    REQUIRE(  t -> getLevelNameLen() == 4 );
};

TEST_CASE( "The length of the level names can be set", "[setLevelNameLen]" ) {
    mercury::Logger &mercury = mercury::Logger::get();
    mercury::Theme *t = mercury.getTheme();
    t -> setLevelNameLen(1);
    REQUIRE(  t -> getLevelNameLen() == 1 );

    REQUIRE_THROWS( t -> setLevelNameLen(9) );
};

TEST_CASE( "A theme can be applied to a string", "[apply]" ) {
    mercury::Logger &mercury = mercury::Logger::get();
    mercury::Theme *t = mercury.getTheme();
    std::string s = "Just like the simulations";
    std::string n = t -> apply(mercury.getLevel(), s);
    std::string f = "\033[";
    f += std::to_string(t -> getInfo().style) + ";";
    f += std::to_string(t -> getInfo().color) + "m";
    f += s + "\033[0m";

    REQUIRE( n == f );
};
