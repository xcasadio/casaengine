#ifndef CAMERA3DCOMPONENT_H_
#define CAMERA3DCOMPONENT_H_

#include "CA_Export.h"
#include <iosfwd>
#include "Entities/Components/CameraComponent.h"
#include "Maths/Vector3.h"

namespace CasaEngine
{
	class CA_EXPORT Camera3DComponent :
		public CameraComponent
	{
	public:
		Camera3DComponent(BaseEntity* pEntity_);

		void Initialize() override;

		Vector3F Position() const;
		void Position(Vector3F val);

		Vector3F Target() const;
		void Target(Vector3F val);

		float FOV() const;
		void FOV(float val);

		float FarClipPlane() const;
		void FarClipPlane(float val);

		float NearClipPlane() const;
		void NearClipPlane(float val);

		void Write(std::ostream&  os)const;
		void Read (std::ifstream& is);

	protected:
		void ComputeProjectionMatrix() override;
		void ComputeViewMatrix() override;

	private:
		Vector3F m_Target, m_Position;
		float m_fFOV;
	};
}

#endif
