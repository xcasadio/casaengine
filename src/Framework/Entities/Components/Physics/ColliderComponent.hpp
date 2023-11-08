#pragma once

#include <iosfwd>

#include "CA_Export.hpp"

#include  "GameTime.hpp"
#include  "Entities/Component.hpp"
#include  "Physics/RigidBodyParameters.hpp"

namespace CasaEngine
{

	class CA_EXPORT ColliderComponent :
		public Component
	{
	public:
		~ColliderComponent() override;

		void Initialize() override;
		void Update(const GameTime& gameTime_) override;

		IShape* GetShape() const;

		float Mass() const;
		void Mass(float val);

		AxisConstraints AxisConstraint() const;
		void AxisConstraint(AxisConstraints val);

		virtual void Write(std::ostream& os)const;
		virtual void Read(std::ifstream& is);

	protected:
		IShape* _shape;

		ColliderComponent(BaseEntity* entity_, int type_);
		void CreateAndSetRigidBody(float mass);

	private:
		AxisConstraints _axisConstraint;
		float _mass;
	};
}
