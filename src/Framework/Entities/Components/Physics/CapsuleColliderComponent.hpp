#pragma once*
#include <iosfwd>

#include "CA_Export.hpp"
#include  "ColliderComponent.hpp"

namespace CasaEngine
{
	class CA_EXPORT CapsuleColliderComponent :
		public ColliderComponent
	{
	public:
		CapsuleColliderComponent(BaseEntity* entity);
		~CapsuleColliderComponent() override;

		void Initialize() override;

		void Write(std::ostream&  os)const override;
		void Read (std::ifstream& is) override;
	};

}
