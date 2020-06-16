
uniform sampler2D u_texture;

void main() {

	vec4 color = texture2D(u_texture, gl_TexCoord[0]);

	float multiplier = 1;
	if (color.a < 0.5) {
		multiplier = 0;
	}

	gl_FragColor = multiplier * vec4(1.0, 1.0, 1.0, 1.0);
}