uniform mediump mat4 ModelViewProj;

layout(location = 0) in vec3 vVertexIn;
layout(location = 2) in vec4 vColorIn;
layout(location = 1) in vec2 vTextCoordIn;

out vec2 texCoord;
out vec4 spriteColor;

void main()
{
	gl_Position = ModelViewProj * vec4(vVertexIn, 1.0);
	texCoord = vTextCoordIn;
	spriteColor = vColorIn;
	
	/*
	float particleSize = xyzs.w; // because we encoded it this way.
	vec3 particleCenter_wordspace = xyzs.xyz;
	
	vec3 vertexPosition_worldspace = 
		particleCenter_wordspace
		+ CameraRight_worldspace * squareVertices.x * particleSize
		+ CameraUp_worldspace * squareVertices.y * particleSize;

	// Output position of the vertex
	gl_Position = VP * vec4(vertexPosition_worldspace, 1.0f);

	// UV of the vertex. No special space for this one.
	UV = squareVertices.xy + vec2(0.5, 0.5);
	particlecolor = color;
	*/
}
