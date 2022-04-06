#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include "CA_Export.h"
#include "Maths/Vector3.h"
#include "Maths/Matrix4.h"


namespace CasaEngine
{
	class CA_EXPORT Viewport
	{
	public:
		Viewport();
		Viewport(const Viewport& rsh_);
		Viewport(float x, float y, float width, float height);
		const Viewport& operator = (const Viewport& rsh_);

		float X() const;
		void X(float val);
		float Y() const;
		void Y(float val);
		float Width() const;
		void Width(float val);
		float Height() const;
		void Height(float val);
		float NearClipPlane() const;
		void NearClipPlane(float val);
		float FarClipPlane() const;
		void FarClipPlane(float val);

		Vector3F Project(const Vector3F& source, const Matrix4& projection, const Matrix4& view, const Matrix4& world) const;
		Vector3F Unproject(const Vector3F& source, const Matrix4& projection, const Matrix4& view, const Matrix4& world) const;

	private:
		void ComputeAspectRatio();

		float m_X{};
		float m_Y{};
		float m_Width{};
		float m_Height{};
		float m_fNearClipPlane{};
		float m_fFarClipPlane{};
	};
}

#endif
