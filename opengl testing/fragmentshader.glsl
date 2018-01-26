#version 440
layout(location = 0) in vec4 pos;
uniform sampler2D shadowmap;

void main() {
	vec3 color = vec3(1,0,0);
	float depth = texture(shadowmap, pos.xy).b;
	
	if (depth < 0.9) {
		color = vec3(1,0,0);
	}
	else {
		color = vec3(0,1,0);
	}

	gl_FragColor = vec4(depth, depth, depth, 1);
}