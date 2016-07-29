// Project Hydra
// (C) 2016 Christian Gunderman
// Json Reader and Writer

#include <iostream>
#include <sstream>

#include "hydra_json.h"

using namespace nlohmann;

namespace hydra {
namespace core {

HyBool HyJson::LoadJsonFile(const std::string& fileName) {
    
    HyFile* file;
    std::stringstream buffer;
    HyInt c;

    // Unable to open file.
    if ((file = HyOpenFile(fileName.c_str(), HyOpenFileRead)) == NULL) {
        return false;
    }

    // Read all text from file into the buffer. Ideally we would use
    // a stream instead to avoid the memalloc and copying of using the
    // buffer, but laziness wins! I can fix this later. :)
    while ((c = HyReadCharFromFile(file)) != -1) {
        buffer << static_cast<HyChar>(c);
    }

    HyCloseFile(file);

    return this->ParseJsonString(buffer.str());
}

HyBool HyJson::WriteJsonFile(const std::string& fileName) {

    HyFile* file;
    
    // Unable to open file.
    if ((file = HyOpenFile(fileName.c_str(), HyOpenFileWrite)) == NULL) {
        return false;
    }

    std::string jsonText;

    // Unable to create json.
    if (!this->JsonString(jsonText)) {
        HyCloseFile(file);
        return false;
    }

    // Write all text.
    for (size_t i = 0; i < jsonText.size(); i++) {

        if (HyWriteCharToFile(file, jsonText.at(i)) == -1) {
            HyCloseFile(file);
            return false;
        }
    }

    HyCloseFile(file);

    return true;
}

HyBool HyJson::JsonString(std::string& strValue) {

    try {
        const std::string str = this->jsonObj;
        strValue = str;
    }
    catch (std::exception&) {
        return false;
    }

    return true;
}

HyBool HyJson::ParseJsonString(const std::string& jsonStr) {

    try {
        this->jsonObj = json::parse(jsonStr);
    }
    catch (const std::exception&) {
        return false;
    }

    return true;
}

HyBool HyJson::Value(const std::string& key, std::string& value) {

    basic_json<> valObj = this->jsonObj[key];

    // Invalid JSON, this is not a string.
    if (!valObj.is_string()) {
        return false;
    }

    // Implicit conversion from json to string.
    const std::string jsonVal = valObj;
    value = jsonVal;

    return true;
}

HyBool HyJson::List(const std::string& key, std::vector<std::string>& arr) {

    nlohmann::basic_json<> valObj = this->jsonObj[key];

    // Invalid JSON, this is not an array.
    if (!valObj.is_array()) {
        return false;
    }

    // Get each string in the list.
    for (size_t i = 0; i < valObj.size(); i++) {
        basic_json<> itemObj = valObj.at(i);

        // Not a string.
        if (!itemObj.is_string()) {
            return false;
        }

        arr.push_back(itemObj);
    }

    return true;
}

} // namespace core
} // namespace hydra