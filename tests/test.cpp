#define BOOST_TEST_MAIN
#include <PLcomparer/PLcomparer.h>
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ExampleSuite)

BOOST_AUTO_TEST_CASE(loadJson_not_empty)
{
    nlohmann::json JsonSimple = PackageListComparer::loadJson("p10", "aarch64");

    /*std::ofstream file;
    file.open("JsonSimple.json");
    file << JsonSimple.dump(4);
    file.close();*/

    BOOST_CHECK(JsonSimple != "");
}

BOOST_AUTO_TEST_CASE(comparing)
{
    nlohmann::json Json1 = R"(
        {"packages": [
        {
            "name": "a-firstSame",
            "version": "1.1.1"
        },
        {
            "name": "b-versionUP",
            "version": "2.2.2"
        },
        {
            "name": "Extra",
            "version": "3.3.3"
        }
        ]})"_json;
    nlohmann::json Json2 = R"(
        {"packages": [
        {
            "name": "a-firstSame",
            "version": "1.1.1"
        },
        {
            "name": "b-versionUP",
            "version": "2.2.1"
        },
        {
            "name": "Missing",
            "version": "4.4.4"
        }
        ]})"_json;
    nlohmann::json JsonTrue = R"(["missing",[{"name":"Missing","version":"4.4.4"}],"extra",[{"name":"Extra","version":"3.3.3"}],"updated",[{"name":"b-versionUP","version":"2.2.2"}]])"_json;
    nlohmann::json JsonComparing = PackageListComparer::comparing(Json1, Json2);

    BOOST_REQUIRE_MESSAGE( (JsonComparing == JsonTrue), JsonComparing );
}

BOOST_AUTO_TEST_SUITE_END()