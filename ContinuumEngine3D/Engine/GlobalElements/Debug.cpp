#include "Debug.h"


namespace ContinuumEngine3D {

	MessageType Debug::currentSeverity = MessageType::TYPE_NONE; //we need to initialize it in cpp as well since its static


	void Debug::DebugInit() {
		std::ofstream out;
		out.open("GAME301Log.txt", std::ios::out); // lets you write to the file
		out.close();
		currentSeverity = MessageType::TYPE_INFO;
	}
	void Debug::SetSeverity(MessageType type_) {
		currentSeverity = type_;
	}

	void Debug::Log(const MessageType type_, const std::string& message_, const std::string& fileName_, const int line_) {
		if (type_ <= currentSeverity && currentSeverity > MessageType::TYPE_NONE) {
			std::ofstream file;
			file.open("GAME301Log.txt", std::ios::out | std::ios::app);
			file << message_ << " in " << fileName_ << " on line: " << line_;
			file.flush();
			file.close();
		}
	}
	void Debug::Info(const std::string& message_, const std::string& fileName_, const int line_) {

		Log(MessageType::TYPE_INFO, "[INFO]" + message_, fileName_, line_);

	}
	void Debug::Trace(const std::string& message_, const std::string& fileName_, const int line_) {

		Log(MessageType::TYPE_TRACE, "[TRACE]" + message_, fileName_, line_);

	}
	void Debug::Warning(const std::string& message_, const std::string& fileName_, const int line_) {

		Log(MessageType::TYPE_WARNING, "[WARNING]" + message_, fileName_, line_);

	}
	void Debug::Error(const std::string& message_, const std::string& fileName_, const int line_) {

		Log(MessageType::TYPE_ERROR, "[ERROR]" + message_, fileName_, line_);

	}
	void Debug::FatalError(const std::string& message_, const std::string& fileName_, const int line_) {

		Log(MessageType::TYPE_FATAL_ERROR, "[FATAL_ERROR]" + message_, fileName_, line_);

	}

}