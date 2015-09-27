
#include "AI/FSM/StateMachine.h"
#include "Entities/BaseEntity.h"
#include "Entities/ComponentTypeEnum.h"
#include "Base.h"
#include "Game/Game.h"
#include "FSMComponent.h"
#include "Maths/Matrix4.h"


#include <string>
#include "Memory/MemoryAllocation.h"



namespace CasaEngine
{

/**
 * 
 */
FSMComponent::FSMComponent(BaseEntity* pEntity_)
	: Component(pEntity_, FSM)
{
	m_pStateMachine = ::new StateMachine<BaseEntity>(pEntity_);
}

/**
 * 
 */
FSMComponent::~FSMComponent()
{

}

/**
 * 
 */
StateMachine<BaseEntity>* FSMComponent::GetFSM() const
{
	return m_pStateMachine;
}

/**
 * 
 */
void FSMComponent::Initialize()
{
	
}

/**
 * 
 */
void FSMComponent::Update(const GameTime& /*gameTime_*/)
{
	/*Matrix4 mat = m_pTransform->GetWorldMatrix();
	Vector3F pos3 = mat.GetTranslation();
	Vector2F pos(pos3.x, pos3.y);*/
}

/**
 * 
 */
/*void FSMComponent::HandleEvent(const Event* pEvent_)
{

}*/

/**
 * 
 */
void FSMComponent::Write(std::ostream& /*os*/) const
{

}

/**
 * 
 */
void FSMComponent::Read (std::ifstream& /*is*/)
{

}



} // namespace CasaEngine
