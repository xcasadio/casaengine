#include "Quaternion.h"
#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"
#include "Maths/Vector4.h"
#include "Exceptions.h"

namespace CasaEngine
{
	Matrix4::Matrix4()
	{
		Identity();
	}

	Matrix4::Matrix4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31,
		float m32, float m33, float m34, float m41, float m42, float m43, float m44) :
		m11(m11), m21(m21), m31(m31), m41(m41), m12(m12), m22(m22), m32(m32), m42(m42), m13(m13), m23(m23), m33(m33),
		m43(m43), m14(m14), m24(m24), m34(m34),
		m44(m44)
	{
		
	}

	Matrix4::Matrix4(Vector4F row1, Vector4F row2, Vector4F row3, Vector4F row4) : m11(row1.x), m21(row2.x),
		m31(row3.x), m41(row4.x), m12(row1.y), m22(row2.y), m32(row3.y), m42(row4.y), m13(row1.z), m23(row2.z),
		m33(row3.z), m43(row4.z), m14(row1.w), m24(row2.w), m34(row3.w), m44(row4.w)
	{
	}

	float Matrix4::operator[](int index) const
	{
		switch (index)
		{
		case 0: return m11;
		case 1: return m12;
		case 2: return m13;
		case 3: return m14;
		case 4: return m21;
		case 5: return m22;
		case 6: return m23;
		case 7: return m24;
		case 8: return m31;
		case 9: return m32;
		case 10: return m33;
		case 11: return m34;
		case 12: return m41;
		case 13: return m42;
		case 14: return m43;
		case 15: return m44;
		default: throw CArgumentOutOfRangeException("Matrix4::operator[]");
		}
	}

	float& Matrix4::operator()(std::size_t i, std::size_t j)
	{
		return *(&m11 + (i + 4 * j));
	}

	const float& Matrix4::operator()(std::size_t i, std::size_t j) const
	{
		return *(&m11 + (i + 4 * j));
	}

	Matrix4::operator const float* () const
	{
		return &m11;
	}

	Matrix4::operator float* ()
	{
		return &m11;
	}

	Matrix4 Matrix4::CreateIdentity()
	{
		return {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}

	void Matrix4::Identity()
	{
		m11 = 1.0f;
		m12 = 0.0f;
		m13 = 0.0f;
		m14 = 0.0f;
		m21 = 0.0f;
		m22 = 1.0f;
		m23 = 0.0f;
		m24 = 0.0f;
		m31 = 0.0f;
		m32 = 0.0f;
		m33 = 1.0f;
		m34 = 0.0f;
		m41 = 0.0f;
		m42 = 0.0f;
		m43 = 0.0f;
		m44 = 1.0f;
	}

	Vector3F Matrix4::Backward()
	{
		return {m31, m32, m33};
	}

	void Matrix4::Backward(const Vector3F& value)
	{
		m31 = value.x;
		m32 = value.y;
		m33 = value.z;
	}

	Vector3F Matrix4::Down() const
	{
		return {-m21, -m22, -m23};
	}

	void Matrix4::Down(const Vector3F& value)
	{
		m21 = -value.x;
		m22 = -value.y;
		m23 = -value.z;
	}

	Vector3F Matrix4::Forward() const
	{
		return {-m31, -m32, -m33};
	}

	void Matrix4::Forward(const Vector3F& value)
	{
		m31 = -value.x;
		m32 = -value.y;
		m33 = -value.z;
	}

	Vector3F Matrix4::Left() const
	{
		return {-m11, -m12, -m13};
	}

	void Matrix4::Left(const Vector3F& value)
	{
		m11 = -value.x;
		m12 = -value.y;
		m13 = -value.z;
	}

	Vector3F Matrix4::Right()
	{
		return {m11, m12, m13};
	}

	void Matrix4::Right(Vector3F value)
	{
		m11 = value.x;
		m12 = value.y;
		m13 = value.z;
	}

	Vector3F Matrix4::Translation()
	{
		return {m41, m42, m43};
	}

	void Matrix4::Translation(const Vector3F& value)
	{
		Translation(value.x, value.y, value.z);
	}

	void Matrix4::Translation(float x, float y, float z)
	{
		m41 = x;
		m42 = y;
		m43 = z;
	}

	Vector3F Matrix4::Up()
	{
		return {m21, m22, m23};
	}

	void Matrix4::Up(Vector3F value)
	{
		m21 = value.x;
		m22 = value.y;
		m23 = value.z;
	}

	void Matrix4::CreateFromDirection(const Vector3F& forward, const Vector3F& side, const Vector3F& up)
	{
		Forward(forward);
		Up(up);
		Right(side);
		//a11 = side.x; a12 = up.x; a13 = -forward.x; a14 = 0.0f;
		//a21 = side.y; a22 = up.y; a23 = -forward.y; a24 = 0.0f;
		//a31 = side.z; a32 = up.z; a33 = -forward.z; a34 = 0.0f;
		m41 = 0.0f; m42 = 0.0f; m43 = 0.0f; m44 = 1.0f;
	}

	void Matrix4::Transformation(const Vector3F* pscalingcenter, const Quaternion* pscalingrotation,
		const Vector3F* pscaling, const Vector3F* protationcenter, const Quaternion* protation,
		const Vector3F* ptranslation)
	{
		Matrix4 m1, m2, m3, m4, m5, m6, m7, p1, p2, p3, p4, p5;
		Quaternion prc;
		Vector3F psc, pt;

		if (!pscalingcenter)
		{
			psc.x = 0.0f;
			psc.y = 0.0f;
			psc.z = 0.0f;
		}
		else
		{
			psc.x = pscalingcenter->x;
			psc.y = pscalingcenter->y;
			psc.z = pscalingcenter->z;
		}
		if (!protationcenter)
		{
			prc.x = 0.0f;
			prc.y = 0.0f;
			prc.z = 0.0f;
		}
		else
		{
			prc.x = protationcenter->x;
			prc.y = protationcenter->y;
			prc.z = protationcenter->z;
		}
		if (!ptranslation)
		{
			pt.x = 0.0f;
			pt.y = 0.0f;
			pt.z = 0.0f;
		}
		else
		{
			pt.x = ptranslation->x;
			pt.y = ptranslation->y;
			pt.z = ptranslation->z;
		}

		m1 = Matrix4::CreateTranslation(-psc.x, -psc.y, -psc.z);

		if (!pscalingrotation)
		{
			//m2.Identity();
			//m4.Identity();
		}
		else
		{
			m4 = pscalingrotation->ToMatrix4();
			m2 = Matrix4::Invert(m4);
		}
		if (!pscaling)
		{
			//D3DXMatrixIdentity(&m3);
		}
		else
		{
			m3 = Matrix4::CreateScale(pscaling->x, pscaling->y, pscaling->z);
		}
		if (!protation)
		{
			//D3DXMatrixIdentity(&m6);
		}
		else
		{
			m6 = protation->ToMatrix4();
		}

		m5 = Matrix4::CreateTranslation(psc.x - prc.x, psc.y - prc.y, psc.z - prc.z);
		//D3DXMatrixTranslation(&m5, psc.x - prc.x,  psc.y - prc.y,  psc.z - prc.z);
		m7 = Matrix4::CreateTranslation(prc.x + pt.x, prc.y + pt.y, prc.z + pt.z);
		//D3DXMatrixTranslation(&m7, prc.x + pt.x, prc.y + pt.y, prc.z + pt.z);

		p1 = m1 * m2;
		p2 = p1 * m3;
		p3 = p2 * m4;
		p4 = p3 * m5;
		p5 = p4 * m6;
		*this = p5 * m7;
	}

	Matrix4 Matrix4::Add(Matrix4 matrix1, Matrix4 matrix2)
	{
		matrix1.m11 += matrix2.m11;
		matrix1.m12 += matrix2.m12;
		matrix1.m13 += matrix2.m13;
		matrix1.m14 += matrix2.m14;
		matrix1.m21 += matrix2.m21;
		matrix1.m22 += matrix2.m22;
		matrix1.m23 += matrix2.m23;
		matrix1.m24 += matrix2.m24;
		matrix1.m31 += matrix2.m31;
		matrix1.m32 += matrix2.m32;
		matrix1.m33 += matrix2.m33;
		matrix1.m34 += matrix2.m34;
		matrix1.m41 += matrix2.m41;
		matrix1.m42 += matrix2.m42;
		matrix1.m43 += matrix2.m43;
		matrix1.m44 += matrix2.m44;
		return matrix1;
	}

	Vector3F Matrix4::Transform(const Vector3F& v, float w) const
	{
		return Vector3F(v.x * m11 + v.y * m21 + v.z * m31 + w * m41,
		                v.x * m12 + v.y * m22 + v.z * m32 + w * m42,
		                v.x * m13 + v.y * m23 + v.z * m33 + w * m43);
	}

	Vector4F Matrix4::Transform(const Vector4F& v) const
	{
		return Vector4F(v.x * m11 + v.y * m21 + v.z * m31 + v.w * m41,
		                v.x * m12 + v.y * m22 + v.z * m32 + v.w * m42,
		                v.x * m13 + v.y * m23 + v.z * m33 + v.w * m43,
		                v.x * m14 + v.y * m24 + v.z * m34 + v.w * m44);
	}

	Vector3F Matrix4::Transform(const Vector3F& position)
	{
		Vector3F result;
		result.x = position.x * m11 + position.y * m21 + position.z * m31 + m41;
		result.y = position.x * m12 + position.y * m22 + position.z * m32 + m42;
		result.z = position.x * m13 + position.y * m23 + position.z * m33 + m43;
		return result;
	}

	void Matrix4::Transform(const std::vector<Vector3F>& sourceArray, std::vector<Vector3F>& destinationArray)
	{
		CA_ASSERT(destinationArray.size() >= sourceArray.size(), "The destination array is smaller than the source array.");

		int i = 0;

		for (auto it = sourceArray.cbegin();
		     it != sourceArray.cend();
		     ++it)
		{
			Vector3F position = *it;
			destinationArray[i] = Vector3F(
				position.x * m11 + position.y * m21 + position.z * m31 + m41,
				position.x * m12 + position.y * m22 + position.z * m32 + m42,
				position.x * m13 + position.y * m23 + position.z * m33 + m43);
			i++;
		}
	}

	void Matrix4::TransformNormal(const Vector3F& normal, Vector3F& result) const
	{
		result = Vector3F(
			normal.x * m11 + normal.y * m21 + normal.z * m31,
			normal.x * m12 + normal.y * m22 + normal.z * m32,
			normal.x * m13 + normal.y * m23 + normal.z * m33);
	}

	Matrix4 Matrix4::CreateBillboard(Vector3F objectPosition, Vector3F cameraPosition, Vector3F cameraUpVector,
	                                 Vector3F* cameraForwardVector)
	{
		Matrix4 result;

		Vector3F vector;
		Vector3F vector2;
		Vector3F vector3;
		vector.x = objectPosition.x - cameraPosition.x;
		vector.y = objectPosition.y - cameraPosition.y;
		vector.z = objectPosition.z - cameraPosition.z;
		const float num = vector.LengthSquared();
		if (num < 0.0001f)
		{
			vector = cameraForwardVector != nullptr ? -*cameraForwardVector : Vector3F::Forward();
		}
		else
		{
			vector *= 1.0f / sqrtf(num);
		}
		vector3 = Vector3F::Cross(cameraUpVector, vector);
		vector3.Normalize();
		vector2 = Vector3F::Cross(vector, vector3);
		result.m11 = vector3.x;
		result.m12 = vector3.y;
		result.m13 = vector3.z;
		result.m14 = 0;
		result.m21 = vector2.x;
		result.m22 = vector2.y;
		result.m23 = vector2.z;
		result.m24 = 0;
		result.m31 = vector.x;
		result.m32 = vector.y;
		result.m33 = vector.z;
		result.m34 = 0;
		result.m41 = objectPosition.x;
		result.m42 = objectPosition.y;
		result.m43 = objectPosition.z;
		result.m44 = 1;

		return result;
	}

	Matrix4 Matrix4::CreateConstrainedBillboard(Vector3F objectPosition, Vector3F cameraPosition, Vector3F rotateAxis,
		Vector3F* cameraForwardVector, Vector3F* objectForwardVector)
	{
		Matrix4 result;

		float num;
		Vector3F vector;
		Vector3F vector2;
		Vector3F vector3;
		vector2.x = objectPosition.x - cameraPosition.x;
		vector2.y = objectPosition.y - cameraPosition.y;
		vector2.z = objectPosition.z - cameraPosition.z;
		const float num2 = vector2.LengthSquared();
		if (num2 < 0.0001f)
		{
			vector2 = cameraForwardVector != nullptr ? -*cameraForwardVector : Vector3F::Forward();
		}
		else
		{
			vector2 *= 1.0f / sqrtf(num2);
		}
		const Vector3F vector4 = rotateAxis;
		num = Vector3F::Dot(rotateAxis, vector2);
		if (fabsf(num) > 0.9982547f)
		{
			if (objectForwardVector != nullptr)
			{
				vector = *objectForwardVector;
				num = Vector3F::Dot(rotateAxis, vector);
				if (fabsf(num) > 0.9982547f)
				{
					num = ((rotateAxis.x * Vector3F::Forward().x) + (rotateAxis.y * Vector3F::Forward().y)) + (rotateAxis.z * Vector3F::Forward().z);
					vector = (fabsf(num) > 0.9982547f) ? Vector3F::Right() : Vector3F::Forward();
				}
			}
			else
			{
				num = ((rotateAxis.x * Vector3F::Forward().x) + (rotateAxis.y * Vector3F::Forward().y)) + (rotateAxis.z * Vector3F::Forward().z);
				vector = (fabsf(num) > 0.9982547f) ? Vector3F::Right() : Vector3F::Forward();
			}
			vector3 = Vector3F::Cross(rotateAxis, vector);
			vector3.Normalize();
			vector = Vector3F::Cross(vector3, rotateAxis);
			vector.Normalize();
		}
		else
		{
			vector3 = Vector3F::Cross(rotateAxis, vector2);
			vector3.Normalize();
			vector = Vector3F::Cross(vector3, vector4);
			vector.Normalize();
		}
		result.m11 = vector3.x;
		result.m12 = vector3.y;
		result.m13 = vector3.z;
		result.m14 = 0;
		result.m21 = vector4.x;
		result.m22 = vector4.y;
		result.m23 = vector4.z;
		result.m24 = 0;
		result.m31 = vector.x;
		result.m32 = vector.y;
		result.m33 = vector.z;
		result.m34 = 0;
		result.m41 = objectPosition.x;
		result.m42 = objectPosition.y;
		result.m43 = objectPosition.z;
		result.m44 = 1;

		return result;
	}

	Matrix4 Matrix4::CreateFromAxisAngle(Vector3F axis, float angle)
	{
		Matrix4 result;

		const float x = axis.x;
		const float y = axis.y;
		const float z = axis.z;
		const float num2 = sinf(angle);
		const float num = cosf(angle);
		const float num11 = x * x;
		const float num10 = y * y;
		const float num9 = z * z;
		const float num8 = x * y;
		const float num7 = x * z;
		const float num6 = y * z;
		result.m11 = num11 + (num * (1.0f - num11));
		result.m12 = (num8 - (num * num8)) + (num2 * z);
		result.m13 = (num7 - (num * num7)) - (num2 * y);
		result.m14 = 0;
		result.m21 = (num8 - (num * num8)) - (num2 * z);
		result.m22 = num10 + (num * (1.0f - num10));
		result.m23 = (num6 - (num * num6)) + (num2 * x);
		result.m24 = 0;
		result.m31 = (num7 - (num * num7)) + (num2 * y);
		result.m32 = (num6 - (num * num6)) - (num2 * x);
		result.m33 = num9 + (num * (1.0f - num9));
		result.m34 = 0;
		result.m41 = 0;
		result.m42 = 0;
		result.m43 = 0;
		result.m44 = 1;

		return result;
	}

	Matrix4 Matrix4::CreateFromQuaternion(Quaternion quaternion)
	{
		Matrix4 result;

		const float num9 = quaternion.x * quaternion.x;
		const float num8 = quaternion.y * quaternion.y;
		const float num7 = quaternion.z * quaternion.z;
		const float num6 = quaternion.x * quaternion.y;
		const float num5 = quaternion.z * quaternion.w;
		const float num4 = quaternion.z * quaternion.x;
		const float num3 = quaternion.y * quaternion.w;
		const float num2 = quaternion.y * quaternion.z;
		const float num = quaternion.x * quaternion.w;
		result.m11 = 1.0f - (2.0f * (num8 + num7));
		result.m12 = 2.0f * (num6 + num5);
		result.m13 = 2.0f * (num4 - num3);
		result.m14 = 0.0f;
		result.m21 = 2.0f * (num6 - num5);
		result.m22 = 1.0f - (2.0f * (num7 + num9));
		result.m23 = 2.0f * (num2 + num);
		result.m24 = 0.0f;
		result.m31 = 2.0f * (num4 + num3);
		result.m32 = 2.0f * (num2 - num);
		result.m33 = 1.0f - (2.0f * (num8 + num9));
		result.m34 = 0.0f;
		result.m41 = 0.0f;
		result.m42 = 0.0f;
		result.m43 = 0.0f;
		result.m44 = 1.0f;

		return result;
	}

	Matrix4 Matrix4::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
	{
		Quaternion quaternion;
		quaternion.CreateFromYawPitchRoll(yaw, pitch, roll);
		return CreateFromQuaternion(quaternion);
	}

	Matrix4 Matrix4::CreateLookAt(Vector3F cameraPosition, Vector3F cameraTarget, Vector3F cameraUpVector)
	{
		Matrix4 result;

		//auto view = (cameraPosition - cameraTarget);
		auto view = (cameraTarget - cameraPosition);
		view.Normalize();
		auto right = Vector3F::Cross(cameraUpVector, view);
		right.Normalize();
		const auto up = Vector3F::Cross(view, right);
		result.m11 = right.x;
		result.m12 = up.x;
		result.m13 = view.x;
		result.m14 = 0.0f;
		result.m21 = right.y;
		result.m22 = up.y;
		result.m23 = view.y;
		result.m24 = 0.0f;
		result.m31 = right.z;
		result.m32 = up.z;
		result.m33 = view.z;
		result.m34 = 0.0f;
		result.m41 = -Vector3F::Dot(right, cameraPosition);
		result.m42 = -Vector3F::Dot(up, cameraPosition);
		result.m43 = -Vector3F::Dot(view, cameraPosition);
		result.m44 = 1.0f;

		return result;
	}

	Matrix4 Matrix4::CreateOrthographic(float width, float height, float _near, float _far)
	{
		return CreateOrthographicOffCenter(0.0f, width, height, 0.0f, _near, _far);
	}

	Matrix4 Matrix4::CreateOrthographicOffCenter(float _left, float _right, float _bottom, float _top, float _near, float _far)
	{
		Matrix4 result;

		const float aa = 2.0f / (_right - _left);
		const float bb = 2.0f / (_top - _bottom);
		const float cc = 1.0f / (_far - _near);
		const float dd = (_left + _right) / (_left - _right);
		const float ee = (_top + _bottom) / (_bottom - _top);
		const float ff = _near / (_near - _far);

		/*result.m11 = aa;	result.m12 = 0.0f; result.m13 = 0.0f; result.m14 = dd;
		result.m21 = 0.0f;	result.m22 = bb;   result.m23 = 0.0f; result.m24 = ee;
		result.m31 = 0.0f;	result.m32 = 0.0f; result.m33 = 1.0f; result.m34 = ff;
		result.m41 = 0.0f;	result.m42 = 0.0f; result.m43 = 0.0f; result.m44 = 1.0f;*/

		//bgfx
		result.m11 = aa;	result.m12 = 0.0f;  result.m13 = 0.0f;  result.m14 = 0.0f;
		result.m21 = 0.0f;	result.m22 = bb;	result.m23 = 0.0f;  result.m24 = 0.0f;
		result.m31 = 0.0f;	result.m32 = 0.0f;  result.m33 = cc;	result.m34 = 0.0f;
		result.m41 = dd;	result.m42 = ee;	result.m43 = ff;	result.m44 = 1.0f;
		//result.m41 = dd +_offset

		return result;
	}

	Matrix4 Matrix4::CreatePerspective(float width, float height, float nearPlaneDistance, float farPlaneDistance)
	{
		if (nearPlaneDistance <= 0.0f)
		{
			throw CArgumentException("nearPlaneDistance <= 0");
		}
		if (farPlaneDistance <= 0.0f)
		{
			throw CArgumentException("farPlaneDistance <= 0");
		}
		if (nearPlaneDistance >= farPlaneDistance)
		{
			throw CArgumentException("nearPlaneDistance >= farPlaneDistance");
		}

		Matrix4 result;

		const auto negFarRange = isNaN(farPlaneDistance) ? -1.0f : farPlaneDistance / (nearPlaneDistance - farPlaneDistance);

		result.m11 = (2.0f * nearPlaneDistance) / width;
		result.m12 = result.m13 = result.m14 = 0.0f;
		result.m22 = (2.0f * nearPlaneDistance) / height;
		result.m21 = result.m23 = result.m24 = 0.0f;
		result.m33 = negFarRange;
		result.m31 = result.m32 = 0.0f;
		result.m34 = -1.0f;
		result.m41 = result.m42 = result.m44 = 0.0f;
		result.m43 = nearPlaneDistance * negFarRange;

		return result;
	}

	Matrix4 Matrix4::CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance)
	{
		if ((fieldOfView <= 0.0f) || (fieldOfView >= 3.141593f))
		{
			throw CArgumentException("fieldOfView <= 0 or >= PI");
		}
		if (nearPlaneDistance < 0.0f)
		{
			throw CArgumentException("nearPlaneDistance <= 0");
		}
		if (farPlaneDistance <= 0.0f)
		{
			throw CArgumentException("farPlaneDistance <= 0");
		}
		if (nearPlaneDistance >= farPlaneDistance)
		{
			throw CArgumentException("nearPlaneDistance >= farPlaneDistance");
		}

		Matrix4 result;

		/*const auto yScale = 1.0f / tanf(fieldOfView * 0.5f);
		const auto xScale = yScale / aspectRatio;
		const auto negFarRange = isNaN(farPlaneDistance) ? -1.0f : farPlaneDistance / (farPlaneDistance - nearPlaneDistance);

		result.m11 = xScale;
		result.m12 = result.m13 = result.m14 = 0.0f;
		result.m22 = yScale;
		result.m21 = result.m23 = result.m24 = 0.0f;
		result.m31 = result.m32 = 0.0f;
		result.m33 = negFarRange;
		result.m34 = -1.0f;
		result.m41 = result.m42 = result.m44 = 0.0f;
		result.m43 = nearPlaneDistance * negFarRange;*/

		float YScale = 1.0f / std::tan(fieldOfView / 2.0f);
		float XScale = YScale / aspectRatio;
		float Coeff = farPlaneDistance / (farPlaneDistance - nearPlaneDistance);

		//TODO : righthanded : XScale = -XScale;
		//TODO : lefthanded : XScale = XScale;

		result.m11 = XScale; result.m21 = 0.0f;   result.m31 = 0.0f;  result.m41 = 0.0f;
		result.m12 = 0.0f;   result.m22 = YScale; result.m32 = 0.0f;  result.m42 = 0.0f;
		result.m13 = 0.0f;   result.m23 = 0.0f;   result.m33 = Coeff; result.m43 = nearPlaneDistance * -Coeff;
		result.m14 = 0.0f;   result.m24 = 0.0f;   result.m34 = 1.0f;  result.m44 = 0.0f;
																			   
		return result;														   

		/*
		
		const float height = 1.0f / tan(toRad(_fovy) * 0.5f);
		const float width = height * 1.0f / _aspect;

		bool _homogeneousNdc = false;
		bx::Handness _handness = Handness::Left;
		const float diff = _far - _near;
		const float aa = _homogeneousNdc ? (_far + _near) / diff : _far / diff;
		const float bb = _homogeneousNdc ? (2.0f * _far * _near) / diff : _near * aa;

		memSet(_result, 0, sizeof(float) * 16);
		_result[0] = _width;
		_result[5] = _height;
		_result[8] = (Handness::Right == _handness) ? _x : -_x;
		_result[9] = (Handness::Right == _handness) ? _y : -_y;
		_result[10] = (Handness::Right == _handness) ? -aa : aa;
		_result[11] = (Handness::Right == _handness) ? -1.0f : 1.0f;
		_result[14] = -bb;*/
	}

	Matrix4 Matrix4::CreatePerspectiveFieldOfView2(float fieldOfView, float aspectRatio, float nearPlaneDistance,
		float farPlaneDistance)
	{
		Matrix4 result;

		float YScale = 1.0f / std::tan(fieldOfView / 2.0f);
		float XScale = YScale / aspectRatio;
		float Coeff = farPlaneDistance / (farPlaneDistance - nearPlaneDistance);

		//TODO : righthanded : XScale = -XScale;
		//TODO : lefthanded : XScale = XScale;

		result.m11 = XScale; result.m12 = 0.0f;   result.m13 = 0.0f;  result.m14 = 0.0f;
		result.m21 = 0.0f;   result.m22 = YScale; result.m23 = 0.0f;  result.m24 = 0.0f;
		result.m31 = 0.0f;   result.m32 = 0.0f;   result.m33 = Coeff; result.m34 = nearPlaneDistance * -Coeff;
		result.m41 = 0.0f;   result.m42 = 0.0f;   result.m43 = 1.0f;  result.m44 = 0.0f;

		return result;
	}

	Matrix4 Matrix4::CreatePerspectiveOffCenter(float left, float right, float bottom, float top,
		float nearPlaneDistance, float farPlaneDistance)
	{
		if (nearPlaneDistance <= 0.0f)
		{
			throw CArgumentException("nearPlaneDistance <= 0");
		}
		if (farPlaneDistance <= 0.0f)
		{
			throw CArgumentException("farPlaneDistance <= 0");
		}
		if (nearPlaneDistance >= farPlaneDistance)
		{
			throw CArgumentException("nearPlaneDistance >= farPlaneDistance");
		}

		Matrix4 result;

		result.m11 = (2.0f * nearPlaneDistance) / (right - left);
		result.m12 = result.m13 = result.m14 = 0;
		result.m22 = (2.0f * nearPlaneDistance) / (top - bottom);
		result.m21 = result.m23 = result.m24 = 0;
		result.m31 = (left + right) / (right - left);
		result.m32 = (top + bottom) / (top - bottom);
		result.m33 = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
		result.m34 = -1;
		result.m43 = (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance);
		result.m41 = result.m42 = result.m44 = 0;

		return result;
	}

	Matrix4 Matrix4::CreatePerspectiveOffCenter(RectangleF viewingVolume, float nearPlaneDistance,
		float farPlaneDistance)
	{
		return CreatePerspectiveOffCenter(viewingVolume.Left(), viewingVolume.Right(), viewingVolume.Bottom(), viewingVolume.Top(), nearPlaneDistance, farPlaneDistance);
	}

	Matrix4 Matrix4::CreateRotationX(float radians)
	{
		Matrix4 result;
		result.Identity();

		const auto val1 = cosf(radians);
		const auto val2 = sinf(radians);

		result.m22 = val1;
		result.m23 = val2;
		result.m32 = -val2;
		result.m33 = val1;

		return result;
	}

	Matrix4 Matrix4::CreateRotationY(float radians)
	{
		Matrix4 result;

		const auto val1 = cosf(radians);
		const auto val2 = sinf(radians);

		result.m11 = val1;
		result.m13 = -val2;
		result.m31 = val2;
		result.m33 = val1;

		return result;
	}

	Matrix4 Matrix4::CreateRotationZ(float radians)
	{
		Matrix4 result;

		const auto val1 = cosf(radians);
		const auto val2 = sinf(radians);

		result.m11 = val1;
		result.m12 = val2;
		result.m21 = -val2;
		result.m22 = val1;

		return result;
	}

	Matrix4 Matrix4::CreateScale(float scale)
	{
		return CreateScale(scale, scale, scale);
	}

	Matrix4 Matrix4::CreateScale(float xScale, float yScale, float zScale)
	{
		Matrix4 result;

		result.m11 = xScale;
		result.m12 = 0;
		result.m13 = 0;
		result.m14 = 0;
		result.m21 = 0;
		result.m22 = yScale;
		result.m23 = 0;
		result.m24 = 0;
		result.m31 = 0;
		result.m32 = 0;
		result.m33 = zScale;
		result.m34 = 0;
		result.m41 = 0;
		result.m42 = 0;
		result.m43 = 0;
		result.m44 = 1;

		return result;
	}

	Matrix4 Matrix4::CreateScale(Vector3F scales)
	{
		return CreateScale(scales.x, scales.y, scales.z);
	}

	Matrix4 Matrix4::CreateShadow(Vector3F lightDirection, Plane plane)
	{
		Matrix4 result;

		const float dot = (plane.n.x * lightDirection.x) + (plane.n.y * lightDirection.y) + (plane.n.z * lightDirection.z);
		const float x = -plane.n.x;
		const float y = -plane.n.y;
		const float z = -plane.n.z;
		const float d = -plane.d;

		result.m11 = (x * lightDirection.x) + dot;
		result.m12 = x * lightDirection.y;
		result.m13 = x * lightDirection.z;
		result.m14 = 0;
		result.m21 = y * lightDirection.x;
		result.m22 = (y * lightDirection.y) + dot;
		result.m23 = y * lightDirection.z;
		result.m24 = 0;
		result.m31 = z * lightDirection.x;
		result.m32 = z * lightDirection.y;
		result.m33 = (z * lightDirection.z) + dot;
		result.m34 = 0;
		result.m41 = d * lightDirection.x;
		result.m42 = d * lightDirection.y;
		result.m43 = d * lightDirection.z;
		result.m44 = dot;

		return result;
	}

	Matrix4 Matrix4::CreateTranslation(float xPosition, float yPosition, float zPosition)
	{
		Matrix4 result;

		result.m41 = xPosition;
		result.m42 = yPosition;
		result.m43 = zPosition;

		return result;
	}

	Matrix4 Matrix4::CreateTranslation(Vector3F position)
	{
		return CreateTranslation(position.x, position.y, position.z);
	}

	Matrix4 Matrix4::CreateReflection(Plane value)
	{
		Matrix4 result;

		Plane plane = value;
		plane.Normalize();
		const float x = plane.n.x;
		const float y = plane.n.y;
		const float z = plane.n.z;
		const float num3 = -2.0f * x;
		const float num2 = -2.0f * y;
		const float num = -2.0f * z;
		result.m11 = (num3 * x) + 1.0f;
		result.m12 = num2 * x;
		result.m13 = num * x;
		result.m14 = 0;
		result.m21 = num3 * y;
		result.m22 = (num2 * y) + 1;
		result.m23 = num * y;
		result.m24 = 0;
		result.m31 = num3 * z;
		result.m32 = num2 * z;
		result.m33 = (num * z) + 1;
		result.m34 = 0;
		result.m41 = num3 * plane.d;
		result.m42 = num2 * plane.d;
		result.m43 = num * plane.d;
		result.m44 = 1;

		return result;
	}

	Matrix4 Matrix4::CreateWorld(Vector3F position, Vector3F forward, Vector3F up)
	{
		Matrix4 result;

		Vector3F x, y, z = forward;
		z.Normalize();
		x = Vector3F::Cross(forward, up);
		y = Vector3F::Cross(x, forward);
		x.Normalize();
		y.Normalize();

		result.Right(x);
		result.Up(y);
		result.Forward(z);
		result.Translation(position);
		result.m44 = 1.0f;

		return result;
	}

	bool Matrix4::Decompose(Vector3F& scale, Quaternion& rotation, Vector3F& translation)
	{
		translation.x = m41;
		translation.y = m42;
		translation.z = m43;

		const float xs = (Sign(m11 * m12 * m13 * m14) < 0) ? -1 : 1;
		const float ys = (Sign(m21 * m22 * m23 * m24) < 0) ? -1 : 1;
		const float zs = (Sign(m31 * m32 * m33 * m34) < 0) ? -1 : 1;

		scale.x = xs * sqrtf(m11 * m11 + m12 * m12 + m13 * m13);
		scale.y = ys * sqrtf(m21 * m21 + m22 * m22 + m23 * m23);
		scale.z = zs * sqrtf(m31 * m31 + m32 * m32 + m33 * m33);

		if (scale.x == 0.0 || scale.y == 0.0 || scale.z == 0.0)
		{
			rotation.Identity();
			return false;
		}

		Matrix4 m1(m11 / scale.x, m12 / scale.x, m13 / scale.x, 0,
			m21 / scale.y, m22 / scale.y, m23 / scale.y, 0,
			m31 / scale.z, m32 / scale.z, m33 / scale.z, 0,
			0, 0, 0, 1);
		rotation.FromMatrix(m1);
		//rotation = Quaternion::CreateFromRotationMatrix(m1);
		return true;
	}

	float Matrix4::Determinant() const
	{
		const float num22 = m11;
		const float num21 = m12;
		const float num20 = m13;
		const float num19 = m14;
		const float num12 = m21;
		const float num11 = m22;
		const float num10 = m23;
		const float num9 = m24;
		const float num8 = m31;
		const float num7 = m32;
		const float num6 = m33;
		const float num5 = m34;
		const float num4 = m41;
		const float num3 = m42;
		const float num2 = m43;
		const float num = m44;
		const float num18 = (num6 * num) - (num5 * num2);
		const float num17 = (num7 * num) - (num5 * num3);
		const float num16 = (num7 * num2) - (num6 * num3);
		const float num15 = (num8 * num) - (num5 * num4);
		const float num14 = (num8 * num2) - (num6 * num4);
		const float num13 = (num8 * num3) - (num7 * num4);
		return ((((num22 * (((num11 * num18) - (num10 * num17)) + (num9 * num16))) - (num21 * (((num12 * num18) - (num10 * num15)) + (num9 * num14)))) + (num20 * (((num12 * num17) - (num11 * num15)) + (num9 * num13)))) - (num19 * (((num12 * num16) - (num11 * num14)) + (num10 * num13))));
	}

	Matrix4 Matrix4::Divide(Matrix4 matrix1, float divider)
	{
		const float num = 1.0f / divider;
		matrix1.m11 = matrix1.m11 * num;
		matrix1.m12 = matrix1.m12 * num;
		matrix1.m13 = matrix1.m13 * num;
		matrix1.m14 = matrix1.m14 * num;
		matrix1.m21 = matrix1.m21 * num;
		matrix1.m22 = matrix1.m22 * num;
		matrix1.m23 = matrix1.m23 * num;
		matrix1.m24 = matrix1.m24 * num;
		matrix1.m31 = matrix1.m31 * num;
		matrix1.m32 = matrix1.m32 * num;
		matrix1.m33 = matrix1.m33 * num;
		matrix1.m34 = matrix1.m34 * num;
		matrix1.m41 = matrix1.m41 * num;
		matrix1.m42 = matrix1.m42 * num;
		matrix1.m43 = matrix1.m43 * num;
		matrix1.m44 = matrix1.m44 * num;
		return matrix1;
	}

	Matrix4 Matrix4::Invert(Matrix4 matrix)
	{
		Matrix4 result;

		const float num1 = matrix.m11;
		const float num2 = matrix.m12;
		const float num3 = matrix.m13;
		const float num4 = matrix.m14;
		const float num5 = matrix.m21;
		const float num6 = matrix.m22;
		const float num7 = matrix.m23;
		const float num8 = matrix.m24;
		const float num9 = matrix.m31;
		const float num10 = matrix.m32;
		const float num11 = matrix.m33;
		const float num12 = matrix.m34;
		const float num13 = matrix.m41;
		const float num14 = matrix.m42;
		const float num15 = matrix.m43;
		const float num16 = matrix.m44;
		const float num17 = num11 * num16 - num12 * num15;
		const float num18 = num10 * num16 - num12 * num14;
		const float num19 = num10 * num15 - num11 * num14;
		const float num20 = num9 * num16 - num12 * num13;
		const float num21 = num9 * num15 - num11 * num13;
		const float num22 = num9 * num14 - num10 * num13;
		const float num23 = num6 * num17 - num7 * num18 + num8 * num19;
		const float num24 = -(num5 * num17 - num7 * num20 + num8 * num21);
		const float num25 = num5 * num18 - num6 * num20 + num8 * num22;
		const float num26 = -(num5 * num19 - num6 * num21 + num7 * num22);
		const float num27 = (float)(1.0 / (num1 * num23 + num2 * num24 + num3 * num25 + num4 * num26));

		result.m11 = num23 * num27;
		result.m21 = num24 * num27;
		result.m31 = num25 * num27;
		result.m41 = num26 * num27;
		result.m12 = -(num2 * num17 - num3 * num18 + num4 * num19) * num27;
		result.m22 = (num1 * num17 - num3 * num20 + num4 * num21) * num27;
		result.m32 = -(num1 * num18 - num2 * num20 + num4 * num22) * num27;
		result.m42 = (num1 * num19 - num2 * num21 + num3 * num22) * num27;
		const float num28 = num7 * num16 - num8 * num15;
		const float num29 = num6 * num16 - num8 * num14;
		const float num30 = num6 * num15 - num7 * num14;
		const float num31 = num5 * num16 - num8 * num13;
		const float num32 = num5 * num15 - num7 * num13;
		const float num33 = num5 * num14 - num6 * num13;
		result.m13 = (num2 * num28 - num3 * num29 + num4 * num30) * num27;
		result.m23 = -(num1 * num28 - num3 * num31 + num4 * num32) * num27;
		result.m33 = (num1 * num29 - num2 * num31 + num4 * num33) * num27;
		result.m43 = -(num1 * num30 - num2 * num32 + num3 * num33) * num27;
		const float num34 = num7 * num12 - num8 * num11;
		const float num35 = num6 * num12 - num8 * num10;
		const float num36 = num6 * num11 - num7 * num10;
		const float num37 = num5 * num12 - num8 * num9;
		const float num38 = num5 * num11 - num7 * num9;
		const float num39 = num5 * num10 - num6 * num9;
		result.m14 = -(num2 * num34 - num3 * num35 + num4 * num36) * num27;
		result.m24 = (num1 * num34 - num3 * num37 + num4 * num38) * num27;
		result.m34 = -(num1 * num35 - num2 * num37 + num4 * num39) * num27;
		result.m44 = (num1 * num36 - num2 * num38 + num3 * num39) * num27;

		return result;
	}

	Matrix4 Matrix4::Lerp(Matrix4 matrix1, Matrix4 matrix2, float amount)
	{
		Matrix4 result;

		result.m11 = matrix1.m11 + ((matrix2.m11 - matrix1.m11) * amount);
		result.m12 = matrix1.m12 + ((matrix2.m12 - matrix1.m12) * amount);
		result.m13 = matrix1.m13 + ((matrix2.m13 - matrix1.m13) * amount);
		result.m14 = matrix1.m14 + ((matrix2.m14 - matrix1.m14) * amount);
		result.m21 = matrix1.m21 + ((matrix2.m21 - matrix1.m21) * amount);
		result.m22 = matrix1.m22 + ((matrix2.m22 - matrix1.m22) * amount);
		result.m23 = matrix1.m23 + ((matrix2.m23 - matrix1.m23) * amount);
		result.m24 = matrix1.m24 + ((matrix2.m24 - matrix1.m24) * amount);
		result.m31 = matrix1.m31 + ((matrix2.m31 - matrix1.m31) * amount);
		result.m32 = matrix1.m32 + ((matrix2.m32 - matrix1.m32) * amount);
		result.m33 = matrix1.m33 + ((matrix2.m33 - matrix1.m33) * amount);
		result.m34 = matrix1.m34 + ((matrix2.m34 - matrix1.m34) * amount);
		result.m41 = matrix1.m41 + ((matrix2.m41 - matrix1.m41) * amount);
		result.m42 = matrix1.m42 + ((matrix2.m42 - matrix1.m42) * amount);
		result.m43 = matrix1.m43 + ((matrix2.m43 - matrix1.m43) * amount);
		result.m44 = matrix1.m44 + ((matrix2.m44 - matrix1.m44) * amount);

		return result;
	}

	Matrix4 Matrix4::Multiply(Matrix4 matrix1, float scaleFactor)
	{
		matrix1.m11 *= scaleFactor;
		matrix1.m12 *= scaleFactor;
		matrix1.m13 *= scaleFactor;
		matrix1.m14 *= scaleFactor;
		matrix1.m21 *= scaleFactor;
		matrix1.m22 *= scaleFactor;
		matrix1.m23 *= scaleFactor;
		matrix1.m24 *= scaleFactor;
		matrix1.m31 *= scaleFactor;
		matrix1.m32 *= scaleFactor;
		matrix1.m33 *= scaleFactor;
		matrix1.m34 *= scaleFactor;
		matrix1.m41 *= scaleFactor;
		matrix1.m42 *= scaleFactor;
		matrix1.m43 *= scaleFactor;
		matrix1.m44 *= scaleFactor;
		return matrix1;
	}

	float* Matrix4::ToFloatArray(Matrix4 matrix)
	{
		/*auto array = new float[] {
								matrix.M11, matrix.M12, matrix.M13, matrix.M14,
								matrix.M21, matrix.M22, matrix.M23, matrix.M24,
								matrix.M31, matrix.M32, matrix.M33, matrix.M34,
								matrix.M41, matrix.M42, matrix.M43, matrix.M44
		};
		return array;*/
		return &matrix.m11;
	}

	Matrix4 Matrix4::Negate(Matrix4 matrix)
	{
		matrix.m11 = -matrix.m11;
		matrix.m12 = -matrix.m12;
		matrix.m13 = -matrix.m13;
		matrix.m14 = -matrix.m14;
		matrix.m21 = -matrix.m21;
		matrix.m22 = -matrix.m22;
		matrix.m23 = -matrix.m23;
		matrix.m24 = -matrix.m24;
		matrix.m31 = -matrix.m31;
		matrix.m32 = -matrix.m32;
		matrix.m33 = -matrix.m33;
		matrix.m34 = -matrix.m34;
		matrix.m41 = -matrix.m41;
		matrix.m42 = -matrix.m42;
		matrix.m43 = -matrix.m43;
		matrix.m44 = -matrix.m44;
		return matrix;
	}

	bool Matrix4::operator==(const Matrix4& m) const
	{
		return std::fabs(m11 - m.m11) < std::numeric_limits<float>::epsilon() && std::fabs(m12 - m.m12) < std::numeric_limits<float>::epsilon() &&
			std::fabs(m13 - m.m13) < std::numeric_limits<float>::epsilon() && std::fabs(m14 - m.m14) < std::numeric_limits<float>::epsilon() &&
			std::fabs(m21 - m.m21) < std::numeric_limits<float>::epsilon() && std::fabs(m22 - m.m22) < std::numeric_limits<float>::epsilon() &&
			std::fabs(m23 - m.m23) < std::numeric_limits<float>::epsilon() && std::fabs(m24 - m.m24) < std::numeric_limits<float>::epsilon() &&
			std::fabs(m31 - m.m31) < std::numeric_limits<float>::epsilon() && std::fabs(m32 - m.m32) < std::numeric_limits<float>::epsilon() &&
			std::fabs(m33 - m.m33) < std::numeric_limits<float>::epsilon() && std::fabs(m34 - m.m34) < std::numeric_limits<float>::epsilon() &&
			std::fabs(m41 - m.m41) < std::numeric_limits<float>::epsilon() && std::fabs(m42 - m.m42) < std::numeric_limits<float>::epsilon() &&
			std::fabs(m43 - m.m43) < std::numeric_limits<float>::epsilon() && std::fabs(m44 - m.m44) < std::numeric_limits<float>::epsilon();
	}

	bool Matrix4::operator!=(const Matrix4& m) const
	{
		return !(*this == m);
	}

	Matrix4& Matrix4::operator+(const Matrix4& matrix2)
	{
		m11 += matrix2.m11;
		m12 += matrix2.m12;
		m13 += matrix2.m13;
		m14 += matrix2.m14;
		m21 += matrix2.m21;
		m22 += matrix2.m22;
		m23 += matrix2.m23;
		m24 += matrix2.m24;
		m31 += matrix2.m31;
		m32 += matrix2.m32;
		m33 += matrix2.m33;
		m34 += matrix2.m34;
		m41 += matrix2.m41;
		m42 += matrix2.m42;
		m43 += matrix2.m43;
		m44 += matrix2.m44;
		return *this;
	}

	Matrix4& Matrix4::operator/(const Matrix4& matrix2)
	{
		m11 /= matrix2.m11;
		m12 /= matrix2.m12;
		m13 /= matrix2.m13;
		m14 /= matrix2.m14;
		m21 /= matrix2.m21;
		m22 /= matrix2.m22;
		m23 /= matrix2.m23;
		m24 /= matrix2.m24;
		m31 /= matrix2.m31;
		m32 /= matrix2.m32;
		m33 /= matrix2.m33;
		m34 /= matrix2.m34;
		m41 /= matrix2.m41;
		m42 /= matrix2.m42;
		m43 /= matrix2.m43;
		m44 /= matrix2.m44;
		return *this;
	}

	Matrix4 Matrix4::operator/(float divider)
	{
		const float num = 1.0f / divider;
		m11 *= num;
		m12 *= num;
		m13 *= num;
		m14 *= num;
		m21 *= num;
		m22 *= num;
		m23 *= num;
		m24 *= num;
		m31 *= num;
		m32 *= num;
		m33 *= num;
		m34 *= num;
		m41 *= num;
		m42 *= num;
		m43 *= num;
		m44 *= num;
		return *this;
	}

	Matrix4 Matrix4::operator*(const Matrix4& matrix2)
	{
		const auto a11 = (((m11 * matrix2.m11) + (m12 * matrix2.m21)) + (m13 * matrix2.m31)) + (m14 * matrix2.m41);
		const auto a12 = (((m11 * matrix2.m12) + (m12 * matrix2.m22)) + (m13 * matrix2.m32)) + (m14 * matrix2.m42);
		const auto a13 = (((m11 * matrix2.m13) + (m12 * matrix2.m23)) + (m13 * matrix2.m33)) + (m14 * matrix2.m43);
		const auto a14 = (((m11 * matrix2.m14) + (m12 * matrix2.m24)) + (m13 * matrix2.m34)) + (m14 * matrix2.m44);
		const auto a21 = (((m21 * matrix2.m11) + (m22 * matrix2.m21)) + (m23 * matrix2.m31)) + (m24 * matrix2.m41);
		const auto a22 = (((m21 * matrix2.m12) + (m22 * matrix2.m22)) + (m23 * matrix2.m32)) + (m24 * matrix2.m42);
		const auto a23 = (((m21 * matrix2.m13) + (m22 * matrix2.m23)) + (m23 * matrix2.m33)) + (m24 * matrix2.m43);
		const auto a24 = (((m21 * matrix2.m14) + (m22 * matrix2.m24)) + (m23 * matrix2.m34)) + (m24 * matrix2.m44);
		const auto a31 = (((m31 * matrix2.m11) + (m32 * matrix2.m21)) + (m33 * matrix2.m31)) + (m34 * matrix2.m41);
		const auto a32 = (((m31 * matrix2.m12) + (m32 * matrix2.m22)) + (m33 * matrix2.m32)) + (m34 * matrix2.m42);
		const auto a33 = (((m31 * matrix2.m13) + (m32 * matrix2.m23)) + (m33 * matrix2.m33)) + (m34 * matrix2.m43);
		const auto a34 = (((m31 * matrix2.m14) + (m32 * matrix2.m24)) + (m33 * matrix2.m34)) + (m34 * matrix2.m44);
		const auto a41 = (((m41 * matrix2.m11) + (m42 * matrix2.m21)) + (m43 * matrix2.m31)) + (m44 * matrix2.m41);
		const auto a42 = (((m41 * matrix2.m12) + (m42 * matrix2.m22)) + (m43 * matrix2.m32)) + (m44 * matrix2.m42);
		const auto a43 = (((m41 * matrix2.m13) + (m42 * matrix2.m23)) + (m43 * matrix2.m33)) + (m44 * matrix2.m43);
		const auto a44 = (((m41 * matrix2.m14) + (m42 * matrix2.m24)) + (m43 * matrix2.m34)) + (m44 * matrix2.m44);
		m11 = a11;
		m12 = a12;
		m13 = a13;
		m14 = a14;
		m21 = a21;
		m22 = a22;
		m23 = a23;
		m24 = a24;
		m31 = a31;
		m32 = a32;
		m33 = a33;
		m34 = a34;
		m41 = a41;
		m42 = a42;
		m43 = a43;
		m44 = a44;
		return *this;
	}

	const Matrix4& Matrix4::operator*=(const Matrix4& m)
	{
		*this = *this * m;
		return *this;
	}

	Matrix4 Matrix4::operator*(float scaleFactor)
	{
		m11 *= scaleFactor;
		m12 *= scaleFactor;
		m13 *= scaleFactor;
		m14 *= scaleFactor;
		m21 *= scaleFactor;
		m22 *= scaleFactor;
		m23 *= scaleFactor;
		m24 *= scaleFactor;
		m31 *= scaleFactor;
		m32 *= scaleFactor;
		m33 *= scaleFactor;
		m34 *= scaleFactor;
		m41 *= scaleFactor;
		m42 *= scaleFactor;
		m43 *= scaleFactor;
		m44 *= scaleFactor;
		return *this;
	}

	Matrix4 Matrix4::operator-(const Matrix4& matrix2)
	{
		m11 -= matrix2.m11;
		m12 -= matrix2.m12;
		m13 -= matrix2.m13;
		m14 -= matrix2.m14;
		m21 -= matrix2.m21;
		m22 -= matrix2.m22;
		m23 -= matrix2.m23;
		m24 -= matrix2.m24;
		m31 -= matrix2.m31;
		m32 -= matrix2.m32;
		m33 -= matrix2.m33;
		m34 -= matrix2.m34;
		m41 -= matrix2.m41;
		m42 -= matrix2.m42;
		m43 -= matrix2.m43;
		m44 -= matrix2.m44;
		return *this;
	}

	Matrix4 Matrix4::operator-()
	{
		m11 = -m11;
		m12 = -m12;
		m13 = -m13;
		m14 = -m14;
		m21 = -m21;
		m22 = -m22;
		m23 = -m23;
		m24 = -m24;
		m31 = -m31;
		m32 = -m32;
		m33 = -m33;
		m34 = -m34;
		m41 = -m41;
		m42 = -m42;
		m43 = -m43;
		m44 = -m44;
		return *this;
	}

	Matrix4 Matrix4::Subtract(Matrix4 matrix1, Matrix4 matrix2)
	{
		Matrix4 result;
		result.m11 = matrix1.m11 - matrix2.m11;
		result.m12 = matrix1.m12 - matrix2.m12;
		result.m13 = matrix1.m13 - matrix2.m13;
		result.m14 = matrix1.m14 - matrix2.m14;
		result.m21 = matrix1.m21 - matrix2.m21;
		result.m22 = matrix1.m22 - matrix2.m22;
		result.m23 = matrix1.m23 - matrix2.m23;
		result.m24 = matrix1.m24 - matrix2.m24;
		result.m31 = matrix1.m31 - matrix2.m31;
		result.m32 = matrix1.m32 - matrix2.m32;
		result.m33 = matrix1.m33 - matrix2.m33;
		result.m34 = matrix1.m34 - matrix2.m34;
		result.m41 = matrix1.m41 - matrix2.m41;
		result.m42 = matrix1.m42 - matrix2.m42;
		result.m43 = matrix1.m43 - matrix2.m43;
		result.m44 = matrix1.m44 - matrix2.m44;
		return result;
	}

	Matrix4 Matrix4::Transpose(Matrix4 matrix)
	{
		Matrix4 ret;

		ret.m11 = matrix.m11;
		ret.m12 = matrix.m21;
		ret.m13 = matrix.m31;
		ret.m14 = matrix.m41;

		ret.m21 = matrix.m12;
		ret.m22 = matrix.m22;
		ret.m23 = matrix.m32;
		ret.m24 = matrix.m42;

		ret.m31 = matrix.m13;
		ret.m32 = matrix.m23;
		ret.m33 = matrix.m33;
		ret.m34 = matrix.m43;

		ret.m41 = matrix.m14;
		ret.m42 = matrix.m24;
		ret.m43 = matrix.m34;
		ret.m44 = matrix.m44;

		return ret;
	}

	Matrix4 Matrix4::Multiply(Matrix4 matrix1, Matrix4 matrix2)
	{
		Matrix4 result;

		/*const auto m11 = (((matrix1.m11 * matrix2.m11) + (matrix1.m12 * matrix2.m21)) + (matrix1.m13 * matrix2.m31)) + (matrix1.m14 * matrix2.m41);
		const auto m12 = (((matrix1.m11 * matrix2.m12) + (matrix1.m12 * matrix2.m22)) + (matrix1.m13 * matrix2.m32)) + (matrix1.m14 * matrix2.m42);
		const auto m13 = (((matrix1.m11 * matrix2.m13) + (matrix1.m12 * matrix2.m23)) + (matrix1.m13 * matrix2.m33)) + (matrix1.m14 * matrix2.m43);
		const auto m14 = (((matrix1.m11 * matrix2.m14) + (matrix1.m12 * matrix2.m24)) + (matrix1.m13 * matrix2.m34)) + (matrix1.m14 * matrix2.m44);
		const auto m21 = (((matrix1.m21 * matrix2.m11) + (matrix1.m22 * matrix2.m21)) + (matrix1.m23 * matrix2.m31)) + (matrix1.m24 * matrix2.m41);
		const auto m22 = (((matrix1.m21 * matrix2.m12) + (matrix1.m22 * matrix2.m22)) + (matrix1.m23 * matrix2.m32)) + (matrix1.m24 * matrix2.m42);
		const auto m23 = (((matrix1.m21 * matrix2.m13) + (matrix1.m22 * matrix2.m23)) + (matrix1.m23 * matrix2.m33)) + (matrix1.m24 * matrix2.m43);
		const auto m24 = (((matrix1.m21 * matrix2.m14) + (matrix1.m22 * matrix2.m24)) + (matrix1.m23 * matrix2.m34)) + (matrix1.m24 * matrix2.m44);
		const auto m31 = (((matrix1.m31 * matrix2.m11) + (matrix1.m32 * matrix2.m21)) + (matrix1.m33 * matrix2.m31)) + (matrix1.m34 * matrix2.m41);
		const auto m32 = (((matrix1.m31 * matrix2.m12) + (matrix1.m32 * matrix2.m22)) + (matrix1.m33 * matrix2.m32)) + (matrix1.m34 * matrix2.m42);
		const auto m33 = (((matrix1.m31 * matrix2.m13) + (matrix1.m32 * matrix2.m23)) + (matrix1.m33 * matrix2.m33)) + (matrix1.m34 * matrix2.m43);
		const auto m34 = (((matrix1.m31 * matrix2.m14) + (matrix1.m32 * matrix2.m24)) + (matrix1.m33 * matrix2.m34)) + (matrix1.m34 * matrix2.m44);
		const auto m41 = (((matrix1.m41 * matrix2.m11) + (matrix1.m42 * matrix2.m21)) + (matrix1.m43 * matrix2.m31)) + (matrix1.m44 * matrix2.m41);
		const auto m42 = (((matrix1.m41 * matrix2.m12) + (matrix1.m42 * matrix2.m22)) + (matrix1.m43 * matrix2.m32)) + (matrix1.m44 * matrix2.m42);
		const auto m43 = (((matrix1.m41 * matrix2.m13) + (matrix1.m42 * matrix2.m23)) + (matrix1.m43 * matrix2.m33)) + (matrix1.m44 * matrix2.m43);
		const auto m44 = (((matrix1.m41 * matrix2.m14) + (matrix1.m42 * matrix2.m24)) + (matrix1.m43 * matrix2.m34)) + (matrix1.m44 * matrix2.m44);
		result.m11 = m11;
		result.m12 = m12;
		result.m13 = m13;
		result.m14 = m14;
		result.m21 = m21;
		result.m22 = m22;
		result.m23 = m23;
		result.m24 = m24;
		result.m31 = m31;
		result.m32 = m32;
		result.m33 = m33;
		result.m34 = m34;
		result.m41 = m41;
		result.m42 = m42;
		result.m43 = m43;
		result.m44 = m44;*/

		result = matrix1 * matrix2;

		return result;
	}

	Matrix4 Matrix4::Divide(Matrix4 matrix1, Matrix4 matrix2)
	{
		Matrix4 result;

		result.m11 = matrix1.m11 / matrix2.m11;
		result.m12 = matrix1.m12 / matrix2.m12;
		result.m13 = matrix1.m13 / matrix2.m13;
		result.m14 = matrix1.m14 / matrix2.m14;
		result.m21 = matrix1.m21 / matrix2.m21;
		result.m22 = matrix1.m22 / matrix2.m22;
		result.m23 = matrix1.m23 / matrix2.m23;
		result.m24 = matrix1.m24 / matrix2.m24;
		result.m31 = matrix1.m31 / matrix2.m31;
		result.m32 = matrix1.m32 / matrix2.m32;
		result.m33 = matrix1.m33 / matrix2.m33;
		result.m34 = matrix1.m34 / matrix2.m34;
		result.m41 = matrix1.m41 / matrix2.m41;
		result.m42 = matrix1.m42 / matrix2.m42;
		result.m43 = matrix1.m43 / matrix2.m43;
		result.m44 = matrix1.m44 / matrix2.m44;

		return result;
	}
}
