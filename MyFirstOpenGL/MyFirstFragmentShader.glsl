#version 440 core

out vec4 fragColor;

void main() {
	fragColor = vec4(1.0, 0.0, 0.0, 1.0);

	if(gl_FragCoord.x > 320.0f)
	{
		fragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	}
	else
	{
		fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}
}