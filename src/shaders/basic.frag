
#version 460 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec4 newColor;

void main() {
	vec4 texColor1 = texture(texture1, texCoord);
	texColor1 = mix(texColor1, newColor, 0.5);
	vec4 texColor2 = texture(texture2, texCoord);
	FragColor = mix(texColor1, texColor2, 0.2);
}
