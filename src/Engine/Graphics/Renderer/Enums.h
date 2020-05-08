#ifndef ENUMS_H
#define ENUMS_H

namespace CasaEngine
{
    /**
     * 
     */
    enum TAlign
    {
        ALIGN_LEFT    = 1 << 0, ///< align left
        ALIGN_HCENTER = 1 << 1, ///< align horizontal center
        ALIGN_RIGHT   = 1 << 2, ///< align right
        ALIGN_TOP     = 1 << 3, ///< align top
        ALIGN_VCENTER = 1 << 4, ///< align vertical center
        ALIGN_BOTTOM  = 1 << 5, ///< align bottom

		ALIGN_FORCE_DWORD = 0x7fffffff, /* force 32-bit size enum */
    };

}

#endif // ENUMS_H
