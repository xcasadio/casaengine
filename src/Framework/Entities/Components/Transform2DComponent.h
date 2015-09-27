#ifndef TRANSFORM2DCOMPONENT_H_
#define TRANSFORM2DCOMPONENT_H_

#include <string>

#include "CA_Export.h"
#include "GameTime.h"
#include <iosfwd>
#include "Entities/Components/TransformComponent.h"
#include "Maths/Vector2.h"
#include "Maths/Matrix4.h"
#include "Entities/BaseEntity.h"
#include "Entities/Events/BaseEntityEvents.h"
#include "EventHandler/Event.h"

namespace CasaEngine
{
	/*
	 *	
	 */
	class CA_EXPORT Transform2DComponent :
		public TransformComponent
	{
	private:

		// The position in local space.
		Vector2F m_LocalPosition;
		
		// The rotation in local space and in degrees unit.
		float m_LocalRotation;
		
		// The scale in local space.
		Vector2F m_LocalScale;
		
		// The parent of this transform component.
		// In effect this field stores the game object parent.
		Transform2DComponent* m_pParentTransform;

		Event::Connection m_ParentChangedConnection;

	public:
		Transform2DComponent(BaseEntity* pEntity_);
		virtual ~Transform2DComponent();

		void SetLocalMatrix(Matrix4 val);
		void SetWorldMatrix(Matrix4 val);

		Vector2F GetLocalPosition() const;
		void SetLocalPosition(Vector2F val);

		float GetLocalRotation() const;
		void SetLocalRotation(float val);

		Vector2F GetLocalScale() const;
		void SetLocalScale(Vector2F val);

		Vector2F GetPosition() const;
		float GetRotation() const;
		Vector2F GetScale() const;

		void Initialize();

		//all entities must implement an update function
		void  Update(const GameTime& gameTime_);

		/**
		 * 
		 */
		bool OnParentChange(const EventArgs &e_);

		//entities should be able to read/write their data to a stream
		void Write(std::ostream&  os)const;
		void Read (std::ifstream& is);

	protected:
		void UpdateLocalMatrix();
		void UpdateWorldMatrix();
	};

}

#endif // TRANSFORM2DCOMPONENT_H_
