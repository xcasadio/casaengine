#ifndef QUATERNION_H
#define QUATERNION_H

#include "CA_Export.h"
#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"

#include "Memory/MemoryAllocation.h"
#include "Matrix3.h"

namespace CasaEngine
{
    ////////////////////////////////////////////////////////////
    // Classe des quaternions
    ////////////////////////////////////////////////////////////
	class CA_EXPORT Quaternion :
		public AllocatedObject<Quaternion>
    {
    public :

        //----------------------------------------------------------
        // Constructeur par défaut
        //----------------------------------------------------------
        Quaternion(float X = 0.0f, float Y = 0.0f, float Z = 0.0f, float W = 1.0f);

        //----------------------------------------------------------
        // Constructeur à partir d'une matrice
        //----------------------------------------------------------
        Quaternion(const Matrix4& Matrix);

        //----------------------------------------------------------
        // Constructeur à partir d'un axe et d'un angle
        //----------------------------------------------------------
        Quaternion(const Vector3F& Axis, float Angle);

		float getX() const;
		float getY() const;
		float getZ() const;
		float getW() const;

        //----------------------------------------------------------
        // Met le quaternion à l'identité
        //----------------------------------------------------------
        void Identity();

        //----------------------------------------------------------
        // Normalise le quaternion
        //----------------------------------------------------------
        void Normalize();

        //----------------------------------------------------------
        // Renvoie le conjugué
        //----------------------------------------------------------
        Quaternion Conjugate() const;

        Matrix3 ToMatrix3() const;
        Matrix4 ToMatrix4() const;

        //----------------------------------------------------------
        // Construit le quaternion à partir d'une matrice
        //----------------------------------------------------------
        void FromMatrix(const Matrix4& Matrix);

        //----------------------------------------------------------
        // Construit le quaternion à partir d'un axe et d'un angle
        //----------------------------------------------------------
        void FromAxisAngle(const Vector3F& Axis, float Angle);

        //----------------------------------------------------------
        // Transforme le quaternion en axe & angle de rotation
        //----------------------------------------------------------
        void ToAxisAngle(Vector3F& Axis, float& Angle) const;

		void Transform(const Vector3F &value, Vector3F &result) const;
		void Transform(const std::vector<Vector3F> &sourceArray, std::vector<Vector3F> &destinationArray) const;


        //----------------------------------------------------------
        // Construit le quaternion à partir de 3 angles d'Euler
        //----------------------------------------------------------
        void FromEulerAngles(float X, float Y, float Z);

        //----------------------------------------------------------
        // Opérateur de multiplication
        //----------------------------------------------------------
        Quaternion operator *(const Quaternion& q_) const;

        //----------------------------------------------------------
        // Opérateur de multiplication - affectation
        //----------------------------------------------------------
        const Quaternion& operator *=(const Quaternion& q_);

        //----------------------------------------------------------
        // Données membres
        //----------------------------------------------------------
        float x; ///< Composante X
        float y; ///< Composante Y
        float z; ///< Composante Z
        float w; ///< Composante W
    };


    //==========================================================
    // Fonctions globales relatives aux quaternions
    //==========================================================
    std::istream& operator >>(std::istream& Stream, Quaternion& Quaternion);
    std::ostream& operator <<(std::ostream& Stream, const Quaternion& Quaternion);

} // namespace CasaEngine


#endif // QUATERNION_H
