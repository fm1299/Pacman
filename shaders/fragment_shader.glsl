#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
uniform vec3 vertexColor;
uniform sampler2D texture1;
void main()
{
	FragColor = vec4(vertexColor,1.0f);//texture(texture1,TexCoord);
}