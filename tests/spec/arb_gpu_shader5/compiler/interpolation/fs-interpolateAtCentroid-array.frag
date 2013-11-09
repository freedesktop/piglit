// [config]
// expect_result: pass
// glsl_version: 1.50
// require_extensions: GL_ARB_gpu_shader5
// [end config]

#version 150
#extension GL_ARB_gpu_shader5: require

in float v1[2];
in vec2 v2[2];
in vec3 v3[2];
in vec4 v4[2];

void main()
{
	vec4 res = vec4(0);

	res += vec4(interpolateAtCentroid(v1[1]), 1, 1, 1);
	res += vec4(interpolateAtCentroid(v2[1]), 1, 1);
	res += vec4(interpolateAtCentroid(v3[1]), 1);
	res += interpolateAtCentroid(v4[1]);

	gl_FragColor = res;
}
