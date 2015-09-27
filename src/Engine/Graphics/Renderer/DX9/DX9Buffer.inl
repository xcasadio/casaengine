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
/// \param Buffer : Pointeur sur le buffer Dx9
///
////////////////////////////////////////////////////////////
template <class T>
inline DX9Buffer<T>::DX9Buffer(unsigned long Count, T* Buffer) :
IBufferBase(Count),
m_Buffer   (Buffer)
{

}


/////////////////////////////////////////////////////////////
/// Renvoie un poiteur sur le buffer
///
/// \return Poiteur sur le buffer interne
///
////////////////////////////////////////////////////////////
template <class T>
inline T* DX9Buffer<T>::GetBuffer() const
{
    return m_Buffer;
}

/**
 * 
 */
template <class T>
void DX9Buffer<T>::Fill(const void* data_, unsigned long size_, unsigned long flags_)
{
	void* pData = Lock(0, 0, flags_); // 0 => lock entire  buffer
	CA_ASSERT(pData != nullptr, "DX9Buffer::Fill() : pData is nullptr. Lock() failed");

	memcpy(pData, data_, size_);
	//std::copy(pData, pData + count_, data_);
    Unlock();
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
template <class T>
inline void* DX9Buffer<T>::Lock(unsigned long Offset, unsigned long Size, unsigned long Flags)
{
    void* Data = nullptr;
    m_Buffer->Lock(Offset, Size, &Data, DX9Enum::LockFlags(Flags));

    return Data;
}


/////////////////////////////////////////////////////////////
/// Déverouille le buffer
///
////////////////////////////////////////////////////////////
template <class T>
inline void DX9Buffer<T>::Unlock()
{
    m_Buffer->Unlock();
}
