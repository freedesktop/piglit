// [config]
// expect_result: fail
// glsl_version: 3.30
// require_extensions: GL_ARB_bindless_texture
// [end config]

#version 330
#extension GL_ARB_bindless_texture: require

// The ARB_bindless_texture spec says:
//
//  "Modify Section 4.3.7, Interface Blocks, p. 38"
//
//  "If these layout qualifiers are applied to other types of default block
//   uniforms, or variables with non-uniform storage, a compile-time error
//   will be generated."

layout (bound_sampler) uint i;

void main()
{
}
