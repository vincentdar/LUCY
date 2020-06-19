uniform sampler2D u_texture;

void main() {
	vec4 texel = texture2D(u_texture, gl_TexCoord[0].st);

	// Grayscale
	float avg = (texel.r + texel.g + texel.b) / 3.0;
	vec4 grayscale = vec4(avg, avg, avg, 1.0);

	gl_FragColor = grayscale * vec4(0.5, 0.5, 0.5, 1.0);;
}