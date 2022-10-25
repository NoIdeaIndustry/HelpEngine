#pragma once

#define ASSERT(BOOL) if(!BOOL) throw;
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define DEBUG_LOG(MESSAGE) Core::Debug::Log::Print(std::string(__FILENAME__) + "::" + Core::Debug::Log::GetFunctionName(__FUNCDNAME__) + '\n' + "Line " + std::to_string(__LINE__) + " : " + MESSAGE)
#define DEBUG_LOGWARNING(MESSAGE) Core::Debug::Log::Print(std::string(__FILENAME__) + "::" + Core::Debug::Log::GetFunctionName(__FUNCDNAME__) + '\n' + "Line " + std::to_string(__LINE__) + " : " + MESSAGE, Core::Debug::Log::logType::Warning);
#define DEBUG_LOGERROR(MESSAGE) Core::Debug::Log::Print(std::string(__FILENAME__) + "::" + Core::Debug::Log::GetFunctionName(__FUNCDNAME__) + '\n' + "Line " + std::to_string(__LINE__) + " : " + MESSAGE, Core::Debug::Log::logType::Error);

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "Resources/Texture.hpp"

namespace Core::Debug {
	class Log
	{
	public:
		enum logType {
			Message,
			Warning,
			Error
		};

		static void Clear();
		static void Init();
		static void Update();
		static void Print(std::string message, logType type = Message);
		static std::string GetFunctionName(const std::string& macro);

	private:
		inline static std::vector<std::string> logs;
		inline static Resources::Texture* messageIcon, * warningIcon, * errorIcon;
	};
}
