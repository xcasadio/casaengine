#pragma once

#include <iosfwd>

#include "CA_Export.h"
#include "ColliderComponent.h"

namespace CasaEngine
{
	class CA_EXPORT SphereColliderComponent :
		public ColliderComponent
	{
	private:

	public:
		SphereColliderComponent(BaseEntity* entity);
		~SphereColliderComponent() override;

		void Initialize() override;

		void Write(std::ostream&  os)const override;
		void Read (std::ifstream& is) override;
	};

}
