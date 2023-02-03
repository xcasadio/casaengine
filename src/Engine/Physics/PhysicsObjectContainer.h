#pragma once

#include "CA_Export.h"
#include "Maths/Vector3.h"
#include "Log/LogManager.h"
#include "Maths/Quaternion.h"

namespace CasaEngine
{
	class CA_EXPORT IRigidBodyContainer
	{
	public:
		virtual ~IRigidBodyContainer();

#if defined(CA_DEBUG)
		virtual void logInfo() = 0;
#endif // #if defined(CA_DEBUG)

		virtual Vector3 GetLinearVelocity() const = 0;
		virtual void setLinearVelocity(const Vector3& lin_vel) = 0;

		virtual Vector3 getAngularVelocity() const = 0;
		virtual void setAngularVelocity(const Vector3& ang_vel) = 0;

		virtual Vector3 getTranslation() const = 0;
		virtual void setTranslation(const Vector3& ang_vel) = 0;

		virtual Quaternion getRotation() const = 0;
		virtual void setRotation(const Quaternion& rot) = 0;
	};


	class CA_EXPORT ICollisionObjectContainer
	{
	public:
		virtual ~ICollisionObjectContainer();
	};
}
