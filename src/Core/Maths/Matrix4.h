#ifndef MATRIX4_H
#define MATRIX4_H

#include "CA_Export.h"
#include "Maths/Vector3.h"
#include "Maths/Vector4.h"
#include "CA_Assert.h"
#include "Memory/MemoryAllocation.h"

#include <cmath>

namespace CasaEngine
{
	class Quaternion;

	/**
	 *
	 */
	class CA_EXPORT Matrix4 :
		public AllocatedObject<Matrix4>
	{
	public:

		//----------------------------------------------------------
		// Constructeur par défaut
		//----------------------------------------------------------
		Matrix4(float m11 = 1.0f, float m12 = 0.0f, float m13 = 0.0f, float m14 = 0.0f,
			float m21 = 0.0f, float m22 = 1.0f, float m23 = 0.0f, float m24 = 0.0f,
			float m31 = 0.0f, float m32 = 0.0f, float m33 = 1.0f, float m34 = 0.0f,
			float m41 = 0.0f, float m42 = 0.0f, float m43 = 0.0f, float m44 = 1.0f);

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
		Matrix4 Transpose() const;

		//----------------------------------------------------------
		// Inverse la matrice
		//----------------------------------------------------------
		Matrix4 Invert() const;

		void SetTranslation(float x, float y, float z);
		void SetTranslation(Vector3F& trans_);

		//----------------------------------------------------------
		// Renvoie la translation contenue dans la matrice
		//----------------------------------------------------------
		Vector3F GetTranslation() const;

		//----------------------------------------------------------
		// Construit une matrice de translation
		//----------------------------------------------------------
		void CreateTranslation(float x, float y, float z);

		//----------------------------------------------------------
		// Construit une matrice de mise à l'échelle
		//----------------------------------------------------------
		void CreateScale(float x, float y, float z);

		//----------------------------------------------------------
		// Construit une matrice de rotation centrée en (0, 0, 0)
		//----------------------------------------------------------
		void CreateRotationX(float Angle);
		void CreateRotationY(float Angle);
		void CreateRotationZ(float Angle);

		//----------------------------------------------------------
		// Construit une matrice de rotation en spécifiant le centre
		//----------------------------------------------------------
		void CreateRotationX(float Angle, const Vector3F& Center);
		void CreateRotationY(float Angle, const Vector3F& Center);
		void CreateRotationZ(float Angle, const Vector3F& Center);

		void CreateFromDirection(const Vector3F& forward, const Vector3F& side, const Vector3F& up);

		/**
		 *
		 */
		void Transformation(
			const Vector3F* pscalingcenter,
			const Quaternion* pscalingrotation,
			const Vector3F* pscaling,
			const Vector3F* protationcenter,
			const Quaternion* protation,
			const Vector3F* ptranslation);

		//----------------------------------------------------------
		// Transforme un vecteur
		//----------------------------------------------------------
		Vector3F Transform(const Vector3F& v, float w = 1.0f) const;
		Vector4F Transform(const Vector4F& v) const;

		void Transform(const Vector3F& position, Vector3F& result);
		void Transform(const std::vector<Vector3F>& sourceArray, std::vector<Vector3F>& destinationArray);
		void TransformNormal(const Vector3F& normal, Vector3F& result) const;

		//----------------------------------------------------------
		// Construit une matrice ortho non-centrée
		//----------------------------------------------------------
		void OrthoOffCenter(float _left, float _top, float _right, float _bottom, float _near, float _far, float _offset = 0.0f);

		//----------------------------------------------------------
		// Construit une matrice de projection perspective
		//----------------------------------------------------------
		void PerspectiveFOV(float Fov, float Ratio, float Near, float Far);

		//----------------------------------------------------------
		// Construit une matrice de vue
		//----------------------------------------------------------
		void LookAt(const Vector3F& From, const Vector3F& To, const Vector3F& Up = Vector3F(0, 1, 0));

		//----------------------------------------------------------
		// Opérateurs + et - unaires
		//----------------------------------------------------------
		Matrix4 operator +() const;
		Matrix4 operator -() const;

		//----------------------------------------------------------
		// Opérateurs + et - binaires
		//----------------------------------------------------------
		Matrix4 operator +(const Matrix4& m) const;
		Matrix4 operator -(const Matrix4& m) const;

		//----------------------------------------------------------
		// Opérateurs += et -=
		//----------------------------------------------------------
		const Matrix4& operator +=(const Matrix4& m);
		const Matrix4& operator -=(const Matrix4& m);

		//----------------------------------------------------------
		// Opérateur * et *=
		//----------------------------------------------------------
		Matrix4 operator *(const Matrix4& m) const;
		const Matrix4& operator *=(const Matrix4& m);

		//----------------------------------------------------------
		// Opérateurs *= et /= avec un scalaire
		//----------------------------------------------------------
		const Matrix4& operator *=(float t);
		const Matrix4& operator /=(float t);

		//----------------------------------------------------------
		// Opérateurs de comparaison
		//----------------------------------------------------------
		bool operator ==(const Matrix4& m) const;
		bool operator !=(const Matrix4& m) const;

		//----------------------------------------------------------
		// Opérateurs d'accès indexé aux éléments
		//----------------------------------------------------------
		float& operator ()(std::size_t i, std::size_t j);
		const float& operator ()(std::size_t i, std::size_t j) const;

		//----------------------------------------------------------
		// Opérateur de cast en float*
		//----------------------------------------------------------
		operator float* ();
		operator const float* () const;

		//----------------------------------------------------------
		// Données membres
		//----------------------------------------------------------
		/*float a11, a12, a13, a14;
		float a21, a22, a23, a24;
		float a31, a32, a33, a34;
		float a41, a42, a43, a44;*/
		float a11, a21, a31, a41; ///< 1ère ligne de la matrice
		float a12, a22, a32, a42; ///< 2ème ligne de la matrice
		float a13, a23, a33, a43; ///< 3ème ligne de la matrice
		float a14, a24, a34, a44; ///< 4ème ligne de la matrice
	};

	//==========================================================
	// Fonctions globales relatives aux matrices
	//==========================================================
	Matrix4      operator * (const Matrix4& m, float t);
	Matrix4      operator * (float t, const Matrix4& m);
	Matrix4      operator / (const Matrix4& m, float t);
	std::istream& operator >>(std::istream& Stream, Matrix4& Mat);
	std::ostream& operator <<(std::ostream& Stream, const Matrix4& Mat);
}

#endif // MATRIX4_H
