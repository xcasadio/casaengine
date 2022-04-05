#ifndef Transform3DComponent_H_
#define Transform3DComponent_H_

#include "CA_Export.h"
#include "GameTime.h"
#include <iosfwd>
#include "Entities/Components/TransformComponent.h"
#include "Maths/Matrix4.h"
#include "Entities/BaseEntity.h"
#include "Maths/Quaternion.h"

namespace CasaEngine
{
	class CA_EXPORT Transform3DComponent :
		public TransformComponent
	{
	private:
		Vector3F m_LocalCenterOfRotation;
		Vector3F m_LocalPosition;
		Quaternion m_LocalRotation;
		Vector3F m_LocalScale;
		
		// The parent of this transform component.
		// In effect this field stores the game object parent.
		Transform3DComponent* m_pParentTransform;

		Event::Connection m_ParentChangedConnection;

	public:
		Transform3DComponent(BaseEntity* pEntity_);
		~Transform3DComponent() override;

		void SetLocalMatrix(Matrix4 val) override;
		void SetWorldMatrix(Matrix4 val) override;

		Vector3F GetCenterOfRotation() const;
		void SetCenterOfRotation(Vector3F val);
		
		Vector3F GetLocalPosition() const;
		void SetLocalPosition(Vector3F val);

		Quaternion GetLocalRotation() const;
		void SetLocalRotation(Quaternion val);

		Vector3F GetLocalScale() const;
		void SetLocalScale(Vector3F val);

		Vector3F GetPosition() const;
		Quaternion GetRotation() const;
		Vector3F GetScale() const;

		void Initialize() override;
		void  Update(const GameTime& gameTime_) override;

		bool OnParentChange(const EventArgs &e);

		void ShowDebugWidget() override;

		void Write(std::ostream&  os)const override;
		void Read (std::ifstream& is) override;

	protected:
		void UpdateLocalMatrix() override;
		void UpdateWorldMatrix() override;
	};

}

#endif
