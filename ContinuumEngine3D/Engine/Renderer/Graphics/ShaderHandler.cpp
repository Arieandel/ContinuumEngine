#include "ShaderHandler.h"


namespace ContinuumEngine3D {

	std::unique_ptr<ShaderHandler> ShaderHandler::shaderInstance = nullptr;
	std::map<std::string, GLuint> ShaderHandler::programs = std::map<std::string, GLuint>();

	ShaderHandler::ShaderHandler()
	{
	}


	ShaderHandler::~ShaderHandler()
	{
		if (programs.size() > 0) {
			for (auto entry : programs) {
				glDeleteProgram(entry.second);
			}

			programs.clear();
		}
	}

	ShaderHandler* ShaderHandler::GetInstance() {
		if (shaderInstance.get() == nullptr) {
			shaderInstance.reset(new ShaderHandler);
		}
		return shaderInstance.get();

	}


	void ShaderHandler::CreateProgram(const std::string& shaderName_, const std::string& vertexFilePath_, const std::string& fragmentFilePath_) {
		std::string vertexCode = ReadShader(vertexFilePath_);
		std::string fragmentCode = ReadShader(fragmentFilePath_);

		GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexCode, vertexFilePath_);
		GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentCode, fragmentFilePath_);
		std::cout << vertexFilePath_ << std::endl;
		std::cout << fragmentFilePath_ << std::endl;
		GLint linkResult = 0;
		GLuint program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
		if (!linkResult) {
			GLint infoLogLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
			char programLog[512];
			glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]);
			Debug::Error("Shader Loader: Link error: " + shaderName_ + ": " + programLog, __FILE__, __LINE__);
			return;
		}
		programs[shaderName_] = program;
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	const GLuint ShaderHandler::GetShader(const std::string& shaderName_) {
		if (programs.find(shaderName_) != programs.end()) {
			return programs[shaderName_];
		}
		return -1;
	}


	std::string ShaderHandler::ReadShader(const std::string& fileName_) {
		std::string shaderCode;
		std::ifstream file;
		file.exceptions(std::ifstream::badbit);
		try {
			file.open(fileName_);
			std::stringstream tmpStream;
			tmpStream << file.rdbuf();
			file.close();
			shaderCode = tmpStream.str();
		}
		catch (std::ifstream::failure error_) {
			Debug::Error("Cloud not read the shader file:" + fileName_, __FILE__, __LINE__);
			return "";

		}
		return shaderCode;
	}
	GLuint ShaderHandler::CreateShader(GLenum shaderType_, const std::string& source_, const std::string& shaderName_) {
		GLint compileResult = 0;
		GLuint shader = glCreateShader(shaderType_);
		const char* shaderCodePtr = source_.c_str();
		const int shaderSize = source_.size();

		glShaderSource(shader, 1, &shaderCodePtr, &shaderSize);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
		if (!compileResult) {
			GLint infoLogLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			char shaderLog[512];
			glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
			Debug::Error("Error compiling shader " + shaderName_ + "\n" + shaderLog, __FILE__, __LINE__);
			return -1;
		}
		return shader;

	}


}