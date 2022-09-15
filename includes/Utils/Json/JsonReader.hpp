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
		inline static std::ifstream json;
	};
}