/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef BGFX_UTILS_H_HEADER_GUARD
#define BGFX_UTILS_H_HEADER_GUARD

#include <bgfx.h>
#include "..\..\..\bx\include\bx\debug.h"
#include "Log\LogManager.h"

namespace bgfx_utils
{

void initBgfxUtils();
void clearBgfxUtils();

void* load(const char* _filePath, uint32_t* _size = NULL);
void unload(void* _ptr);
bgfx::ShaderHandle loadShader(const char* _name);
bgfx::ProgramHandle loadProgram(const char* _vsName, const char* _fsName);
bgfx::TextureHandle loadTexture(const char* _name, uint32_t _flags = BGFX_TEXTURE_NONE, uint8_t _skip = 0, bgfx::TextureInfo* _info = NULL);
void calcTangents(void* _vertices, uint16_t _numVertices, bgfx::VertexDecl _decl, const uint16_t* _indices, uint32_t _numIndices);

struct MeshState
{
	struct Texture
	{
		uint32_t            m_flags;
		bgfx::UniformHandle m_sampler;
		bgfx::TextureHandle m_texture;
		uint8_t             m_stage;
	};

	Texture             m_textures[4];
	uint64_t            m_state;
	bgfx::ProgramHandle m_program;
	uint8_t             m_numTextures;
	uint8_t             m_viewId;
};

struct Mesh;

Mesh* meshLoad(const char* _filePath);
void meshUnload(Mesh* _mesh);

MeshState* meshStateCreate();
void meshStateDestroy(MeshState* _meshState);

void meshSubmit(const Mesh* _mesh, uint8_t _id, bgfx::ProgramHandle _program, const float* _mtx, uint64_t _state = BGFX_STATE_MASK);
void meshSubmit(const Mesh* _mesh, const MeshState*const* _state, uint8_t _numPasses, const float* _mtx, uint16_t _numMatrices = 1);

using namespace bgfx;

struct CallbackStub : public bgfx::CallbackI
{
	virtual ~CallbackStub();
	virtual void traceVargs(const char* _filePath, uint16_t _line, const char* _format, va_list _argList);
	virtual void fatal(Fatal::Enum _code, const char* _str);
	virtual uint32_t cacheReadSize(uint64_t /*_id*/);
	virtual bool cacheRead(uint64_t /*_id*/, void* /*_data*/, uint32_t /*_size*/);
	virtual void cacheWrite(uint64_t /*_id*/, const void* /*_data*/, uint32_t /*_size*/);
	virtual void screenShot(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _data, uint32_t _size, bool _yflip);
	virtual void captureBegin(uint32_t /*_width*/, uint32_t /*_height*/, uint32_t /*_pitch*/, TextureFormat::Enum /*_format*/, bool /*_yflip*/);
	virtual void captureEnd();
	virtual void captureFrame(const void* /*_data*/, uint32_t /*_size*/);
};

} // namespace bgfx_utils

#endif // BGFX_UTILS_H_HEADER_GUARD
