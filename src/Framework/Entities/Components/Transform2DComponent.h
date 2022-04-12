#ifndef TRANSFORM2DCOMPONENT_H_
#define TRANSFORM2DCOMPONENT_H_

#include "CA_Export.h"
#include "GameTime.h"
#include <iosfwd>
#include "Entities/Components/TransformComponent.h"
#include "Maths/Vector2.h"
#include "Maths/Matrix4.h"
#include "Entities/Events/BaseEntityEvents.h"
#include "EventHandler/Event.h"

namespace CasaEngine
{
	class CA_EXPORT Transform2DComponent :
		public TransformComponent
	{
	private:
		Vector2 m_LocalPosition;
		
		// The rotation in local space and in degrees unit.
		float m_LocalRotation;
		Vector2 m_LocalScale;
		
		// The parent of this transform component.
		// In effect this field stores the game object parent.
		Transform2DComponent* m_pParentTransform;

		Event::Connection m_ParentChangedConnection;

	public:
		Transform2DComponent(BaseEntity* pEntity_);
		~Transform2DComponent() override;

		void SetLocalMatrix(Matrix4 val) override;
		void SetWorldMatrix(Matrix4 val) override;

		Vector2 GetLocalPosition() const;
		void SetLocalPosition(Vector2 val);

		float GetLocalRotation() const;
		void SetLocalRotation(float val);

		Vector2 GetLocalScale() const;
		void SetLocalScale(Vector2 val);

		Vector2 GetPosition() const;
		float GetRotation() const;
		Vector2 GetScale() const;

		void Initialize() override;

		//all entities must implement an update function
		void  Update(const GameTime& gameTime_) override;

		bool OnParentChange(const EventArgs &e_);

		//entities should be able to read/write their data to a stream
		void Write(std::ostream&  os)const override;
		void Read (std::ifstream& is) override;

	protected:
		void UpdateLocalMatrix() override;
		void UpdateWorldMatrix() override;
	};

}

#endif
