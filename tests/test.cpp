#define BOOST_TEST_MAIN
#include <PLcomparer/PLcomparer.h>
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ExampleSuite)

BOOST_AUTO_TEST_CASE(loadJson_not_empty)
{
    nlohmann::json JsonSimple = PackageListComparer::loadJson("p10", "aarch64");

    BOOST_CHECK(JsonSimple != "");
}

BOOST_AUTO_TEST_CASE(simple_comparing)
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

    BOOST_REQUIRE_MESSAGE((JsonComparing == JsonTrue), JsonComparing);
}

BOOST_AUTO_TEST_CASE(version_up_comparing)
{
    // Comparison with the result the first version is greater than the second

    // is newer
    BOOST_CHECK(PackageListComparer::CompareVersions("2.0", "1.0") == 1);
    BOOST_CHECK(PackageListComparer::CompareVersions("1.0010", "1.9") == 1);
    BOOST_CHECK(PackageListComparer::CompareVersions("1.0", "1") == 1);
    BOOST_CHECK(PackageListComparer::CompareVersions("2.50", "2.5") == 1);
    BOOST_CHECK(PackageListComparer::CompareVersions("1.0", "1.fc4") == 1);

    // is equal 
    BOOST_CHECK(PackageListComparer::CompareVersions("1", "1") == 0);
    BOOST_CHECK(PackageListComparer::CompareVersions("fc4", "fc.4") == 0);
    BOOST_CHECK(PackageListComparer::CompareVersions("1.05", "1.5") == 0);
    BOOST_CHECK(PackageListComparer::CompareVersions("3.0.0_fc", "3.0.0.fc") == 0);  

    // is older 
    BOOST_CHECK(PackageListComparer::CompareVersions("ab2.cd.e1", "ab3.cd.e1") == -1);
    BOOST_CHECK(PackageListComparer::CompareVersions("2b", "2.0") == -1);
    BOOST_CHECK(PackageListComparer::CompareVersions("FC5", "fc4") == -1);
}
BOOST_AUTO_TEST_SUITE_END()
