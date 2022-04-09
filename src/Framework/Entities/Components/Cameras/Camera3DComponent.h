#pragma once

#include "CA_Export.h"
#include <iosfwd>
#include "Entities/Components/CameraComponent.h"

namespace CasaEngine
{
	class CA_EXPORT Camera3DComponent :
		public CameraComponent
	{
	public:
		Camera3DComponent(BaseEntity* pEntity_, int type);

		void Initialize() override;

		float FOV() const;
		void FOV(float val);

		void Write(std::ostream&  os)const;
		void Read (std::ifstream& is);

	protected:
		void ComputeProjectionMatrix() override;

	private:
		float m_fFOV;
	};
}
