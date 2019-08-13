/* Copyright 2019 Timothy Arceri
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "piglit-util-gl.h"

PIGLIT_GL_TEST_CONFIG_BEGIN

	config.supports_gl_compat_version = 20;
	config.window_visual = PIGLIT_GL_VISUAL_RGBA | PIGLIT_GL_VISUAL_DOUBLE;
	config.khr_no_error_support = PIGLIT_HAS_ERRORS;

PIGLIT_GL_TEST_CONFIG_END

static const char *const vs_source =
"#version 150\n"
"void main() { gl_Position = vec4(0.0); }\n";

/* From the ARB_shading_language_include spec:
 *
 *    "A path is invalid if:
 *
 *    * <path> contains any characters not listed in Section 3.1
 *      "Character Set", or the double quote character, or angled
 *      brackets, or any white space characters other than the space
 *      character,
 *    * <path> has consecutive forward slashes ( // ); "/foo//bar" is
 *      not valid (zero length tokens are not allowed),
 *    * <path> ends with a forward slash ( / ), or
 *    * <path> contains no characters."
 */
#define num_invalid_paths 8
const char* const invalid_paths[num_invalid_paths] =
 { "path", "/path/to	include", "/path$/to",
   "/path/\"to\"", "/path/<to>", "/path//to",
   "/path/to/", ""
 };

