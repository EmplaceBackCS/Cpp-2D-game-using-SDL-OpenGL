#include "IOManager.h"

namespace CSGengine
{
	//--------------------------- Static function to get our file where our images will load from ---------------------------
	bool IOManager::ReadFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
	{
		//We're reading it in binary so we get the exact file
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail())
		{
			perror(filePath.c_str());
			return false;
		}

		//We need to fix the vector to be the correct size, since it is 0 when this function is called
		//We'll use seek to the end function
		file.seekg(0, std::ios::end);

		//Now we'll get the file size
		//The tellg will return an int that will say how many bytes we have passed
		std::streamoff fileSize = file.tellg();

		//Beg for begning, so we are back at the start of the file
		file.seekg(0, std::ios::beg);

		//To reduce the file size by any header bytes that might be in here 
		fileSize -= file.tellg();

		//re size the buffer argument
		buffer.resize(fileSize);

		//We are using the first subscript of our vector and it's adress to treat it like a pointer. A neat little trick
		// We are pretending it's a buffer of char's, so we will use (char *), so that our paramater list can have an unsigned char as a parameter
		file.read((char *)&(buffer[0]), fileSize);
		//Close the file once we are done!
		file.close();

		return true;
	}
}
