/*
 * Copyright © 2020 Intel Corporation
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
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Author:
 *    Eleni Maria Stea <estea@igalia.com>
 */

#ifndef PARAMS_H
#define PARAMS_H

#include "interop.h"

uint32_t w;
uint32_t h;
uint32_t d = 1;
uint32_t num_samples = 1;
uint32_t num_levels = 1;
uint32_t num_layers = 1;
VkFormat color_format = VK_FORMAT_R32G32B32A32_SFLOAT;
VkFormat depth_format = VK_FORMAT_D32_SFLOAT;
VkImageUsageFlagBits color_usage = VK_IMAGE_USAGE_SAMPLED_BIT |
				   VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
				   VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
VkImageUsageFlagBits depth_usage = VK_IMAGE_USAGE_SAMPLED_BIT |
				   VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
				   VK_IMAGE_USAGE_TRANSFER_DST_BIT |
				   VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
VkImageTiling color_tiling = VK_IMAGE_TILING_OPTIMAL;
VkImageTiling depth_tiling = VK_IMAGE_TILING_OPTIMAL;
VkImageLayout color_in_layout = VK_IMAGE_LAYOUT_UNDEFINED;
VkImageLayout color_end_layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
VkImageLayout depth_in_layout = VK_IMAGE_LAYOUT_UNDEFINED;
VkImageLayout depth_end_layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

