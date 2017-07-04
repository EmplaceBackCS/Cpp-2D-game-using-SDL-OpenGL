#include "Sprite.h"
#include "Vertex.h"
#include <cstddef>

namespace CSGengine
{
	//----------------------------------------------- Draw the sprite ----------------------------------
	void Sprite::draw()
	{
		//We don't want to unbind textures, because we can use then once! 
		glBindTexture(GL_TEXTURE_2D, _texture.id);

		/*Bind to draw it*/
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		/*Enable it now that we know what we want to draw after it's binded*/
		//Tell openGL that we want to use the first arrtribute array. We only
		//Need one array right now since we are using position
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);


		//This is the position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),/*Casting this to a void pointer to make meet the requirements*/(void*)offsetof(Vertex, position));
		//This is the color attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		//This is the UV attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		/*Draw the data now*/
		glDrawArrays(GL_TRIANGLES, 0, 6);

		/*Disable it once it's done*/
		//Optional, but still good so we can free up the space
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		/*Unbind it at the end, delete it so the memory is freed up*/
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//-------------------------- Init the sprite, x and y coord, width, height of the sprite ---------------------
	void Sprite::init(float x, float y, float width, float height, std::string texturePath)
	{
		_x = x;
		_y = y;
		_width = width;
		_height = height;


		_texture = ResourceManager::getTexture(texturePath);

		if (_vboID == 0)
		{
			glGenBuffers(1, &_vboID);
		}

		Vertex verTexData[_SIZE];
		/*First triangle of the square*/
		verTexData[0].setPosition(x + width, y + width);
		verTexData[0].setUV(1.0f, 1.0f);

		verTexData[1].setPosition(x, y + height);
		verTexData[1].setUV(0.0f, 1.0f);

		verTexData[2].setPosition(x, y);
		verTexData[2].setUV(0.0f, 0.0f);

		/*Second triangle of the square*/
		verTexData[3].setPosition(x, y);
		verTexData[3].setUV(0.0f, 0.0f);

		verTexData[4].setPosition(x + width, y);
		verTexData[4].setUV(1.0f, 0.0f);

		verTexData[5].setPosition(x + width, y + height);
		verTexData[5].setUV(1.0f, 1.0f);

		//Just coloring the sprite for now all one color. For testing, will chage later
		//The commented out ones are from before we made the function in the struct
		for (int i = 0; i < _SIZE; i++)
		{
			verTexData[i].setColor(255, 0, 255, 255);
			//verTexData[i].color.r = 255;
			//verTexData[i].color.g = 0;
			//verTexData[i].color.b = 255;
			//verTexData[i].color.a = 255;
		}

		//The commented out ones are from before we made the function in the struct
		verTexData[1].setColor(0, 0, 255, 255);
		//verTexData[1].color.r = 0;
		//verTexData[1].color.g = 0;
		//verTexData[1].color.b = 255;
		//verTexData[1].color.a = 255;

		verTexData[4].setColor(0, 255, 0, 255);


		/*Bind the ID that we made, basically storing it somewhere*/
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verTexData), verTexData, GL_STATIC_DRAW);

		//Unbind the VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}