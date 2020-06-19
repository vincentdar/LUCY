uniform sampler2D u_texture;

void main() {

	vec4 color = texture2D(u_texture, vec2(gl_TexCoord[0].st));

	if (color.a < 0.5) {
		gl_FragColor = color;
	}
	else {
		gl_FragColor = 1 * vec4(1.0, 1.0, 1.0, 1.0);
	}

}