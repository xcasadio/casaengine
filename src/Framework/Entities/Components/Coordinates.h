#pragma once

#include "CA_Export.h"
#include "Maths/Matrix4.h"
#include "Maths/Quaternion.h"
#include "Maths/Vector3.h"
#include "EventHandler/Event.h"

#include <iosfwd>

namespace CasaEngine
{
	class BaseEntity;

	class CA_EXPORT Coordinates
	{
	public:
		Coordinates();

		Matrix4 GetLocalMatrix();
		void SetLocalMatrix(const Matrix4& val);

		Matrix4 GetWorldMatrix();
		void SetWorldMatrix(const Matrix4& val);

		Vector3 GetCenterOfRotation() const;
		void SetCenterOfRotation(const Vector3& val);

		Vector3 GetLocalPosition() const;
		void SetLocalPosition(const Vector3& val);

		Quaternion GetLocalRotation() const;
		void SetLocalRotation(const Quaternion& val);

		Vector3 GetLocalScale() const;
		void SetLocalScale(const Vector3& val);

		Vector3 GetPosition() const;
		Quaternion GetRotation() const;
		Vector3 GetScale() const;

		void SetParent(Coordinates *parent);

		void Write(std::ostream&  os)const;
		void Read (std::ifstream& is);

	private :
		void UpdateLocalMatrix();
		void UpdateWorldMatrix();

		Coordinates* _parent;

		Matrix4 m_LocalMatrix;
		Matrix4 m_WorldMatrix;

		Vector3 m_LocalCenterOfRotation;
		Vector3 m_LocalPosition;
		Quaternion m_LocalRotation;
		Vector3 m_LocalScale;

		Event::Connection m_ParentChangedConnection;

		bool m_LocalMatrixChanged;

#if EDITOR
	public:
		void ShowDebugWidget();
#endif
	};
}
