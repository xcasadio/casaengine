#ifndef PLANE_H
#define PLANE_H


#include <Maths/Vector3.h>
#include <Maths/Vector4.h>
#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
    ////////////////////////////////////////////////////////////
    /// Plans à 4 composantes réelles
    ////////////////////////////////////////////////////////////
	class CPlane :
		public AllocatedObject<CPlane>
    {
    public :

        //----------------------------------------------------------
        // Constructeur par défaut
        //----------------------------------------------------------
        CPlane(float A = 0.0f, float B = 0.0f, float C = 0.0f, float D = 0.0f);

        //----------------------------------------------------------
        // Constructeur à partir de trois points
        //----------------------------------------------------------
        CPlane(const Vector3F& v0, const Vector3F& v1, const Vector3F& v2);

        //----------------------------------------------------------
        // Constructeur à partir d'une normale et d'un point
        //----------------------------------------------------------
        CPlane(const Vector3F& Normal, const Vector3F& Point);

        //----------------------------------------------------------
        // Construit le plan à partir de trois points
        //----------------------------------------------------------
        void BuildFromPoints(const Vector3F& v0, const Vector3F& v1, const Vector3F& v2);

        //----------------------------------------------------------
        // Renvoie la plus courte distance entre le plan et un point
        //----------------------------------------------------------
        float DistanceToPoint(const Vector3F& Point) const;
        float DistanceToPoint(const Vector4F& Point) const;

		/**
		 * 
		 */
		bool IntersectLine(const Vector3F& p1_, const Vector3F& p2_, Vector3F *pOut_);

        //----------------------------------------------------------
        // Opérateurs de comparaison
        //----------------------------------------------------------
        bool operator ==(const CPlane& p) const;
        bool operator !=(const CPlane& p) const;

        //----------------------------------------------------------
        // Intersections
        //----------------------------------------------------------

        //----------------------------------------------------------
        // Données membres
        //----------------------------------------------------------
        Vector3F n; ///< Normale du plan
        float     d; ///< Distance du plan à l'originie
    };

    //==========================================================
    // Fonctions globales relatives aux plan
    //==========================================================
    std::istream& operator >>(std::istream& Stream, CPlane& Plane);
    std::ostream& operator <<(std::ostream& Stream, const CPlane& Plane);

    #include "Plane.inl"


} // namespace CasaEngine


#endif // PLANE_H
