#pragma once

#include "CA_Export.hpp"
#include <iosfwd>

#include  "Camera3DComponent.hpp"
#include  "Maths/Vector3.hpp"

namespace CasaEngine
{
	class CA_EXPORT Camera3DLookAtComponent :
		public Camera3DComponent
	{
	public:
		Camera3DLookAtComponent(BaseEntity* entity);

		void Initialize() override;

		Vector3 Position() const;
		void Position(Vector3 val);

		Vector3 Target() const;
		void Target(Vector3 val);

		void Write(std::ostream& os)const;
		void Read(std::ifstream& is);

	protected:
		void ComputeViewMatrix() override;

	private:
		Vector3 m_Target, m_Position;
	};
}