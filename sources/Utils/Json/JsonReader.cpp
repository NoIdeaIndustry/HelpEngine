#include "Utils/Json/JsonReader.hpp"

#include <iostream>

namespace NJson {
	void JsonReader::Deserialize() {
		if (!json.is_open()) {
			std::cout << "File cannot be deserialized, Make sure it is openned beforehand!" << std::endl;
			return;
		}

		std::string field;

		while (json) {
			std::getline(json, field);
			std::cout << field << ": " << json.tellg() << '\n';
		}
	}

	void JsonReader::Open(const std::string& p_FileName) {
		json.open(p_FileName);
	}

	void JsonReader::Close() {
		json.close();
	}
}