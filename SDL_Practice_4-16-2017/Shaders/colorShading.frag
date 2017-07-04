#version 130
//

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

//This is the 3 compoent float vector that gets outputted on the screen.
//For each Pixel.
out vec4 color;

//uniform float time;
uniform sampler2D mySampler;

void main() 
{
	vec4 textureColor= texture(mySampler, fragmentUV);

	//For the colors, you just have to do (cos(x) + 1.0 * 0.5
	//Just hardcoding the color to red to test. Red, green, blue, max value 1
	//Can change the values a bit, using time and position you can get some nice colors!
	
	//color = textureColor * fragmentColor;
	
	//color = vec4(fragmentColor.r * (cos(fragmentPosition.x * 4.0 + time) + 1.0)* 0.5,
	//			fragmentColor.g * (cos(fragmentPosition.x * 8.0 + time) + 1.0) * 0.5,
	//			fragmentColor.b * (cos(fragmentPosition.x * 2.4 + time) + 1.0) * 0.5, //fragmentColor.a) * textureColor; <-- Was just to give the sprite a cool color //effect
		
	//No effect now
	color = fragmentColor * textureColor;

	
}