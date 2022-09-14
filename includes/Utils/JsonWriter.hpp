#pragma once

#include <fstream>
#include <string>

namespace NJson
{
	class JsonWriter
	{
	public:
		static void Serialize();

		static void Create(const std::string& p_FileName);
		static void Delete();

		static void Open(const std::string& p_FileName);
		static void Close();

	private:
		static std::ofstream json;
		static bool jsonExist;
	};
}