static bool
test_api_errors(void)
{
	char *test_name;
	bool pass = true;
	bool invalid_path_result;

	/* clear any prev errors */
	while (glGetError())
		;

	/* Test passing invalid type enum to glNamedStringARB() */
	glNamedStringARB(GL_INVALID_OPERATION, -1 , "/path", -1, "");
	test_name = "Test glNamedStringARB() invalid type enum";
	if (!piglit_check_gl_error(GL_INVALID_VALUE)) {
		piglit_report_subtest_result(PIGLIT_FAIL, "%s", test_name);
		pass = false;
	} else
		piglit_report_subtest_result(PIGLIT_PASS, "%s", test_name);

	/* Test passing NULL name to glNamedStringARB() */
	glNamedStringARB(GL_SHADER_INCLUDE_ARB, -1 , NULL, -1, "");
	test_name = "Test glNamedStringARB() NULL name";
	if (!piglit_check_gl_error(GL_INVALID_VALUE)) {
		piglit_report_subtest_result(PIGLIT_FAIL, "%s", test_name);
		pass = false;
	} else
		piglit_report_subtest_result(PIGLIT_PASS, "%s", test_name);

	/* Test passing NULL include string to glNamedStringARB() */
	glNamedStringARB(GL_SHADER_INCLUDE_ARB, -1 , "/path", -1, NULL);
	test_name = "Test glNamedStringARB() NULL include string";
	if (!piglit_check_gl_error(GL_INVALID_VALUE)) {
		piglit_report_subtest_result(PIGLIT_FAIL, "%s", test_name);
		pass = false;
	} else
		piglit_report_subtest_result(PIGLIT_PASS, "%s", test_name);

	/* Test invalid include paths passed to glNamedStringARB() */
	test_name = "Test glNamedStringARB() invalid paths";
	invalid_path_result = true;
	for (unsigned i = 0; i < num_invalid_paths; i++) {
		glNamedStringARB(GL_SHADER_INCLUDE_ARB, -1 , invalid_paths[i], -1, "");
		if (!piglit_check_gl_error(GL_INVALID_VALUE)) {
			invalid_path_result = false;
			break;
		}
	}
	piglit_report_subtest_result(invalid_path_result ? PIGLIT_PASS : PIGLIT_FAIL, "%s", test_name);
	pass &= invalid_path_result;

	/* Test passing NULL name string to glDeleteNamedStringARB() */
	glDeleteNamedStringARB(-1 , NULL);
	test_name = "Test glDeleteNamedStringARB() NULL name";
	if (!piglit_check_gl_error(GL_INVALID_VALUE)) {
		piglit_report_subtest_result(PIGLIT_FAIL, "%s", test_name);
		pass = false;
	} else
		piglit_report_subtest_result(PIGLIT_PASS, "%s", test_name);

	/* Test invalid include paths passed to glDeleteNamedStringARB() */
	test_name = "Test glDeleteNamedStringARB() invalid paths";
	invalid_path_result = true;
	for (unsigned i = 0; i < num_invalid_paths; i++) {
		glDeleteNamedStringARB(-1 , invalid_paths[i]);
		if (!piglit_check_gl_error(GL_INVALID_VALUE)) {
			invalid_path_result = false;
			break;
		}
	}
	piglit_report_subtest_result(invalid_path_result ? PIGLIT_PASS : PIGLIT_FAIL, "%s", test_name);
	pass &= invalid_path_result;

	/* Test deletion of a path that doesn't have a string attached to it */
	glDeleteNamedStringARB(-1 , "/path");
	test_name = "Test glDeleteNamedStringARB() no string attached to path";
	if (!piglit_check_gl_error(GL_INVALID_OPERATION)) {
		piglit_report_subtest_result(PIGLIT_FAIL, "%s", test_name);
		pass = false;
	} else
		piglit_report_subtest_result(PIGLIT_PASS, "%s", test_name);

	/* Test compile shader with invalid shader object name.
	 *
	 * From the ARB_shading_language_include spec:
	 *
	 *   "An INVALID_OPERATION error is generated if <shader> is not the
	 *   name of a valid shader object generated by CreateShader."
	 */
	glCompileShaderIncludeARB(1, 0, NULL, NULL);
	test_name = "Test glCompileShaderIncludeARB() invalid shader object name";
	if (!piglit_check_gl_error(GL_INVALID_OPERATION)) {
		piglit_report_subtest_result(PIGLIT_FAIL, "%s", test_name);
		pass = false;
	} else
		piglit_report_subtest_result(PIGLIT_PASS, "%s", test_name);

	/*  From the ARB_shading_language_include spec:
	 *
	 *     "An INVALID_VALUE error will be generated under any of the
	 *     following conditions:
	 *
	 *        - <count> is greater than zero and <path> is NULL, or any
	 *          of the pointers path[0] .. path[<count>-1] is NULL."
	 */
	GLuint shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader, 1, &vs_source, NULL);
	glCompileShaderIncludeARB(shader, 1, NULL, NULL);
	test_name = "Test glCompileShaderIncludeARB() non-zero count and NULL path";
	if (!piglit_check_gl_error(GL_INVALID_VALUE)) {
		piglit_report_subtest_result(PIGLIT_FAIL, "%s", test_name);
		pass = false;
	} else
		piglit_report_subtest_result(PIGLIT_PASS, "%s", test_name);

	const char* const null_path[2] = { "/valid path", NULL };
	glCompileShaderIncludeARB(shader, 2, null_path, NULL);
	test_name = "Test glCompileShaderIncludeARB() NULL in path array";
	if (!piglit_check_gl_error(GL_INVALID_VALUE)) {
		piglit_report_subtest_result(PIGLIT_FAIL, "%s", test_name);
		pass = false;
	} else
		piglit_report_subtest_result(PIGLIT_PASS, "%s", test_name);

	/* Test invalid include paths passed to glCompileShaderIncludeARB() */
	test_name = "Test glCompileShaderIncludeARB() invalid paths";
	invalid_path_result = true;
	for (unsigned i = 0; i < num_invalid_paths; i++) {
		glCompileShaderIncludeARB(shader, 1, &invalid_paths[i], NULL);
		if (!piglit_check_gl_error(GL_INVALID_VALUE)) {
			invalid_path_result = false;
			break;
		}
	}
	piglit_report_subtest_result(invalid_path_result ? PIGLIT_PASS : PIGLIT_FAIL, "%s", test_name);
	pass &= invalid_path_result;

	/*  From the ARB_shading_language_include spec:
	 *
	 *     "An INVALID_OPERATION error is generated if CompileShaderIncludeARB
	 *     is executed between Begin and the corresponding End."
	 */
	glBegin(GL_POINTS);
	glCompileShaderIncludeARB(shader, 0, NULL, NULL);
	glEnd();
	test_name = "Test glCompileShaderIncludeARB() between glBegin/End()";
	if (!piglit_check_gl_error(GL_INVALID_OPERATION)) {
		piglit_report_subtest_result(PIGLIT_FAIL, "%s", test_name);
		pass = false;
	} else
		piglit_report_subtest_result(PIGLIT_PASS, "%s", test_name);

	/*  From the ARB_shading_language_include spec:
	 *
	 *     "An INVALID_VALUE error will be generated under any of the following
	 *     conditions:
	 *
	 *        - <name> is NULL."
	 */
	int string_len;
	glGetNamedStringivARB(-1, NULL, GL_NAMED_STRING_LENGTH_ARB, &string_len);
	test_name = "Test glGetNamedStringivARB() NULL name";
	if (!piglit_check_gl_error(GL_INVALID_VALUE)) {
		piglit_report_subtest_result(PIGLIT_FAIL, "%s", test_name);
		pass = false;
	} else
		piglit_report_subtest_result(PIGLIT_PASS, "%s", test_name);

	/* Test invalid include paths passed to glGetNamedStringivARB() */
	test_name = "Test glGetNamedStringivARB() invalid paths";
	invalid_path_result = true;
	for (unsigned i = 0; i < num_invalid_paths; i++) {
		glGetNamedStringivARB(-1, invalid_paths[i], GL_NAMED_STRING_LENGTH_ARB, &string_len);
		if (!piglit_check_gl_error(GL_INVALID_VALUE)) {
			invalid_path_result = false;
			break;
		}
	}
	piglit_report_subtest_result(invalid_path_result ? PIGLIT_PASS : PIGLIT_FAIL, "%s", test_name);
	pass &= invalid_path_result;

	/* Test a path that doesn't have a string attached to it */
	glGetNamedStringivARB(-1 , "/path", GL_NAMED_STRING_LENGTH_ARB, &string_len);
	test_name = "Test glGetNamedStringivARB() no string attached to path";
	if (!piglit_check_gl_error(GL_INVALID_OPERATION)) {
		piglit_report_subtest_result(PIGLIT_FAIL, "%s", test_name);
		pass = false;
	} else
		piglit_report_subtest_result(PIGLIT_PASS, "%s", test_name);

	/*  From the ARB_shading_language_include spec:
	 *
	 *     "An INVALID_VALUE error will be generated under any of the following
	 *     conditions:
	 *
	 *        - <name> is NULL."
	 */
	int buffser_size = 1028;
	char string[1028];
	glGetNamedStringARB(-1, NULL, buffser_size, &string_len, string);
	test_name = "Test glGetNamedStringARB() NULL name";
	if (!piglit_check_gl_error(GL_INVALID_VALUE)) {
		piglit_report_subtest_result(PIGLIT_FAIL, "%s", test_name);
		pass = false;
	} else
		piglit_report_subtest_result(PIGLIT_PASS, "%s", test_name);

	/* Test invalid include paths passed to glGetNamedStringARB() */
	test_name = "Test glGetNamedStringARB() invalid paths";
	invalid_path_result = true;
	for (unsigned i = 0; i < num_invalid_paths; i++) {
		glGetNamedStringARB(-1, invalid_paths[i], buffser_size, &string_len, string);
		if (!piglit_check_gl_error(GL_INVALID_VALUE)) {
			invalid_path_result = false;
			break;
		}
	}
	piglit_report_subtest_result(invalid_path_result ? PIGLIT_PASS : PIGLIT_FAIL, "%s", test_name);
	pass &= invalid_path_result;

	/* Test a path that doesn't have a string attached to it */
	glGetNamedStringARB(-1 , "/path", buffser_size, &string_len, string);
	test_name = "Test glGetNamedStringARB() no string attached to path";
	if (!piglit_check_gl_error(GL_INVALID_OPERATION)) {
		piglit_report_subtest_result(PIGLIT_FAIL, "%s", test_name);
		pass = false;
	} else
		piglit_report_subtest_result(PIGLIT_PASS, "%s", test_name);

	return pass;
}

enum piglit_result
piglit_display(void)
{
	return PIGLIT_PASS;
}

void
piglit_init(int argc, char **argv)
{
	bool pass;

	piglit_require_gl_version(20);
	piglit_require_extension("GL_ARB_shading_language_include");

	pass = test_api_errors();

	piglit_report_result(pass ? PIGLIT_PASS : PIGLIT_FAIL);
}
