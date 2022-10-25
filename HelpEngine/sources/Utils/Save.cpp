#include "Utils/Save.hpp"

#pragma region System
#include <filesystem>
#include <string>
#include <iostream>
#include <sstream>
#pragma endregion

#define SAVEFILE_NAME "Save.json"

namespace Data
{
	void SaveData::Exist()
	{
		if (std::filesystem::exists(SAVEFILE_NAME)) {
			std::cout << "Save file Detected!" << std::endl;
			fileExist = true;
		}
		else {
			std::cout << "Save file not detected!" << std::endl;
			fileExist = false;
		}
	}


	void SaveData::Create() {
		std::cout << "Creating save file...." << std::endl;

		std::ofstream outfile(SAVEFILE_NAME);
		outfile.close();
		std::cout << "Save file created!" << std::endl;
	}

	bool SaveData::Load()
	{
		if (fileExist)
		{
			bool readPosition = false;
			bool readLife = false;
			bool readProgress = false;
			bool readData = false;

			std::ifstream save;
			std::string line;
			save.open("Save.json");

			int supposedValue = 1;

			/*while (std::getline(save, line))
			{
				int offset = GetLineOffset(line.c_str());

				std::istringstream iss(line.substr(offset));

				if (memcmp(line.c_str(), "\"ForwardKey\"", 16) == 0)
				{
					readPosition = true; readData = true;
				}
				else if (memcmp(line.c_str(), "\"BackwardKey\"", 12) == 0)
				{
					readLife = true; readData = true;
				}
				else if (memcmp(line.c_str(), "\"Lef\"", 16) == 0)
				{
					readProgress = true; readData = true;
				}

				if (readData)
				{
					if (readPosition && line != "\"PlayerPosition\": [" && line != "    {")
					{
						switch (supposedValue)
						{
						case 1: iss >> playerPos.x; break;
						case 2: iss >> playerPos.y; break;
						case 3: iss >> playerPos.z; readPosition = false; readData = false;  break;
						default: break;
						}
						supposedValue++;
					}

					else if (readLife && line != "\"PlayerLife\": [" && line != "    {")
					{
						iss >> playerLife; readLife = false; readData = false;
					}

					else if (readProgress && line != "\"PlayerProgress\": [" && line != "    {")
					{
						iss >> playerLevel; readProgress = false; readData = false;
					}
				}
			}*/
			std::cout << "Sucessfully Loaded Save" << std::endl;
			return true;
		}
		else
		{
			std::cout << "Save Doesnt Exist" << std::endl;
			return false;
		}
	}

	void SaveData::Erase()
	{

	}

	void SaveData::Save()
	{
		fileExist = true;
		saveFile.open("Save.json");

		saveFile << "{\n";
		CreateField("ForwardKey", { "keycode" }, { (float)forwardKey });
		CreateField("BackwardKey", { "keycode" }, { (float)backwardKey });
		CreateField("LeftKey", { "keycode" }, { (float)leftKey });
		CreateField("RightKey", { "keycode" }, { (float)rightKey });
		saveFile << "}\n";

		saveFile.close();

		std::cout << "Sucessfully Saved Game" << std::endl;
	}

	int SaveData::GetLineOffset(const char* s_Str)
	{
		int l_LineOffset = 0;

		if (memcmp(s_Str, "     \"X\": ", 10) == 0 || memcmp(s_Str, "     \"Y\": ", 10) == 0 || memcmp(s_Str, "     \"Z\": ", 10) == 0)
			return l_LineOffset = 10;
		else if (memcmp(s_Str, "     \"Amount\": ", 15) == 0)
			return l_LineOffset = 15;
		else if (memcmp(s_Str, "     \"Level\": ", 14) == 0)
			return l_LineOffset = 14;
		else if (memcmp(s_Str, "     \"PlayerProgress\": ", 23) == 0)
			return l_LineOffset = 23;
		else return l_LineOffset = 0;
	}

	void SaveData::CreateField(const std::string& _fieldName, const std::vector<std::string>& _dataName, std::vector<float> _dataValue)
	{
		fieldCount++; int index = 0;

		std::string fieldName = "\"" + _fieldName + "\": [\n";
		saveFile << fieldName;
		saveFile << "    {\n";

		_dataValue.insert(_dataValue.begin(), NULL);
		for (std::string s : _dataName)
		{
			index++;
			std::string dataName = "     \"" + s + "\": ";
			if (_dataName.size() <= 1 || _dataName.size() == index)
				saveFile << dataName << _dataValue[index] << "\n";
			else
				saveFile << dataName << _dataValue[index] << ",\n";
		}
		saveFile << "    }\n";

		if (fieldCount == 3)
			saveFile << "  ]\n";
		else
			saveFile << "  ],\n";
	}
}
