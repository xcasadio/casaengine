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

#ifndef DX9SHADER_H
#define DX9SHADER_H

#include "Graphics/Effects/ShaderBase.h"
#include "d3dx9effect.h"
#include "SmartPtr.h"
#include "SmartPtrPolicies.h"


namespace CasaEngine
{
    /////////////////////////////////////////////////////////////
    // Sp�cialisation DirectX9 des shaders Cg
    /////////////////////////////////////////////////////////////
    class DX9Shader : public IShaderBase
    {
    public :

        //----------------------------------------------------------
        // Constructuit le shader � partir d'un CGprogram
        //----------------------------------------------------------
        DX9Shader(LPD3DXEFFECT pEffect);

		~DX9Shader();

		ID3DXEffect* DX9Shader::D3DXEffect() const;

    private :

		//----------------------------------------------------------
		// 
		//----------------------------------------------------------
		//void Begin();

		//----------------------------------------------------------
		// 
		//----------------------------------------------------------
		//void End();

        //----------------------------------------------------------
        // Change un param�tre (scalaire ou vecteur) du shader
        //----------------------------------------------------------
        virtual void SetParameter(const std::string& Name, const size_t count_, const float* Value);

        //----------------------------------------------------------
        // Change un param�tre (matrice) du shader
        //----------------------------------------------------------
        virtual void SetParameter(const std::string& Name, const Matrix4& Value);

		/**
		 * 
		 */
		virtual void SetParameter(const std::string& Name, const ITextureBase* Value);
		
		//SmartPtr<ID3DXEffect, CResourceCOM> m_pEffect;
		ID3DXEffect *m_pEffect;

		DWORD m_Flags;
		int m_CurrentPass;
		unsigned int m_NbPass;
	};

} // namespace CasaEngine


#endif // DX9SHADER_H
