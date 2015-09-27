#ifndef Transform3DComponent_H_
#define Transform3DComponent_H_

#include <string>

#include "CA_Export.h"
#include "GameTime.h"
#include <iosfwd>
#include "Entities/Components/TransformComponent.h"
#include "Maths/Vector2.h"
#include "Maths/Matrix4.h"
#include "Entities/BaseEntity.h"
#include "Entities/Events/BaseEntityEvents.h"
#include "Maths/Quaternion.h"

namespace CasaEngine
{
	/*
	 *	
	 */
	class CA_EXPORT Transform3DComponent :
		public TransformComponent
	{
	private:

		// The position in local space.
		Vector3F m_LocalPosition;
		
		// The rotation in local space and in degrees unit.
		Quaternion m_LocalRotation;
		
		// The scale in local space.
		Vector3F m_LocalScale;
		
		// The parent of this transform component.
		// In effect this field stores the game object parent.
		Transform3DComponent* m_pParentTransform;

		Event::Connection m_ParentChangedConnection;

	public:
		Transform3DComponent(BaseEntity* pEntity_);
		virtual ~Transform3DComponent();

		void SetLocalMatrix(Matrix4 val);
		void SetWorldMatrix(Matrix4 val);

		Vector3F GetLocalPosition() const;
		void SetLocalPosition(Vector3F val);

		Quaternion GetLocalRotation() const;
		void SetLocalRotation(Quaternion val);

		Vector3F GetLocalScale() const;
		void SetLocalScale(Vector3F val);

		Vector3F GetPosition() const;
		Quaternion GetRotation() const;
		Vector3F GetScale() const;

		/**
		 * 
		 */
		void Initialize();

		/**
		 * 
		 */
		void  Update(const GameTime& gameTime_);

		/**
		 * 
		 */
		bool OnParentChange(const EventArgs &e);

		/**
		 * Editor
		 */
		void ShowDebugWidget();

		/**
		 * 
		 */
		void Write(std::ostream&  os)const;
		void Read (std::ifstream& is);

	protected:
		void UpdateLocalMatrix();
		void UpdateWorldMatrix();
	};

}

#endif // Transform3DComponent_H_


