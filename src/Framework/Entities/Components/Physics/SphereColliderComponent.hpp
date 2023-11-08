#pragma once

#include <iosfwd>

#include "CA_Export.hpp"
#include  "ColliderComponent.hpp"

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
