
#include "Base.h"

#include "Viewport.h"
#include "Maths\Matrix4.h"
#include "Maths\Vector3.h"




namespace CasaEngine
{
	/**
	 * 
	 */
	Viewport::Viewport()
	{
		m_X = 0;
		m_Y = 0;
		m_Width = 1;
		m_Height = 1;
		m_fNearClipPlane = 0.0f;
		m_fFarClipPlane = 1.0f;

		ComputeAspectRatio();
	}

	/**
	 * 
	 */
	Viewport::Viewport(const Viewport& rsh_)
	{
		*this = rsh_;
	}

	/**
	 * 
	 */
	Viewport::Viewport(float x, float y, float width, float height)
	{
		m_X = x;
		m_Y = y;
		m_Width = width;
		m_Height = height;
		m_fNearClipPlane = 0.0f;
		m_fFarClipPlane = 1.0f;

		ComputeAspectRatio();
	}

	/**
	 * 
	 */
	const Viewport& Viewport::operator = (const Viewport& rsh_)
	{
		m_X = rsh_.m_X;
		m_Y = rsh_.m_Y;
		m_Width = rsh_.m_Width;
		m_Height = rsh_.m_Height;
		m_fNearClipPlane = rsh_.m_fNearClipPlane;
		m_fFarClipPlane = rsh_.m_fFarClipPlane;
		m_fAspectRatio = rsh_.m_fAspectRatio;

		ComputeAspectRatio();

		return *this;
	}

	/**
	 * 
	 */
	Viewport::~Viewport()
	{
	}

	/**
	 * 
	 */
	float Viewport::X() const { return m_X; }

	/**
	 * 
	 */
	void Viewport::X(float val) { m_X = val; }

	/**
	 * 
	 */
	float Viewport::Y() const { return m_Y; }

	/**
	 * 
	 */
	void Viewport::Y(float val) { m_Y = val; }

	/**
	 * 
	 */
	float Viewport::Width() const 
	{ 
		return m_Width; 
	}

	/**
	 * 
	 */
	void Viewport::Width(float val)
	{ 
		m_Width = val; 
		ComputeAspectRatio();
	}

	/**
	 * 
	 */
	float Viewport::Height() const 
	{ 
		return m_Height;
	}

	/**
	 * 
	 */
	void Viewport::Height(float val)
	{ 
		m_Height = val; 
		ComputeAspectRatio();
	}

	/**
	 * 
	 */
	float Viewport::NearClipPlane() const 
	{ 
		return m_fNearClipPlane; 
	}

	/**
	 * 
	 */
	void Viewport::NearClipPlane(float val) 
	{ 
		m_fNearClipPlane = val; 
	}

	/**
	 * 
	 */
	float Viewport::FarClipPlane() const 
	{ 
		return m_fFarClipPlane; 
	}

	/**
	 * 
	 */
	void Viewport::FarClipPlane(float val) 
	{ 
		m_fFarClipPlane = val; 
	}

	/**
	 * 
	 */
	float Viewport::AspectRatio() const 
	{ 
		return m_fAspectRatio; 
	}

	/**
	 * 
	 */
	void Viewport::ComputeAspectRatio() 
	{ 
		if (m_Height != 0)
		{
			m_fAspectRatio = static_cast<float>(m_Width) / static_cast<float>(m_Height);
		}
		else
		{
			m_fAspectRatio = 0.0f; 
		}		
	}

	/**
	 * 
	 */
	bool WithinEpsilon(float a, float b)
	{
		float num = a - b;
		return -1.401298E-45f <= num && num <= 1.401298E-45f;
	}

	/**
	 * 
	 */
	Vector3F Viewport::Project(const Vector3F &source, const Matrix4 &projection, const Matrix4 &view, const Matrix4 &world) const
	{
		Matrix4 mat = world * view * projection; // Matrix4::Multiply(Matrix4.Multiply(world, view), projection);		
		Vector3F vector;
		mat.Transform(source, vector); // Vector3F::Transform(source, mat);
		float a = source.x * mat.a14 + source.y * mat.a24 + source.z * mat.a34 + mat.a44;
		if (!WithinEpsilon(a, 1.0f))
		{
			vector = static_cast<Vector3F>(vector / a);
		}
		vector.x = (vector.x + 1.0f) * 0.5f * m_Width + m_X;
		vector.y = (-vector.y + 1.0f) * 0.5f * m_Height + m_Y;
		vector.z = vector.z * (m_fFarClipPlane - m_fNearClipPlane) + m_fNearClipPlane;
		return vector;
	}

	/**
	 * 
	 */
	Vector3F Viewport::Unproject(const Vector3F &source, const Matrix4 &projection, const Matrix4 &view, const Matrix4 &world) const
	{
		Vector3F vector = source;
		Matrix4 mat = (world * view * projection).Invert(); //Matrix4.Invert(Matrix4.Multiply(Matrix4.Multiply(world, view), projection));
		vector.x = (source.x - m_X) / m_Width * 2.0f - 1.0f;
		vector.y = -((source.y - m_Y) / m_Height * 2.0f - 1.0f);
		vector.z = (source.z - m_fNearClipPlane) / (m_fFarClipPlane - m_fNearClipPlane);

		mat.Transform(source, vector); // Vector3F.Transform(source, mat);
		const float a = source.x * mat.a14 + source.y * mat.a24 + source.z * mat.a34 + mat.a44;
		if (!WithinEpsilon(a, 1.0f))
		{
			vector = vector / a;
		}
		return vector;
	}

	
}
