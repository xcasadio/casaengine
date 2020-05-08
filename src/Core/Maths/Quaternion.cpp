#include "Base.h"
#include "Log/LogManager.h"

#include "Maths/Quaternion.h"
#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"
#include "CA_Assert.h"

namespace CasaEngine
{
	Quaternion::Quaternion(float X, float Y, float Z, float W) :
		x(X),
		y(Y),
		z(Z),
		w(W)
	{

	}

	Quaternion::Quaternion(const Matrix4& Matrix)
	{
		FromMatrix(Matrix);
	}

	Quaternion::Quaternion(const Vector3F& Axis, float Angle)
	{
		FromAxisAngle(Axis, Angle);
	}


	float Quaternion::getX() const
	{
		return x;
	}

	float Quaternion::getY() const
	{
		return y;
	}

	float Quaternion::getZ() const
	{
		return z;
	}

	float Quaternion::getW() const
	{
		return w;
	}

	/////////////////////////////////////////////////////////////
	/// Met le quaternion à l'identité
	///
	////////////////////////////////////////////////////////////
	void Quaternion::Identity()
	{
		x = y = z = 0.0f;
		w = 1.0f;
	}


	/////////////////////////////////////////////////////////////
	/// Normalise le quaternion
	///
	////////////////////////////////////////////////////////////
	void Quaternion::Normalize()
	{
		float Norm = x * x + y * y + z * z + w * w;

		if (std::fabs(Norm) > std::numeric_limits<float>::epsilon())
		{
			x /= Norm;
			y /= Norm;
			z /= Norm;
			w /= Norm;
		}
	}


	/////////////////////////////////////////////////////////////
	/// Renvoie le conjugué
	///
	/// \return Quanternion conjugué
	///
	////////////////////////////////////////////////////////////
	Quaternion Quaternion::Conjugate() const
	{
		return Quaternion(-x, -y, -z, w);
	}

	/**
	 *
	 */
	Matrix3 Quaternion::ToMatrix3() const
	{
		// 	CA_ASSERT(q.IsValid(0.05f), "Quaternion::ToMatrix3()");
		// 	Vector3F v2(x, y, z);
		// 	v2 *= 2.0f;
		// 	float xx=1-v2.x*x;	float yy=v2.y*y;	float xw=v2.x*w;
		// 	float xy=v2.y*x;	float yz=v2.z*y;	float yw=v2.y*w;
		// 	float xz=v2.z*x;	float zz=v2.z*z;	float zw=v2.z*w;
		// 	m00=1.0f-yy-zz;		m01=xy-zw;			m02=xz+yw;
		// 	m10=xy+zw;			m11=xx-zz;			m12=yz-xw;
		// 	m20=xz-yw;			m21=yz+xw;			m22=xx-yy;

		float xx = x * x;
		float xy = x * y;
		float xz = x * z;
		float xw = x * w;
		float yy = y * y;
		float yz = y * z;
		float yw = y * w;
		float zz = z * z;
		float zw = z * w;

		return Matrix3(
			1.0f - 2.0f * (yy + zz), 2.0f * (xy - zw), 2.0f * (xy + yw),
			2.0f * (xy + zw), 1.0f - 2.0f * (xx + zz), 2.0f * (yz - xw),
			2.0f * (xz - yw), 2.0f * (yz + xw), 1.0f - 2.0f * (xx + yy));
	}

	/////////////////////////////////////////////////////////////
	/// Construit une matrice de rotation à partir du quaternion
	///
	/// \return Matrice construite
	///
	////////////////////////////////////////////////////////////
	Matrix4 Quaternion::ToMatrix4() const
	{
		float xx = x * x;
		float xy = x * y;
		float xz = x * z;
		float xw = x * w;
		float yy = y * y;
		float yz = y * z;
		float yw = y * w;
		float zz = z * z;
		float zw = z * w;

		return Matrix4(1 - 2 * (yy + zz), 2 * (xy - zw), 2 * (xy + yw), 0,
			2 * (xy + zw), 1 - 2 * (xx + zz), 2 * (yz - xw), 0,
			2 * (xz - yw), 2 * (yz + xw), 1 - 2 * (xx + yy), 0,
			0, 0, 0, 1);
	}


