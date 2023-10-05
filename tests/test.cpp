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

    BOOST_CHECK(PackageListComparer::CompareVersions("9.6.3", "1.3.0") == 1);
    BOOST_CHECK(PackageListComparer::CompareVersions("0.0.26", "0.0.23b") == 1);
    BOOST_CHECK(PackageListComparer::CompareVersions("0.7.3.git3a25392", "0.6svn") == 1);
    BOOST_CHECK(PackageListComparer::CompareVersions("10", "p9") == 1);
    BOOST_CHECK(PackageListComparer::CompareVersions("0.9.6", "0.9.3b.0.31.git701e3a3") == 1);
    BOOST_CHECK(PackageListComparer::CompareVersions("0.3.2", "0+bzr726") == 1);
    BOOST_CHECK(PackageListComparer::CompareVersions("1.57", "1.55_04") == 1);
    BOOST_CHECK(PackageListComparer::CompareVersions("4.4_1.0.1", "4.4_0.94") == 1);
    
}

BOOST_AUTO_TEST_SUITE_END()
