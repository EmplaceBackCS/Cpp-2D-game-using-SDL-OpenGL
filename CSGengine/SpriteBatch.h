#pragma once
#include <GL/glew.h>
#include "Vertex.h"
#include <glm/glm.hpp>
#include <vector>

namespace CSGengine
{
	//--------------------------- Enum class GlyphSortType -----------------
	enum class GlyphSortType
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	//----------------------------- Glyph Struct ----------------------------
	//Just using this struct to sort our glyphs
	struct Glyph
	{
		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex TopRight;
		Vertex bottomRight;
	};

	//-------------------------- Render batch class ----------------------------
	class RenderBatch 
	{
		public:
			//Constuctors
			RenderBatch(GLuint OffSet, GLuint NumOfVertices, GLuint Texture):
				offSet(OffSet),
				numOfVertices(NumOfVertices),
				texture(Texture)
			{}

			virtual ~RenderBatch() {}

			GLuint offSet;
			GLuint numOfVertices;
			GLuint texture;

		private:
	};


	//------------------------- Sprite batch class --------------------------
	class SpriteBatch
	{
		public:
			//Constructors
			SpriteBatch();
			virtual ~SpriteBatch();

			//Init all needed things. This should be called whenever you initlize other things, such as init SDL
			void init();
			
			//This will prep everything up. Should be the first thing you call after init
			void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);

			//Call this after begind, it'll add it to the batch. It won't draw it on the screen, but prep it for drawing
			//Const and adress operator so that it won't have to make copies for everything. Since color has 4
			//Values it's going to pass and same with the vec 4's, it's faster to pass the real one
			//And make it a const so we don't change the values accidently
			void draw(const glm::vec4& destRect, const glm::vec4& uvRect, const GLuint& texture, const float depth, const ColorRGBA8& color);

			//This will sort everything up, should be called after draw
			void end();
	
			//Call this in the end. It should render it to the screen and finish up the last things needed
			void renderBatch();

		private:
			//-------------- Private functions ---------

			void createRenderBatches();

			//Create out vertex array
			void createVertexArray();

			//Sort our glyphs
			void sortGlyphs();


			static bool compareFrontToBack(Glyph* a, Glyph* b);
			static bool compareBackToFront(Glyph* a, Glyph* b);
			static bool compareTexture(Glyph* a, Glyph* b);
			//-------------- End private functions

			//GLuint varabiles	
			//vertex buffer object
			GLuint _vbo; 

			//vertex array object
			GLuint _vao;

			//vector varabiles
			//Our glyph vector
			std::vector<Glyph*> _glyphs;
			std::vector<RenderBatch> _renderBatches;
			//Glyph sort type variables
			GlyphSortType _sortType;

			//Const varaibles
			static const unsigned short NUM_OF_VERTICES = 6;
	};
}