uniform sampler2D u_texture;

float invis_rate = 0.3;

void main() {
	vec4 color = texture2D(u_texture, gl_TexCoord[0].st);

	if (color.a <= 0.5) {
		discard;
	}
	else {
		color.a = invis_rate;
		gl_FragColor = color;
	}
}