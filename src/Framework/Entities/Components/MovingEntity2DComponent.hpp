#pragma once

#include "CA_Export.hpp"
#include  "GameTime.hpp"
#include <iosfwd>
#include  "Entities/Component.hpp"
#include  "Maths/Vector2.hpp"
#include  "Maths/Utils/Smoother.hpp"

namespace CasaEngine
{
	class SteeringBehaviorComponent;

	/**
	 *
	 */
	class CA_EXPORT MovingEntity2DComponent :
		public Component
	{
	private:
		SteeringBehaviorComponent* m_pSteering;
		//some steering behaviors give jerky looking movement. The
		//following members are used to smooth the vehicle's heading
		Smoother<Vector2>* m_pHeadingSmoother;

		//this vector represents the average of the vehicle's heading
		//vector smoothed over the last few frames
		Vector2             m_vSmoothedHeading;

		//when true, smoothing is active
		bool                 m_bSmoothingOn;

	public:
		explicit MovingEntity2DComponent(BaseEntity* entity, int smootherSampleSize_ = 10.0f, Vector2 smootherZeroValue_ = Vector2::Zero());
		~MovingEntity2DComponent() override;

		//all entities must implement an Initialize function
		void Initialize() override;

		//all entities must implement an update function
		void  Update(const GameTime& gameTime_) override;

		//all entities can communicate using messages. They are sent
		//using the MessageDispatcher singleton class
		//void HandleEvent(const Event* pEvent_);

		SteeringBehaviorComponent* const GetSteering() const;

		Vector2 SmoothedHeading() const;

		bool IsSmoothingOn() const;
		void SmoothingOn();
		void SmoothingOff();
		void ToggleSmoothing();

		//entities should be able to read/write their data to a stream
		void Write(std::ostream& os)const;
		void Read(std::ifstream& is);

	};// class MovingEntity2DComponent
}
