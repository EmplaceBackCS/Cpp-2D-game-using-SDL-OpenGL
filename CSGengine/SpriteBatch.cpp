#include "SpriteBatch.h"
#include <algorithm>

namespace CSGengine
{
	//--------------------------------------------- construcotrs/destructor -------------------------
	SpriteBatch::SpriteBatch():
		_vbo(0),
		_vao(0)
	{
	}


	SpriteBatch::~SpriteBatch()
	{
		//Always remember to delete your buffers when you are done!
		if (_vbo != 0) 
		{
			glDeleteBuffers(1, &_vbo);
		}
	}

	//----------------------------------------- Init function ------------------------------------
	//This should be called always first
	void SpriteBatch::init()
	{
		createVertexArray();
	}

	//------------------------------------------ Begin function, call it after init has been called --------------------------
	//This will prep everything up. Should be the first thing you call after init
	//The first parameter is set to GlyphSortType::TEXTURE by default, which is what we want
	void SpriteBatch::begin(GlyphSortType sortType /*= GlyphSortType::TEXTURE*/)
	{
		_sortType = sortType;

		for (unsigned int i = 0; i < _glyphs.size(); i++)
		{
			delete _glyphs[i];
		}

		//Clear will just change the size of the vector.
		//It won't clear all the memory, but we will want to use it again and this
		//Saves it for us by resizing the vector back to 0
		_renderBatches.clear();
		_glyphs.clear();
	}

