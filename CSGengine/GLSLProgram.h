#pragma once
#include <iostream>
#include <vector>
#include "Errors.h"
#include <GL/glew.h>
#include<fstream>

namespace CSGengine
{

	class GLSLProgram
	{
		public:
			GLSLProgram();
			virtual ~GLSLProgram() {}

			//Compiler functions
			void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
			void linkShaders();
			void addAttribute(const std::string& attributeName);
			void use();
			void unUse();

			GLint getUniformLocation(const std::string& uniformName);

		private:
			//Compile a shader, different from the public one which compiles both once it goes through all the error checking
			void compileShader(const std::string& filePath, const GLuint id);

			//Ints
			int _numAttributes;

			//Glu ints
			GLuint _programID;
			GLuint _vertexShaderID;
			GLuint _fragmentShaderID;
	};

}