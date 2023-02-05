#pragma once

#include <iosfwd>

#include "CA_Export.h"
#include "ColliderComponent.h"
#include "Maths/Shape/Box.h"


namespace CasaEngine
{
	class CA_EXPORT BoxColliderComponent :
		public ColliderComponent
	{
	private:
		Box m_Shape;

	public:
		BoxColliderComponent(BaseEntity* entity);
		~BoxColliderComponent() override;

		void Initialize() override;
		void Draw() override;
		Box Shape() const;

		void Write(std::ostream&  os)const override;
		void Read (std::ifstream& is) override;
	};

}
