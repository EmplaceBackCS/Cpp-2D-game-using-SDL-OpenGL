#pragma once
#include <GL/glew.h>

namespace CSGengine
{
	struct Position
	{
		float x;
		float y;

		//Default constructor
		Position() : x(0.0f), y(0.0f) {}
		//Non default consturtor
		Position(float X, float Y) : x(X), y(Y) {}
	}; //position; All this does really is: Position position; Like a short cut

	struct ColorRGBA8
	{
		// Red, green, blue, alpha
		GLubyte r;
		GLubyte g;
		GLubyte b;
		//Red, blue, green, and alpha. Alpha meaning transparaency
		GLubyte a;

		//Default Constructor
		ColorRGBA8(): r(0), g(0), b(0), a(255) {}
		//Non default constructor
		ColorRGBA8(GLubyte re, GLubyte gr, GLubyte bl, GLubyte alpha) : 
			r(re), 
			g(gr), 
			b(bl), 
			a(alpha) 
		{}


		void setColor(GLubyte re, GLubyte gr, GLubyte bl, GLubyte alpha)
		{
			r = re;
			g = gr;
			b = bl;
			a = alpha;
		}
	}; // color;

	struct UV
	{
		float u;
		float v;

		//Default constructor
		UV() :u(0.0f), v(0.0f) {}
		//Non default constructor
		UV(float U, float V) : u(U), v(V) {}
	};

	struct Vertex
	{
		//This is the position struct. When you store a struct or a class
		//Inside of another struct or class, it's called compsition. This is
		//Layed out	exactly the same in memory as if we had a flaot position[2],
		//But doing it this way makes mroe sense/looks cleaner
		Position position;
		ColorRGBA8 color;

		//UV texture coordinates. A number between 0-1 For normal texture mapping
		UV uv;

		//Helper functions
		void setPosition(float x, float y)
		{
			position.x = x;
			position.y = y;
		}

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		{
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void setUV(float u, float v)
		{
			uv.u = u;
			uv.v = v;
		}
	};
}