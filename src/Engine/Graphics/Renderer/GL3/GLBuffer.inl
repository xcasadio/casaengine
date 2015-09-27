//==========================================================
// CasaEngine - Free C++ 3D engine
//
// Copyright (C) 2004-2005 Laurent Gomila
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc.,
// 59 Temple Place - Suite 330,
// Boston, MA  02111-1307, USA.
//
// E-mail : laurent.gom@gmail.com
//==========================================================


/////////////////////////////////////////////////////////////
/// Constructeur
///
/// \param Count :  Taille du buffer
/// \param Buffer : Pointeur sur le buffer GL
///
////////////////////////////////////////////////////////////
template <int Type>
inline GLBuffer<Type>::GLBuffer(unsigned long Count, unsigned int Buffer) :
	IBufferBase(Count),
	m_Buffer   (Buffer)
{
}


/////////////////////////////////////////////////////////////
/// Destructeur
///
////////////////////////////////////////////////////////////
template <int Type>
inline GLBuffer<Type>::~GLBuffer()
{
    if (m_Buffer)
	{
#if CA_PLATFORM_ANDROID

        glDeleteBuffers(1, &m_Buffer);

#else

		GLRenderer::glDeleteBuffersARB(1, &m_Buffer);

#endif // CA_PLATFORM_ANDROID
	}
}


/////////////////////////////////////////////////////////////
/// Renvoie un pointeur sur le buffer
///
/// \return Pointeur sur le buffer interne
///
////////////////////////////////////////////////////////////
template <int Type>
inline unsigned int GLBuffer<Type>::GetBuffer() const
{
    return m_Buffer;
}

/**
 * 
 */
template <int Type>
inline void GLBuffer<Type>::Fill(const void *data_, unsigned long size_, unsigned long flags_)
{
#if CA_PLATFORM_ANDROID

	GLCheck(glBindBuffer(Type, m_Buffer));
	GLenum f = flags_ & BUF_STREAM ? GL_STREAM_DRAW : GL_STATIC_DRAW;
	GLCheck(glBufferData(Type, size_, data_, f));

#else

	GLCheck(GLRenderer::glBindBufferARB(Type, m_Buffer));
	GLenum f = flags_ & BUF_STREAM ? GL_STREAM_DRAW_ARB : GL_STATIC_DRAW_ARB;
	GLCheck(glBufferDataARB(Type, size_, data_, f));

#endif
}

/////////////////////////////////////////////////////////////
/// Verrouille le buffer
///
/// \param Offset : Position du verrouillage
/// \param Size :   Nombre d'éléments à verrouiller
/// \param Flags :  Options de verrouillage
///
/// \return Pointeur sur les données du buffer
///
////////////////////////////////////////////////////////////
template <int Type>
inline void* GLBuffer<Type>::Lock(unsigned long Offset, unsigned long /*Size*/, unsigned long Flags)
{
	unsigned char* Buffer = nullptr;

#if CA_PLATFORM_ANDROID

    GLCheck(glBindBuffer(Type, m_Buffer));
	Buffer = reinterpret_cast<unsigned char*>(GLRenderer::glMapBufferOES(Type, GLEnum::LockFlags(Flags)));

#else

	GLCheck(GLRenderer::glBindBufferARB(Type, m_Buffer));
	Buffer = reinterpret_cast<unsigned char*>(GLRenderer::glMapBufferARB(Type, GLEnum::LockFlags(Flags)));

#endif // #if CA_PLATFORM_ANDROID

    return Buffer + Offset;
}


/////////////////////////////////////////////////////////////
/// Déverouille le buffer
///
////////////////////////////////////////////////////////////
template <int Type>
inline void GLBuffer<Type>::Unlock()
{
#if CA_PLATFORM_ANDROID

	GLCheck(GLRenderer::glUnmapBufferOES(Type));

#else

	GLCheck(GLRenderer::glUnmapBufferARB(Type));

#endif
}
