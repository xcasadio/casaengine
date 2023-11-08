#pragma once

#include <iosfwd>

#include "CA_Export.hpp"
#include  "ColliderComponent.hpp"
#include  "Maths/Shape/Box.hpp"


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
