#version 300 es

/* [config]
 * expect_result: fail
 * glsl_version: 3.00
 * [end config]
 *
 * Page 8 (page 14 of the PDF) of the OpenGL ES Shading Language 3.00 spec
 * says:
 *
 *     "Inside comments, the character set is extended to allow any byte
 *     values to be used but with the exception that a byte with the value
 *     zero is always interpreted as the end of the string. The character
 *     encoding is assumed to be UTF-8 but no checking is performed for
 *     invalid characters."
 *
 * Further discussion in Khronos has determined that UTF-8 in unused
 * preprocessor defines should also be allowed.
 */

#define eat_sushi_with_chopsticks 箸で寿司を食べます。

void main()
{
    float eat_sushi_with_chopsticks = 0;
    gl_Position = vec4(eat_sushi_with_chopsticks);
}
