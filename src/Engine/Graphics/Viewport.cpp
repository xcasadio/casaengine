#include "Viewport.h"
#include "Maths\Matrix4.h"
#include "Maths\Vector3.h"

namespace CasaEngine
{
	Viewport::Viewport(): Viewport(0, 0, 1, 1)
	{
	}

	Viewport::Viewport(const Viewport& rsh_)
	{
		*this = rsh_;
	}

	Viewport::Viewport(float x, float y, float width, float height) :
		m_X(x), m_Y(y), m_Width(width), m_Height(height), m_fNearClipPlane(0.1f), m_fFarClipPlane(10000.0f)
	{
	}

	const Viewport& Viewport::operator = (const Viewport& rsh_)
	{
		m_X = rsh_.m_X;
		m_Y = rsh_.m_Y;
		m_Width = rsh_.m_Width;
		m_Height = rsh_.m_Height;
		m_fNearClipPlane = rsh_.m_fNearClipPlane;
		m_fFarClipPlane = rsh_.m_fFarClipPlane;

		return *this;
	}

	float Viewport::X() const { return m_X; }

	void Viewport::X(float val) { m_X = val; }

	float Viewport::Y() const { return m_Y; }

	void Viewport::Y(float val) { m_Y = val; }

	float Viewport::Width() const
	{
		return m_Width;
	}

	void Viewport::Width(float val)
	{
		m_Width = val;
	}

	float Viewport::Height() const
	{
		return m_Height;
	}

	void Viewport::Height(float val)
	{
		m_Height = val;
	}

	float Viewport::NearClipPlane() const
	{
		return m_fNearClipPlane;
	}

	void Viewport::NearClipPlane(float val)
	{
		m_fNearClipPlane = val;
	}

	float Viewport::FarClipPlane() const
	{
		return m_fFarClipPlane;
	}

	void Viewport::FarClipPlane(float val)
	{
		m_fFarClipPlane = val;
	}
	
	bool WithinEpsilon(float a, float b)
	{
		float num = a - b;
		return -1.401298E-45f <= num && num <= 1.401298E-45f;
	}

	Vector3 Viewport::Project(const Vector3& source, const Matrix4& projection, const Matrix4& view, const Matrix4& world) const
	{
		Matrix4 mat = Matrix4::Multiply(Matrix4::Multiply(world, view), projection);
		Vector3 vector = mat.Transform(source); // Vector3::Transform(source, mat);
		float a = source.x * mat.m14 + source.y * mat.m24 + source.z * mat.m34 + mat.m44;
		if (!WithinEpsilon(a, 1.0f))
		{
			vector = vector / a;
		}
		vector.x = (vector.x + 1.0f) * 0.5f * m_Width + m_X;
		vector.y = (-vector.y + 1.0f) * 0.5f * m_Height + m_Y;
		vector.z = vector.z * (m_fFarClipPlane - m_fNearClipPlane) + m_fNearClipPlane;
		return vector;
	}

	Vector3 Viewport::Unproject(const Vector3& source, const Matrix4& projection, const Matrix4& view, const Matrix4& world) const
	{
		Vector3 vector = source;
		Matrix4 mat = Matrix4::Invert(Matrix4::Multiply(Matrix4::Multiply(world, view), projection));
		vector.x = (source.x - m_X) / m_Width * 2.0f - 1.0f;
		vector.y = -((source.y - m_Y) / m_Height * 2.0f - 1.0f);
		vector.z = (source.z - m_fNearClipPlane) / (m_fFarClipPlane - m_fNearClipPlane);

		vector = mat.Transform(source); // Vector3.Transform(source, mat);
		const float a = source.x * mat.m14 + source.y * mat.m24 + source.z * mat.m34 + mat.m44;
		if (!WithinEpsilon(a, 1.0f))
		{
			vector = vector / a;
		}
		return vector;
	}
}