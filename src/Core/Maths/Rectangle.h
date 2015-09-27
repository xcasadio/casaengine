
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "CA_Export.h"
#include "Maths/Vector2.h"
#include "Memory/MemoryAllocation.h"

#include <iostream>

namespace CasaEngine
{
	////////////////////////////////////////////////////////////
	/// Types d'intersections
	////////////////////////////////////////////////////////////
	enum TIntersection
	{
		INT_IN,        ///< Compl�tement � l'int�rieur
		INT_OUT,       ///< Compl�tement � l'ext�rieur
		INT_INTERSECTS ///< Intersection
	};


    ////////////////////////////////////////////////////////////
    /// Class des rectangles 2D � coordonn�es enti�res
    ////////////////////////////////////////////////////////////
	class CA_EXPORT CRectangle :
		public AllocatedObject<CRectangle>
    {
    public :

        //----------------------------------------------------------
        // Constructeur par d�faut
        //----------------------------------------------------------
        CRectangle(const Vector2I& Start = Vector2I(0, 0), const Vector2I& Size = Vector2I(0, 0));

        //----------------------------------------------------------
        // Constructeur � partir de 2 coordonn�es et 2 dimensions
        //----------------------------------------------------------
        CRectangle(int Left, int Top, int Width, int Height);

        //----------------------------------------------------------
        // R�initialise le rectangle
        //----------------------------------------------------------
        void Set(int Left, int Top, int Width, int Height);

        //----------------------------------------------------------
        // Renvoie le cot� gauche du rectangle
        //----------------------------------------------------------
        int Left() const;

        //----------------------------------------------------------
        // Renvoie le cot� droit du rectangle
        //----------------------------------------------------------
        int Right() const;

        //----------------------------------------------------------
        // Renvoie le cot� haut du rectangle
        //----------------------------------------------------------
        int Top() const;

        //----------------------------------------------------------
        // Renvoie le cot� bas du rectangle
        //----------------------------------------------------------
        int Bottom() const;

        //----------------------------------------------------------
        // Renvoie la largeur du rectangle
        //----------------------------------------------------------
        int Width() const;

        //----------------------------------------------------------
        // Renvoie la hauteur du rectangle
        //----------------------------------------------------------
        int Height() const;

        //----------------------------------------------------------
        // Renvoie la taille du rectangle
        //----------------------------------------------------------
        Vector2I Size() const;

        //----------------------------------------------------------
        // Test d'intersection avec un point
        //----------------------------------------------------------
        TIntersection Intersects(const Vector2I& Point) const;

        //----------------------------------------------------------
        // Test d'intersection avec un rectangle
        //----------------------------------------------------------
        TIntersection Intersects(const CRectangle& Rect) const;

        //----------------------------------------------------------
        // Op�rateurs de comparaison
        //----------------------------------------------------------
        bool operator ==(const CRectangle& Rect) const;
        bool operator !=(const CRectangle& Rect) const;

        //----------------------------------------------------------
        // Donn�es membres
        //----------------------------------------------------------
        Vector2I Origin; ///< Coin haut-gauche
        Vector2I End;    ///< Coin bas-droit
    };

    //==========================================================
    // Fonctions globales relatives aux rectangles
    //==========================================================
    CA_EXPORT std::istream& operator >>(std::ostream& Stream, CRectangle& Rect);
    CA_EXPORT std::ostream& operator <<(std::ostream& Stream, const CRectangle& Rect);

} // namespace CasaEngine


#endif // RECTANGLE_H
