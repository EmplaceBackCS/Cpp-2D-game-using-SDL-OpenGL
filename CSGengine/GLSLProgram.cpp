#include "GLSLProgram.h"

namespace CSGengine
{
	//constructor
	GLSLProgram::GLSLProgram() : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0) {}

	//--------------------------- Shader compiler function----------------------------
	void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
	{
		//Vertex and fragment shaders are successfully compiled
		//Now time to link them together into the program
		//Get a program object
		_programID = glCreateProgram();

		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		//If something went wrong and it returned 0 above, exit the game
		if (_vertexShaderID == 0)
		{
			getFatalError("Vertext shader failed to be created!");
		}

		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		//If something went wrong and it returned 0 above, exit the game
		if (_fragmentShaderID == 0)
		{
			getFatalError("Fragment shader failed to be created!");
		}

		compileShader(vertexShaderFilePath, _vertexShaderID);
		compileShader(fragmentShaderFilePath, _fragmentShaderID);

	}


	//----------------------------- Linking the shaders together -------------------------------

	void GLSLProgram::linkShaders()
	{
		//Attach our shaders to our porgram
		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);

		//Link our program
		glLinkProgram(_programID);

		//Note the different functions here: glGetProgram* Instead of glGetShader*
		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			//The max length includes the null cahracter
			//This was a <Glchar> at first, maybe chage it to a char to match above
			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

			//We don't need the program anymore
			glDeleteProgram(_programID);
			//Don't leak the shaders, delete them
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);

			//Print the error log
			std::printf("%s\n", &(errorLog[0]));
			getFatalError("shader failed to link!");
		}

		//Always detach Shaders after a successful link
		glDetachShader(_programID, _vertexShaderID);
		glDetachShader(_programID, _fragmentShaderID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
	}

	//---------------------------------------- Adding the attributes --------------------------------------
	void GLSLProgram::addAttribute(const std::string& attributeName)
	{
		glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
	}

	//---------------------------------- Getting the uniform location -----------------------------------
	GLint GLSLProgram::getUniformLocation(const std::string& uniformName)
	{
		GLint location = glGetUniformLocation(_programID, uniformName.c_str());

		if (location == GL_INVALID_INDEX)
		{
			getFatalError("Uniform " + uniformName + " Not found in shader!");
		}

		return location;
	}

	//----------------------------------- GL use function -------------------------------------
	void GLSLProgram::use()
	{
		glUseProgram(_programID);
		for (int i = 0; i < _numAttributes; i++)
		{
			glEnableVertexAttribArray(i);
		}
	}

	//------------------------------------- GL unUse -------------------------------------------
	void GLSLProgram::unUse()
	{
		glUseProgram(0);
		for (int i = 0; i < _numAttributes; i++)
		{
			glDisableVertexAttribArray(i);
		}
	}

	//-------------------------------------- Compile 1 shader, private function with error checking ------------------------------------
	void GLSLProgram::compileShader(const std::string& filePath, const GLuint id)
	{
		std::ifstream vertexFile(filePath);
		if (vertexFile.fail())
		{
			perror(filePath.c_str());
			getFatalError("Failed to open " + filePath + ". ");
		}

		std::string fileContents = " ";
		std::string line;

		while (std::getline(vertexFile, line))
		{
			fileContents += line + "\n";
		}

		vertexFile.close();

		const char* contentsPtr = fileContents.c_str();

		glShaderSource(id, 1, &contentsPtr, nullptr);

		glCompileShader(id);

		//A bit of error handling!
		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			//The max length includes the null characters
			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			//provide the info log in whatever manor you deem best. 
			//exit if failure
			glDeleteShader(id); //So it doesn't leak

			std::printf("%s\n", &(errorLog[0]));
			getFatalError("shader " + filePath + " failed to compile");
		}
	}
}