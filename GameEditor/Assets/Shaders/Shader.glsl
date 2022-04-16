#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_textCoord;
layout(location = 3) in float a_textIndex;


uniform mat4 u_transform;
uniform mat4 u_projection;
uniform mat4 u_view;

out vec2 v_textCoord;
flat out float v_textIndex;
out vec4 v_color;

void main()
{
	gl_Position =  u_projection * u_view * u_transform * vec4(a_position, 1.0);
	//gl_Position =  vec4(a_position, 1.0);
	v_textCoord = a_textCoord;
	v_textIndex = a_textIndex;
	v_color = a_color;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_textCoord;
in vec4 v_color;
flat in float v_textIndex;


uniform sampler2D u_textures[32];

void main()
{
	vec2 uv;
	vec2 GridWidth = vec2(20, 20);
	vec2 TextureSize = vec2(256,256);
	vec2 texel = v_textCoord * TextureSize;
	
	if (true)
		uv = (floor(texel) + vec2(0.5,0.5)) / TextureSize;
	else
		uv = v_textCoord;
	
	vec2 texelEdge = step(mod(texel,vec2(1.0,1.0)), GridWidth);
	float isGrid = max(texelEdge.x, texelEdge.y);

	color = texture( u_textures[int(v_textIndex)], v_textCoord) * v_color;

	//color = vec4(v_textCoord, 0,1);
	//color = vec4(1,1,1,1);

}