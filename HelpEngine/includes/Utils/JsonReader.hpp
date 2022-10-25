#pragma once

#include <fstream>
#include <string>

namespace NJson
{
	class JsonReader
	{
	public:
		static void Deserialize();

		static void Open(const std::string& p_FileName);
		static void Close();

	private:
		static std::ifstream json;
	};
}