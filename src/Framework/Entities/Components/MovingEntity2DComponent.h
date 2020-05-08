#ifndef MOVING_ENTITY_2D_COMPONENT_H_
#define MOVING_ENTITY_2D_COMPONENT_H_

#include <string>

#include "CA_Export.h"
#include "GameTime.h"
#include <iosfwd>
#include "Entities/Component.h"
#include <string>
#include "Sprite/SpriteRenderer.h"
#include "Graphics/Color.h"
#include "Sprite/SpriteTypes.h"
#include "Transform2DComponent.h"
#include "Maths/Vector2.h"
#include "Maths/Utils/Smoother.h"

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
		Smoother<Vector2F>*  m_pHeadingSmoother;

		//this vector represents the average of the vehicle's heading
		//vector smoothed over the last few frames
		Vector2F             m_vSmoothedHeading;

		//when true, smoothing is active
		bool                 m_bSmoothingOn;

	public:
		explicit MovingEntity2DComponent(BaseEntity* pEntity_, int smootherSampleSize_ = 10.0f, Vector2F smootherZeroValue_ = Vector2F::Zero());
		virtual ~MovingEntity2DComponent();

		//all entities must implement an Initialize function
		void Initialize();

		//all entities must implement an update function
		void  Update(const GameTime& gameTime_);

		//all entities can communicate using messages. They are sent
		//using the MessageDispatcher singleton class
		//void HandleEvent(const Event* pEvent_);

		SteeringBehaviorComponent* const GetSteering() const;

		Vector2F SmoothedHeading() const;

		bool IsSmoothingOn() const;
		void SmoothingOn();
		void SmoothingOff();
		void ToggleSmoothing();

		//entities should be able to read/write their data to a stream
		void Write(std::ostream&  os)const;
		void Read (std::ifstream& is);

	};// class MovingEntity2DComponent
}

#endif // MOVING_ENTITY_2D_COMPONENT_H_
