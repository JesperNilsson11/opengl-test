#version 440
layout(location = 0) in vec4 position;
layout(location = 0) out vec4 pos;

void main() {
	pos = position;
	gl_Position = position;
}