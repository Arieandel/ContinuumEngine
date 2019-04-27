#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


namespace ContinuumEngine3D {

	enum class MessageType : unsigned short {// memory efficient for switching things like menu, arrys that has defined start and end point
		TYPE_NONE = 0, // start point
		TYPE_FATAL_ERROR,
		TYPE_ERROR,
		TYPE_WARNING,
		TYPE_TRACE,
		TYPE_INFO
	};


	class Debug
	{
	public:
		Debug(const Debug&) = delete;
		Debug(Debug&&) = delete;
		Debug& operator=(const Debug&) = delete;
		Debug& operator=(Debug&&) = delete;
		Debug() = delete; //makes the class static <no constructor or destructor>

		static void DebugInit();
		static void SetSeverity(MessageType type_);
		static void Info(const std::string& message_, const std::string& fileName_, const int line_);
		static void Trace(const std::string& message_, const std::string& fileName_, const int line_);
		static void Warning(const std::string& message_, const std::string& fileName_, const int line_);
		static void Error(const std::string& message_, const std::string& fileName_, const int line_);
		static void FatalError(const std::string& message_, const std::string& fileName_, const int line_);


	private:
		static void Log(const MessageType type_, const std::string& message_, const std::string& fileName_, const int line_);
		static MessageType currentSeverity;
	};
}
#endif