#pragma once

#include "CA_Export.h"
#include <iosfwd>

#include "Camera3DComponent.h"
#include "Maths/Vector3.h"

namespace CasaEngine
{
	class CA_EXPORT Camera3DLookAtComponent :
		public Camera3DComponent
	{
	public:
		Camera3DLookAtComponent(BaseEntity* pEntity_);

		void Initialize() override;

		Vector3F Position() const;
		void Position(Vector3F val);

		Vector3F Target() const;
		void Target(Vector3F val);

		void Write(std::ostream& os)const;
		void Read(std::ifstream& is);

	protected:
		void ComputeViewMatrix() override;

	private:
		Vector3F m_Target, m_Position;
	};
}
