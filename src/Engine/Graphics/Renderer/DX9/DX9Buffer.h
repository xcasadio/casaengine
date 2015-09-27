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

#ifndef DX9BUFFER_H
#define DX9BUFFER_H

//==========================================================
// En-têtes
//==========================================================
#include "DX9Enum.h"
#include "Graphics/Vertices/BufferBase.h"

#include "CA_Assert.h"


struct IDirect3DVertexBuffer9;
struct IDirect3DIndexBuffer9;


namespace CasaEngine
{
    /////////////////////////////////////////////////////////////
    // Spécialisation DirectX9 des vertex / index buffers
    /////////////////////////////////////////////////////////////
    template <class T>
    class DX9Buffer : public IBufferBase
    {
    public :

        //----------------------------------------------------------
        // Constructeur
        //----------------------------------------------------------
        DX9Buffer(unsigned long Count, T* Buffer);

        //----------------------------------------------------------
        // Renvoie un pointeur sur le buffer
        //----------------------------------------------------------
        T* GetBuffer() const;

    private :

		/**
		 * 
		 */
		void Fill(const void* Data, unsigned long size_, unsigned long flags_);

        //----------------------------------------------------------
        // Verrouille le buffer
        //----------------------------------------------------------
        void* Lock(unsigned long Offset, unsigned long Size, unsigned long Flags);

        //----------------------------------------------------------
        // Déverouille le buffer
        //----------------------------------------------------------
        void Unlock();

        //----------------------------------------------------------
        // Données membres
        //----------------------------------------------------------
        SmartPtr<T, CResourceCOM> m_Buffer; ///< Pointeur sur le buffer Dx9
    };

    //==========================================================
    // Définition des vertex / index buffers à partir du template DX9Buffer
    //==========================================================
    typedef DX9Buffer<IDirect3DVertexBuffer9> DX9VertexBuffer;
    typedef DX9Buffer<IDirect3DIndexBuffer9>  DX9IndexBuffer;

    #include "DX9Buffer.inl"

} // namespace CasaEngine


#endif // DX9BUFFER_H