const struct format_mapping vk_gl_format[] =
{
	{ "RGBA 4 UNORM linear", GL_RGBA4, VK_FORMAT_R4G4B4A4_UNORM_PACK16, FLOAT_FS, 4, 4, 4, 4,
		VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					VK_IMAGE_USAGE_TRANSFER_DST_BIT },
	{ "RGBA 4 UNORM optimal", GL_RGBA4, VK_FORMAT_R4G4B4A4_UNORM_PACK16, FLOAT_FS, 4, 4, 4, 4,
		VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					 VK_IMAGE_USAGE_TRANSFER_DST_BIT },

	{ "RGB 5 A1 UNORM linear", GL_RGB5_A1, VK_FORMAT_R5G5B5A1_UNORM_PACK16, FLOAT_FS, 5, 5, 5, 1,
		VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					VK_IMAGE_USAGE_TRANSFER_DST_BIT },
	{ "RGB 5 A1 UNORM optimal",  GL_RGB5_A1, VK_FORMAT_R5G5B5A1_UNORM_PACK16, FLOAT_FS, 5, 5, 5, 1,
		VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					 VK_IMAGE_USAGE_TRANSFER_DST_BIT },

	{ "RGBA 8 UNORM linear", GL_RGBA8, VK_FORMAT_R8G8B8A8_UNORM, FLOAT_FS, 8, 8, 8, 8,
		VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					VK_IMAGE_USAGE_TRANSFER_DST_BIT },
	{ "RGBA 8 UNORM optimal", GL_RGBA8, VK_FORMAT_R8G8B8A8_UNORM, FLOAT_FS, 8, 8, 8, 8,
		VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					 VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					 VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT },

	{ "RGBA 8 SNORM linear", GL_RGBA8_SNORM, VK_FORMAT_R8G8B8A8_SNORM, INT_FS, 8, 8, 8, 8,
		VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					VK_IMAGE_USAGE_TRANSFER_DST_BIT },
	{ "RGBA 8 SNORM optimal", GL_RGBA8_SNORM, VK_FORMAT_R8G8B8A8_SNORM, INT_FS, 8, 8, 8, 8,
		VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					 VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					 VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT },

	{ "RGBA 8 SRGB linear", GL_SRGB8_ALPHA8, VK_FORMAT_R8G8B8A8_SRGB, FLOAT_FS, 8, 8, 8, 8,
		VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					VK_IMAGE_USAGE_TRANSFER_DST_BIT },
	{ "RGBA 8 SRGB optimal", GL_SRGB8_ALPHA8, VK_FORMAT_R8G8B8A8_SRGB, FLOAT_FS, 8, 8, 8, 8,
		VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					 VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					 VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT },

	{ "RGBA 8 INT linear", GL_RGBA8I, VK_FORMAT_R8G8B8A8_SINT, INT_FS , 8, 8, 8, 8,
		VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					VK_IMAGE_USAGE_TRANSFER_DST_BIT },
	{ "RGBA 8 INT optimal", GL_RGBA8I, VK_FORMAT_R8G8B8A8_SINT, INT_FS , 8, 8, 8, 8,
		VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					 VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					 VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT },

	{ "RGBA 8 UINT linear", GL_RGBA8UI, VK_FORMAT_R8G8B8A8_UINT, UINT_FS, 8, 8, 8, 8,
		VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					VK_IMAGE_USAGE_TRANSFER_DST_BIT },
	{ "RGBA 8 UINT optimal", GL_RGBA8UI, VK_FORMAT_R8G8B8A8_UINT, UINT_FS, 8, 8, 8, 8,
		VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					 VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					 VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT },

	{ "RGB 10 A2 UNORM linear", GL_RGB10_A2, VK_FORMAT_A2R10G10B10_UNORM_PACK32, FLOAT_FS, 10, 10, 10, 2,
		VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					VK_IMAGE_USAGE_TRANSFER_DST_BIT },
	{ "RGB 10 A2 UNORM optimal", GL_RGB10_A2, VK_FORMAT_A2R10G10B10_UNORM_PACK32, FLOAT_FS, 10, 10, 10, 2,
		VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					 VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					 VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT },

	{ "RGB 10 A2 UINT linear", GL_RGB10_A2UI, VK_FORMAT_A2R10G10B10_UINT_PACK32, UINT_FS, 10, 10, 10, 2,
		VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					VK_IMAGE_USAGE_TRANSFER_DST_BIT },
	{ "RGB 10 A2 UINT optimal", GL_RGB10_A2UI, VK_FORMAT_A2R10G10B10_UINT_PACK32, UINT_FS, 10, 10, 10, 2,
		VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					 VK_IMAGE_USAGE_TRANSFER_DST_BIT },

	{ "RGBA 12 UNORM linear", GL_RGBA12, VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16, FLOAT_FS, 12, 12, 12, 12,
		VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					VK_IMAGE_USAGE_TRANSFER_DST_BIT },
	{ "RGBA 12 UNORM optimal", GL_RGBA12, VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16, FLOAT_FS, 12, 12, 12, 12,
		VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					 VK_IMAGE_USAGE_TRANSFER_DST_BIT },

	{ "RGBA 16 UNORM linear", GL_RGBA16, VK_FORMAT_R16G16B16A16_UNORM, FLOAT_FS, 16, 16, 16, 16,
		VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT },
	{ "RGBA 16 UNORM optimal", GL_RGBA16, VK_FORMAT_R16G16B16A16_UNORM, FLOAT_FS, 16, 16, 16, 16,
		VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					 VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					 VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT },

	{ "RGBA 16 SNORM linear", GL_RGBA16_SNORM, VK_FORMAT_R16G16B16A16_SNORM, INT_FS, 16, 16, 16, 16,
		VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT },
	{ "RGBA 16 SNORM optimal", GL_RGBA16_SNORM, VK_FORMAT_R16G16B16A16_SNORM, INT_FS, 16, 16, 16, 16,
		VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					 VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					 VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT },

	{ "RGBA 16 SFLOAT linear", GL_RGBA16F, VK_FORMAT_R16G16B16A16_SFLOAT, FLOAT_FS, 16, 16, 16, 16,
		VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT },
	{ "RGBA 16 SFLOAT optimal", GL_RGBA16F, VK_FORMAT_R16G16B16A16_SFLOAT, FLOAT_FS, 16, 16, 16, 16,
		VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					 VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					 VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT },

	{ "RGBA 16 INT linear", GL_RGBA16I, VK_FORMAT_R16G16B16A16_SINT, INT_FS, 16, 16, 16, 16,
		VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT },
	{ "RGBA 16 INT optimal", GL_RGBA16I, VK_FORMAT_R16G16B16A16_SINT, INT_FS, 16, 16, 16, 16,
		VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					 VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					 VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT },

	{ "RGBA 16 UINT linear", GL_RGBA16UI, VK_FORMAT_R16G16B16A16_UINT, UINT_FS, 16, 16, 16, 16,
		VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT },
	{ "RGBA 16 UINT optimal", GL_RGBA16UI, VK_FORMAT_R16G16B16A16_UINT, UINT_FS, 16, 16, 16, 16,
		VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					 VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					 VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT },

	{ "RGBA 32 SFLOAT linear", GL_RGBA32F, VK_FORMAT_R32G32B32A32_SFLOAT, FLOAT_FS , 32, 32, 32, 32,
		VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT },
	{ "RGBA 32 SFLOAT optimal", GL_RGBA32F, VK_FORMAT_R32G32B32A32_SFLOAT, FLOAT_FS , 32, 32, 32, 32,
		VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					 VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					 VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT },

	{ "RGBA 32 INT linear", GL_RGBA32I, VK_FORMAT_R32G32B32A32_SINT, INT_FS, 32, 32, 32, 32,
		VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT },
	{ "RGBA 32 INT optimal", GL_RGBA32I, VK_FORMAT_R32G32B32A32_SINT, INT_FS, 32, 32, 32, 32,
		VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					 VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					 VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT },

	{ "RGBA 32 UINT linear", GL_RGBA32UI, VK_FORMAT_R32G32B32A32_UINT, FLOAT_FS , 32, 32, 32, 32,
		VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT },
	{ "RGBA 32 UINT optimal", GL_RGBA32UI, VK_FORMAT_R32G32B32A32_UINT, FLOAT_FS , 32, 32, 32, 32,
		VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
					 VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					 VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT },
};

const struct ds_format depth_stencil_formats[] = {
	{"D16", GL_DEPTH_COMPONENT16, VK_FORMAT_D16_UNORM},
	{"D32S8", GL_DEPTH32F_STENCIL8, VK_FORMAT_D32_SFLOAT_S8_UINT},
	{"D24S8", GL_DEPTH24_STENCIL8, VK_FORMAT_D24_UNORM_S8_UINT},
};

#endif /* PARAMS_H */
