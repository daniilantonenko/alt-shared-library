#include <pl-comparer/pl-comparer.h>

using plc = PackageListComparer::Comparator;
using json = nlohmann::json;

int main() {
  json jsonFirst = R"(
		{
			"libstart": "boo",
			"foo": "bar"
		}
	)"_json;
  json jsonSecond = R"(
		{
			"libstart": "boo",
			"libnew": "wow"
		}
	)"_json;

  /*
          // create the patch
          json patch = json::diff(jsonFirst, jsonSecond);

          // roundtrip
          json patched_source = jsonFirst.patch(patch);

          // output patch and roundtrip result
          std::cout << patch.dump(4) << "\n\n"
                          << patched_source.dump(4) << std::endl;
  */


  plc newClass(jsonFirst, jsonSecond);

  json myClass = newClass.getThisJson();

  std::cout << myClass.dump(4) << std::endl;

  return 0;
}
