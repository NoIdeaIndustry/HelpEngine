#pragma once

#include <fstream>
#include <vector>

namespace Data
{
	class SaveData
	{
	public:
		static void Create();
		static void Save();
		static bool Load();
		static void Erase();
		static void Exist();

		static int GetLineOffset(const char* s_Str);
		static void CreateField(const std::string& _fieldName, const std::vector<std::string>& _dataName, std::vector<float> _dataValue);

		inline static bool fileExist = false;

		inline static int forwardKey, backwardKey, leftKey, rightKey;

	private:
		inline static std::ofstream saveFile;

		inline static int fieldCount = 0;
	};
}