	//--------------------------------------- Draw function, preping it to be rendered on the screen --------------------------
	//Call this after begin, it'll add it to the batch. It won't draw it on the screen, but prep it for drawing
	//Const and adress operator so that it won't have to make copies for everything. Since color has 4
	//Values it's going to pass and same with the vec 4's, it's faster to pass the real one
	//And make it a const so we don't change the values accidently
	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, const GLuint& texture, const float depth, const ColorRGBA8& color)
	{
		Glyph* newGlyph = new Glyph;

		newGlyph->texture = texture;
		newGlyph->depth = depth;

		//--------- Top left ---------
		newGlyph->topLeft.color = color;
		newGlyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		//--------- Bottom left ---------
		newGlyph->bottomLeft.color = color;
		newGlyph->bottomLeft.setPosition(destRect.x, destRect.y);
		newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);

		//--------- Bottom Right ---------
		newGlyph->bottomRight.color = color;
		newGlyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
		newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		//--------- Top right ---------
		newGlyph->TopRight.color = color;
		newGlyph->TopRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		newGlyph->TopRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		_glyphs.push_back(newGlyph);
	}

	//------------------------------------------- End function ----------------------
	//This will sort everything up, should be called after draw
	void SpriteBatch::end()
	{
		sortGlyphs();
		createRenderBatches();
	}

	//------------------------------------- render function ------------------------
	//Call this in the end. It should render it to the screen and finish up the last things needed
	void SpriteBatch::renderBatch()
	{
		//Bind the vertex attrib array
		glBindVertexArray(_vao);

		for (unsigned int i = 0; i < _renderBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);

			glDrawArrays(GL_TRIANGLES, _renderBatches[i].offSet, _renderBatches[i].numOfVertices);
		}

		glBindVertexArray(0);
	}

	//------------------------------ Create render batches -----------------------------
	void SpriteBatch::createRenderBatches()
	{
		std::vector<Vertex> vertices;
		//We'll reserve some memory since we know the size we want our vector
		vertices.resize(_glyphs.size() * NUM_OF_VERTICES); //6 for the number of vertices

		//If it's empty, just return so we don't do the rest of the code with an empty glyph vector
		if (_glyphs.empty())
		{
			return;
		}

		int offSet = 0;
		int cv = 0; // current vertex

		//RenderBatch tempBatch(0, 6, _glyphs[0]->texture); <--6 for 6 vertices from a trinagle
		//_renderBatches.push_back(tempBatch); We won't use this, instead we'll use emplace_back
		//This takes out the middle man, makes it faster and cleaner
		//We just take the parameter list from RenderBatch and emplace_back will do what we just did above for us
		_renderBatches.emplace_back(offSet, 6, _glyphs[0]->texture);
		vertices[cv++] = _glyphs[0]->topLeft;
		vertices[cv++] = _glyphs[0]->bottomLeft;
		vertices[cv++] = _glyphs[0]->bottomRight;
		vertices[cv++] = _glyphs[0]->bottomRight;
		vertices[cv++] = _glyphs[0]->TopRight;
		vertices[cv++] = _glyphs[0]->topLeft;

		//Increase the offSet since we need it to create the texture
		offSet += NUM_OF_VERTICES;

		//cg for current glyph
		//We are starting at 1, since we did 0 above
		for(unsigned int cg = 1; cg < _glyphs.size(); cg++)
		{
			if (_glyphs[cg]->texture != _glyphs[cg - 1]->texture)
			{
				_renderBatches.emplace_back(offSet, NUM_OF_VERTICES, _glyphs[cg]->texture);
			}
			else
			{
				_renderBatches.back().numOfVertices += NUM_OF_VERTICES;
			}
			vertices[cv++] = _glyphs[cg]->topLeft;
			vertices[cv++] = _glyphs[cg]->bottomLeft;
			vertices[cv++] = _glyphs[cg]->bottomRight;
			vertices[cv++] = _glyphs[cg]->bottomRight;
			vertices[cv++] = _glyphs[cg]->TopRight;
			vertices[cv++] = _glyphs[cg]->topLeft;
			//Increase the offSet since we used it
			offSet += NUM_OF_VERTICES;
		}

		
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		//Since we know it isn't empty by this point, we can create our vertex buffer 
		//We can orphan the buffer, It'll be faster
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//Upload the data now
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		//Unbind the buffer with 0
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	//--------------------------------- Create the vertex array ---------------------
	//This will encapsulate all of the state that we need to do all the rendering in openGL
	void SpriteBatch::createVertexArray()
	{
		//Should only generate if the vertex array object is 0 (empty)
		if (_vao == 0)
		{
			//Generate our vertex array object
			glGenVertexArrays(1, &_vao);
		}
		
		//Once we generate it, bind it
		glBindVertexArray(_vao);

		//Shoud only generate if the vertex buffer object is 0 (empty)
		if (_vbo == 0)
		{
			glGenBuffers(1, &_vbo);
		}
		//Bind the buffer object once we generate it
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		/*Enable it now that we know what we want to draw after it's binded*/
		//Tell openGL that we want to use the first arrtribute array. We only
		//Need one array right now since we are using position
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);


		//This is the position attribute pointer
		glVertexAttribPointer(0,
			2,
			GL_FLOAT, GL_FALSE,
			sizeof(Vertex),/*Casting this to a void pointer to make meet the requirements*/
			(void*)offsetof(Vertex,
			position));

		//This is the color attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		//This is the UV attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		//0 means unbind it. We unbind it once we are done with it
		glBindVertexArray(0);

	}

	//----------------------------------------- Sort glyphs -----------------------------------
	void SpriteBatch::sortGlyphs()
	{
		switch (_sortType)
		{
		case CSGengine::GlyphSortType::BACK_TO_FRONT:
			////Stable sort makes it so that 2 elements that are equal will retain the same order
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);
			break;
		case CSGengine::GlyphSortType::FRONT_TO_BACK:
			////Stable sort makes it so that 2 elements that are equal will retain the same order
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
			break;
		case CSGengine::GlyphSortType::TEXTURE:
			////Stable sort makes it so that 2 elements that are equal will retain the same order
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
			break;
		default:
			break;
		}

		////Stable sort makes it so that 2 elements that are equal will retain the same order
		//std::stable_sort()
	}

	//------------------------------------------- Static functions -------------------------------------
	//These will keep us from drawing more then 1 batch when we don't need it.
	//Use these in the sort glyph function in the switch case statment
	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
	{
		return (a->depth < b->depth);
	}
	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b)
	{
		return (a->depth > b->depth);
	}
	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
	{
		return (a->texture < b->texture);
	}
	//------------------------------------ End of static functions --------------------------------------

}