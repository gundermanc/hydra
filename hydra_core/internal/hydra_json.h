// Project Hydra
// (C) 2016 Christian Gunderman
// Json Reader and Writer

#ifndef HYDRA_JSON__H__
#define HYDRA_JSON__H__

#include "json.hpp"

#include "hydra/hydra_core.h"
#include "hydra/hydra_osdeps.h"

namespace hydra {
namespace core {

// Generic JSON file reader and writer. Only reads and writes some commonly used
// JSON constructs.
class HyJson {
public:

    // Public constructor. Creates empty Json.
    HyJson() { }

    // Loads Json from file into the object.
    HyBool LoadJsonFile(const std::string& fileName);

    // Writes Json from the object to a file.
    HyBool WriteJsonFile(const std::string& fileName);

    // Gets the string value from this Json object.
    HyBool JsonString(std::string& strValue);

    // Parses Json from file into this object.
    HyBool ParseJsonString(const std::string& jsonStr);

    // Gets a root level value from the Json.
    HyBool Value(const std::string& key, std::string& value);

    // Gets a root level list from the Json.
    HyBool List(const std::string& key, std::vector<std::string>& arr);

private:
    nlohmann::json jsonObj;
};

} // namespace core
} // namespace hydra

#endif // HYDRA_BOOTSTRAP_CONFIG__H__