#pragma once

#include <iosfwd>

#include "CA_Export.hpp"
#include  "ColliderComponent.hpp"


namespace CasaEngine
{
	class CA_EXPORT Box2DColliderComponent :
		public ColliderComponent
	{
	public:
		Box2DColliderComponent(BaseEntity* entity_);
		~Box2DColliderComponent() override = default;

		void Initialize() override;
		void Set(float left, float top, float width, float height);

		void Write(std::ostream& os)const override;
		void Read (std::ifstream& is) override;

	private:
		Rectangle _box;
	};

}
