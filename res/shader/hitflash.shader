
uniform sampler2D u_texture;

void main() {

	vec4 color = texture2D(u_texture, gl_TexCoord[0]);

	float multiplier = step(color.a, 0.5);

	gl_FragColor = multiplier * vec4(1.0, 1.0, 1.0, 1.0);
}