#pragma once*
#include <iosfwd>

#include "CA_Export.h"
#include "ColliderComponent.h"

namespace CasaEngine
{
	class CA_EXPORT CapsuleColliderComponent :
		public ColliderComponent
	{
	public:
		CapsuleColliderComponent(BaseEntity* pEntity_);
		~CapsuleColliderComponent() override;

		void Initialize() override;

		void Write(std::ostream&  os)const override;
		void Read (std::ifstream& is) override;
	};

}
