#include  "Base.hpp"

#include  "Entities/BaseEntity.hpp"
#include  "Entities/ComponentTypeEnum.hpp"
#include  "Game/Game.hpp"
#include  "MovingEntity2DComponent.hpp"
#include  "SteeringBehaviorComponent.hpp"
#include  "StringUtils.hpp"

#include <string>

namespace CasaEngine
{

/**
 * 
 */
MovingEntity2DComponent::MovingEntity2DComponent(BaseEntity* entity, int smootherSampleSize_, Vector2 smootherZeroValue_)
	: Component(entity, MOVING_ENTITY_2D)
{
	m_pHeadingSmoother = new Smoother<Vector2>(smootherSampleSize_, smootherZeroValue_);
}

/**
 * 
 */
MovingEntity2DComponent::~MovingEntity2DComponent()
{
	delete m_pHeadingSmoother;
}

/**
 * 
 */
void MovingEntity2DComponent::Initialize()
{
	m_pSteering = GetEntity()->GetComponentMgr()->GetComponent<SteeringBehaviorComponent>();
	CA_ASSERT(m_pSteering != nullptr,
		"MovingEntity2DComponent::Initialize() can't find the SteeringBehaviorComponent. Please add it before add a MovingEntity2DComponent");
}

/**
 * 
 */
void MovingEntity2DComponent::Update(const GameTime& /*gameTime_*/)
{
	
}

/**
 * 
 */
/*void MovingEntity2DComponent::HandleEvent(const Event* pEvent_)
{

}*/

//behavior 
SteeringBehaviorComponent* const MovingEntity2DComponent::GetSteering() const
{
	return m_pSteering;
}

Vector2 MovingEntity2DComponent::SmoothedHeading()const
{
	return m_vSmoothedHeading;
}

bool MovingEntity2DComponent::IsSmoothingOn() const
{
	return m_bSmoothingOn;
}

void MovingEntity2DComponent::SmoothingOn()
{
	m_bSmoothingOn = true;
}

void MovingEntity2DComponent::SmoothingOff()
{
	m_bSmoothingOn = false;
}

void MovingEntity2DComponent::ToggleSmoothing()
{
	m_bSmoothingOn = !m_bSmoothingOn;
}

/**
 * 
 */
void MovingEntity2DComponent::Write(std::ostream& /*os*/) const
{

}

/**
 * 
 */
void MovingEntity2DComponent::Read (std::ifstream& /*is*/)
{

}

}
