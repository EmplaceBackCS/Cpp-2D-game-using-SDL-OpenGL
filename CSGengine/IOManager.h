#pragma once
#include <vector>
#include <string>
#include <fstream> 
namespace CSGengine
{
	//No constructors needed as this class will all be static and only be made once
	class IOManager
	{
	public:
		//Buffer is just another name for an array

		static bool ReadFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);

	};
}