	/////////////////////////////////////////////////////////////
	/// Construit le quaternion à partir d'une matrice de rotation
	///
	/// \param Matrix : Matrice source
	///
	////////////////////////////////////////////////////////////
	void Quaternion::FromMatrix(const Matrix4& Matrix)
	{
		float Trace = Matrix(0, 0) + Matrix(1, 1) + Matrix(2, 2) + 1;

		if (Trace > 0)
		{
			float s = 0.5f / std::sqrt(Trace);
			x = (Matrix(2, 1) - Matrix(1, 2)) * s;
			y = (Matrix(0, 2) - Matrix(2, 0)) * s;
			z = (Matrix(1, 0) - Matrix(0, 1)) * s;
			w = 0.25f / s;
		}
		else
		{
			if (Matrix(0, 0) > Matrix(1, 1) && (Matrix(0, 0) > Matrix(2, 2)))
			{
				float s = std::sqrt(1 + Matrix(0, 0) - Matrix(1, 1) - Matrix(2, 2)) * 2;
				x = 0.5f / s;
				y = (Matrix(0, 1) + Matrix(1, 0)) / s;
				z = (Matrix(0, 2) + Matrix(2, 0)) / s;
				w = (Matrix(1, 2) + Matrix(2, 1)) / s;
			}
			else if (Matrix(1, 1) > Matrix(2, 2))
			{
				float s = std::sqrt(1 - Matrix(0, 0) + Matrix(1, 1) - Matrix(2, 2)) * 2;
				x = (Matrix(0, 1) + Matrix(1, 0)) / s;
				y = 0.5f / s;
				z = (Matrix(1, 2) + Matrix(2, 1)) / s;
				w = (Matrix(0, 2) + Matrix(2, 0)) / s;
			}
			else
			{
				float s = std::sqrt(1 - Matrix(0, 0) - Matrix(1, 1) + Matrix(2, 2)) * 2;
				x = (Matrix(0, 2) + Matrix(2, 0)) / s;
				y = (Matrix(1, 2) + Matrix(2, 1)) / s;
				z = 0.5f / s;
				w = (Matrix(0, 1) + Matrix(1, 0)) / s;
			}
		}
	}


	/////////////////////////////////////////////////////////////
	/// Construit le quaternion à partir d'un axe et d'un angle
	///
	/// \param Axis :  Axe de rotation
	/// \param Angle : Angle
	///
	////////////////////////////////////////////////////////////
	void Quaternion::FromAxisAngle(const Vector3F& Axis, float Angle)
	{
		float Cos = std::cos(Angle / 2);
		float Sin = std::sin(Angle / 2);

		x = Axis.x * Sin;
		y = Axis.y * Sin;
		z = Axis.z * Sin;
		w = Cos;

		Normalize();
	}


	/////////////////////////////////////////////////////////////
	/// Transforme le quaternion en axe & angle de rotation
	///
	/// \param Axis :  Axe de rotation
	/// \param Angle : Angle de rotation
	///
	////////////////////////////////////////////////////////////
	void Quaternion::ToAxisAngle(Vector3F& Axis, float& Angle) const
	{
		// Calcul de l'angle
		Angle = std::acos(w) * 2;

		// Calcul de l'axe
		float Norm = std::sqrt(x * x + y * y + z * z);
		if (std::fabs(Norm) > std::numeric_limits<float>::epsilon())
		{
			Axis.x = x / Norm;
			Axis.y = y / Norm;
			Axis.z = z / Norm;
		}
		else
		{
			Axis.x = 0.0f;
			Axis.y = 1.0f;
			Axis.z = 0.0f;
		}
	}

	/// <summary>
	/// Transforms a vector by a quaternion rotation.
	/// </summary>
	/// <param name="vec">The vector to transform.</param>
	/// <param name="quat">The quaternion to rotate the vector by.</param>
	/// <param name="result">The result of the operation.</param>
	void Quaternion::Transform(const Vector3F& value, Vector3F& result) const
	{
		float x = 2 * (this->y * value.z - this->z * value.y);
		float y = 2 * (this->z * value.x - this->x * value.z);
		float z = 2 * (this->x * value.y - this->y * value.x);

		result.x = value.x + x * this->w + (this->y * z - this->z * y);
		result.y = value.y + y * this->w + (this->z * x - this->x * z);
		result.z = value.z + z * this->w + (this->x * y - this->y * x);
	}

