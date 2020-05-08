#ifndef PROGRAM_H
#define PROGRAM_H

#include "Maths/Vector2.h"
#include "Maths/Vector3.h"
#include "Maths/Vector4.h"
#include <string>
#include "Graphics/Color.h"
#include "CA_Export.h"
#include "Memory/MemoryAllocation.h"
#include "Maths/Matrix4.h"
#include "Graphics/Textures/Texture.h"
#include "bgfx.h"
#include "Shader.h"

namespace CasaEngine
{
    /**
     * 
     */
    class CA_EXPORT Program :
		public AllocatedObject<Program>
    {
    public :
        /**
         * 
         */
        static void SetParameter(const char *pName, float Value);

        /**
         * 
         */
        static void SetParameter(const char *pName, const Vector2F& Value);

        /**
         * 
         */
        static void SetParameter(const char *pName, const Vector3F& Value);

        /**
         * 
         */
        static void SetParameter(const char *pName, const Vector4F& Value);

        /**
         * 
         */
        static void SetParameter(const char *pName, const Matrix4& Value);

        /**
         * 
         */
        static void SetParameter(const char *pName, const CColor& Value);

		/**
		 * 
		 */
		static void SetParameter(const char *pName, const Texture* Value);
		
	public:
        Program(const char* _vsName, const char* _fsName);

		/**
         * 
         */
        Program(bgfx::ProgramHandle handle_);

		/**
		 * 
		 */
        virtual ~Program();

		/**
		 * 
		 */
		bgfx::ProgramHandle Handle() const;
		
    private :
		bgfx::ProgramHandle m_Handle;
        Shader *m_pVs, *m_pFs;
	};

}


#endif // PROGRAM_H
