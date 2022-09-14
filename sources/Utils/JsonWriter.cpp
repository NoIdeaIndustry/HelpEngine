#include "Utils/JsonWriter.hpp"

#include <iostream>
#include <filesystem>

namespace NJson
{
	void JsonWriter::Create(const std::string& p_FileName) {
		if (std::filesystem::exists(p_FileName)) {
			std::cout << "Json file detected, aborting!" << std::endl;
			jsonExist = true;
		}
		else {
			std::cout << "Json file not detected, creating..." << std::endl;
			jsonExist = false;
		}

		if (!jsonExist) {
			std::ofstream outfile(p_FileName);
			outfile.close();

			std::cout << "Json file created!" << std::endl;
			jsonExist = true;
		}
	}

	void JsonWriter::Delete() {
		json.flush();
		json.close();
	}

	void JsonWriter::Serialize() {
		if (!json.is_open()) {
			std::cout << "File cannot be serialized, Make sure it is openned beforehand!" << std::endl;
			return;
		}
	}

	void JsonWriter::Open(const std::string& p_FileName) {
		json.open(p_FileName);
	}

	void JsonWriter::Close() {
		json.close();
	}
}
