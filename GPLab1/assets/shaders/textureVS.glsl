#version 150

in vec3 vertexPosition;
in vec2 vertexTexCoords;

out vec2 vertexTexCoordsOut;
uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(vertexPosition, 1.0);
	vertexTexCoordsOut = vertexTexCoords;
}