#ifndef BOX2DCOLLIDERCOMPONENT_H_
#define BOX2DCOLLIDERCOMPONENT_H_

#include <iosfwd>

#include "CA_Export.h"
#include "ColliderComponent.h"


namespace CasaEngine
{
	class CA_EXPORT Box2DColliderComponent :
		public ColliderComponent
	{
	public:
		Box2DColliderComponent(BaseEntity* pEntity_);
		~Box2DColliderComponent() override = default;

		void Initialize() override;
		void Set(float left, float top, float width, float height);

		void Write(std::ostream&  os)const override;
		void Read (std::ifstream& is) override;

	private:
		RectangleF m_Box;
	};

}

#endif // BOX2DCOLLIDERCOMPONENT_H_
