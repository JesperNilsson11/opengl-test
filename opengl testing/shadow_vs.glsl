#version 440
layout(location = 0) in vec4 position;
layout(location = 0) out vec4 pos;
uniform mat4 mvp;

void main() {
	pos = mvp * position;
	gl_Position = mvp * position;
}