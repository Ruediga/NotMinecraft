#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in float TexID;

uniform sampler2DArray texArray;

void main()
{
	// Create texture
	vec4 tex = texture(texArray, vec3(TexCoord.xy, TexID));

	FragColor = vec4(tex);
}