	/// <summary>
	/// Transforms an array of vectors by a quaternion rotation.
	/// </summary>
	/// <param name="sourceArray">The vectors to transform</param>
	/// <param name="rotation">The quaternion to rotate the vector by.</param>
	/// <param name="destinationArray">The result of the operation.</param>
	void Quaternion::Transform(const std::vector<Vector3F>& sourceArray, std::vector<Vector3F>& destinationArray) const
	{
		CA_ASSERT(destinationArray.size() >= sourceArray.size(), "The destination array is smaller than the source array.");

		int i = 0;

		for (std::vector<Vector3F>::const_iterator it = sourceArray.cbegin();
			it != sourceArray.cend();
			it++)
		{
			Vector3F position = *it;

			float x = 2 * (this->y * position.z - this->z * position.y);
			float y = 2 * (this->z * position.x - this->x * position.z);
			float z = 2 * (this->x * position.y - this->y * position.x);

			destinationArray[i] = Vector3F(
				position.x + x * this->w + (this->y * z - this->z * y),
				position.y + y * this->w + (this->z * x - this->x * z),
				position.z + z * this->w + (this->x * y - this->y * x));
			i++;
		}
	}


	/////////////////////////////////////////////////////////////
	/// Construit le quaternion à partir de 3 angles d'Euler
	///
	/// \param X : Angle autour de X
	/// \param Y : Angle autour de Y
	/// \param Z : Angle autour de Z
	///
	////////////////////////////////////////////////////////////
	void Quaternion::FromEulerAngles(float X, float Y, float Z)
	{
		Quaternion Qx(Vector3F(1, 0, 0), X);
		Quaternion Qy(Vector3F(0, 1, 0), Y);
		Quaternion Qz(Vector3F(0, 0, 1), Z);

		*this = Qx * Qy * Qz;
	}


	/////////////////////////////////////////////////////////////
	/// Opérateur de multiplication
	///
	/// \param Quaternion : Quaternion à multiplier
	///
	/// \return Résultat de l'opération
	///
	////////////////////////////////////////////////////////////
	Quaternion Quaternion::operator *(const Quaternion& quat_) const
	{
		return Quaternion(w * quat_.x + x * quat_.w + y * quat_.z - z * quat_.y,
			w * quat_.y + y * quat_.w + z * quat_.x - x * quat_.z,
			w * quat_.z + z * quat_.w + x * quat_.y - y * quat_.x,
			w * quat_.w - x * quat_.x - y * quat_.y - z * quat_.z);
	}


	/////////////////////////////////////////////////////////////
	/// opérateur de multiplication - affectation
	///
	/// \param Quaternion : Quaternion à multiplier
	///
	/// \return Résultat de l'opération
	///
	////////////////////////////////////////////////////////////
	const Quaternion& Quaternion::operator *=(const Quaternion& q_)
	{
		*this = *this * q_;

		return *this;
	}


	/////////////////////////////////////////////////////////////
	/// Surcharge de l'opérateur >> entre un flux et un quaternion
	///
	/// \param  Stream :     Flux d'entrée
	/// \param Quaternion : Quaternion
	///
	/// \return Référence sur le flux d'entrée
	///
	////////////////////////////////////////////////////////////
	std::istream& operator >>(std::istream& Stream, Quaternion& q_)
	{
		return Stream >> q_.x >> q_.y >> q_.z >> q_.w;
	}


	/////////////////////////////////////////////////////////////
	/// Surcharge de l'opérateur << entre un flux et un quaternion
	///
	/// \param Stream :     Flux de sortie
	/// \param Quaternion : Quaternion
	///
	/// \return Référence sur le flux de sortie
	///
	////////////////////////////////////////////////////////////
	std::ostream& operator <<(std::ostream& Stream, const Quaternion& Quaternion)
	{
		return Stream << Quaternion.x << " " << Quaternion.y << " " << Quaternion.z << " " << Quaternion.w;
	}

}
