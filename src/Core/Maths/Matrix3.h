#ifndef MATRIX3_H
#define MATRIX3_H

#include "CA_Export.h"

#include "Maths/Vector2.h"
#include "Maths/Vector3.h"
#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
	/**
	 *
	 */
	class CA_EXPORT Matrix3 :
		public AllocatedObject<Matrix3>
	{
	public:
		float a11, a21, a31;
		float a12, a22, a32;
		float a13, a23, a33;

		/**
		 *
		 */
		Matrix3(float m11 = 1.0f, float m12 = 0.0f, float m13 = 0.0f,
			float m21 = 0.0f, float m22 = 1.0f, float m23 = 0.0f,
			float m31 = 0.0f, float m32 = 0.0f, float m33 = 1.0f);

		//----------------------------------------------------------
		// Met la matrice à l'identité
		//----------------------------------------------------------
		void Identity();

		//----------------------------------------------------------
		// Calcule le déterminant de la matrice
		//----------------------------------------------------------
		float Determinant() const;

		//----------------------------------------------------------
		// Transpose la matrice
		//----------------------------------------------------------
		Matrix3 Transpose() const;

		//----------------------------------------------------------
		// Inverse la matrice
		//----------------------------------------------------------
		Matrix3 Inverse() const;

		//----------------------------------------------------------
		// Construit une matrice de translation
		//----------------------------------------------------------
		void CreateTranslation(float x, float y);

		//----------------------------------------------------------
		// Construit une matrice de mise à l'échelle
		//----------------------------------------------------------
		void CreateScaling(float x, float y);

		//----------------------------------------------------------
		// Construit une matrice de rotation centrée en (0, 0)
		//----------------------------------------------------------
		void CreateRotation(float Angle);

		//----------------------------------------------------------
		// Construit une matrice de rotation en spécifiant le centre
		//----------------------------------------------------------
		void CreateRotation(float Angle, const Vector2F& Center);

		//----------------------------------------------------------
		// Apply a translation
		//----------------------------------------------------------
		void Translate(float x, float y);

		//----------------------------------------------------------
		// Apply a scale
		//----------------------------------------------------------
		void Scale(float x, float y);

		//----------------------------------------------------------
		// Apply a rotation
		//----------------------------------------------------------
		void Rotate(float Angle);
		void Rotate(const Vector2F& fwd, const Vector2F& side);

		//----------------------------------------------------------
		// Renvoie la translation contenue dans la matrice
		//----------------------------------------------------------
		Vector2F GetTranslation() const;

		//----------------------------------------------------------
		// Transforme un vecteur
		//----------------------------------------------------------
		Vector3F Transform(const Vector2F& v, float w = 1.0f) const;
		Vector3F Transform(const Vector3F& v) const;

		//----------------------------------------------------------
		// Transformation
		//----------------------------------------------------------
		void TransformVector2List(std::vector<Vector2F>& vPoint_) const;
		void TransformVector2F(Vector2F& vPoint) const;

		//----------------------------------------------------------
		// Opérateurs + et - unaires
		//----------------------------------------------------------
		Matrix3 operator +() const;
		Matrix3 operator -() const;

		//----------------------------------------------------------
		// Opérateurs + et - binaires
		//----------------------------------------------------------
		Matrix3 operator +(const Matrix3& m) const;
		Matrix3 operator -(const Matrix3& m) const;

		//----------------------------------------------------------
		// Opérateurs += et -=
		//----------------------------------------------------------
		const Matrix3& operator +=(const Matrix3& m);
		const Matrix3& operator -=(const Matrix3& m);

		//----------------------------------------------------------
		// Opérateur * et *=
		//----------------------------------------------------------
		Matrix3 operator *(const Matrix3& m) const;
		const Matrix3& operator *=(const Matrix3& m);

		//----------------------------------------------------------
		// Opérateurs *= et /= avec un scalaire
		//----------------------------------------------------------
		const Matrix3& operator *=(float t);
		const Matrix3& operator /=(float t);

		/**
		 *
		 */
		bool operator ==(const Matrix3& m) const;
		bool operator !=(const Matrix3& m) const;

		/**
		 *
		 */
		float& operator ()(std::size_t i, std::size_t j);
		const float& operator ()(std::size_t i, std::size_t j) const;

		/**
		 *
		 */
		operator float* ();
		operator const float* () const;
	};

	//==========================================================
	// Fonctions globales relatives aux matrices
	//==========================================================
	Matrix3      operator * (const Matrix3& m, float t);
	Matrix3      operator * (float t, const Matrix3& m);
	Matrix3      operator / (const Matrix3& m, float t);
	std::istream& operator >>(std::istream& Stream, Matrix3& Mat);
	std::ostream& operator <<(std::ostream& Stream, const Matrix3& Mat);
}

#endif // Matrix3_H
