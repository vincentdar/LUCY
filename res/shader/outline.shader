const float offset = 1.0 / 256.0; // 0.0039
uniform sampler2D u_texture;
uniform vec4 outline_color;

void main() {
	vec4 color = texture2D(u_texture, gl_TexCoord[0]);
	
	if (color.a > 0.0) {
		gl_FragColor = color;
	}
	else {
		float alphaTop = texture2D(u_texture, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y - offset)).a;
		float alphaBot = texture2D(u_texture, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y + offset)).a;
		float alphaLeft = texture2D(u_texture, vec2(gl_TexCoord[0].x - offset, gl_TexCoord[0].y)).a;
		float alphaRight = texture2D(u_texture, vec2(gl_TexCoord[0].x + offset, gl_TexCoord[0].y)).a;

		float a = alphaBot + alphaLeft + alphaRight + alphaTop;

		if (color.a < 1.0 && a > 0.0) {
			gl_FragColor = outline_color;
		}
		else  {
			gl_FragColor = color;
		}
	}
}