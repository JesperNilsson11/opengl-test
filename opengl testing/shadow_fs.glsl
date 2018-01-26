#version 440
layout(location = 0) in vec4 pos;
layout(location = 0) out float fragmentdepth;

void main() {
	fragmentdepth = pos.z;
}