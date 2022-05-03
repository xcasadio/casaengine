#pragma once

#include "CA_Export.h"

namespace CasaEngine
{
	enum class AxisConstraints
	{
		NONE,
		XY,
		XZ,
		YZ
	};

	struct CA_EXPORT RigidBodyParameters
	{
		float			mass;

		IShape*			collisionShape;
		Vector3			localInertia;
		float			linearDamping;
		float			angularDamping;
		AxisConstraints axisConstraint;

		///best simulation results when friction is non-zero
		float			friction;
		///the rollingFriction prevents rounded shapes, such as spheres, cylinders and capsules from rolling forever.
		///See Bullet/Demos/RollingFrictionDemo for usage
		float			rollingFriction;
		float			restitution;
		float			linearSleepingThreshold;
		float			angularSleepingThreshold;

		//Additional damping can help avoiding lowpass jitter motion, help stability for ragdolls etc.
		//Such damping is undesirable, so once the overall simulation quality of the rigid body dynamics system has improved, this should become obsolete
		bool			additionalDamping;
		float			additionalDampingFactor;
		float			additionalLinearDampingThresholdSqr;
		float			additionalAngularDampingThresholdSqr;
		float			additionalAngularDampingFactor;

		RigidBodyParameters() :
			mass(1.0f),
			collisionShape(nullptr),
			localInertia(Vector3::Zero()),
			linearDamping(0.f),
			angularDamping(0.f),
			axisConstraint(AxisConstraints::NONE),
			friction(0.5f),
			rollingFriction(0.0f),
			restitution(0.f),
			linearSleepingThreshold(0.8f),
			angularSleepingThreshold(1.f),
			additionalDamping(false),
			additionalDampingFactor(0.005f),
			additionalLinearDampingThresholdSqr(0.01f),
			additionalAngularDampingThresholdSqr(0.01f),
			additionalAngularDampingFactor(0.01f)
		{
		}
	};
}
