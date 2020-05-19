
#include "Base.h"
#include "Log/LogManager.h"
#include "ComponentManager.h"
#include "BaseEntity.h"
#include "Component.h"
#include "ContainerUtil.h"



#include "CA_Assert.h"


namespace CasaEngine
{

	/**
	 * 
	 */
	ComponentManager::ComponentManager(BaseEntity* pEntity_)
	{
		CA_ASSERT(pEntity_ != nullptr, "ComponentManager::ComponentManager() : BaseEntity is nullptr");

		m_pEntity = pEntity_;
	}

	/**
	 * 
	 */
	ComponentManager::~ComponentManager()
	{
		DeleteSTLContainer(m_Components);
	}

	/**
	 * 
	 */
	BaseEntity* ComponentManager::GetEntity() const 
	{ 
		return m_pEntity; 
	}

	/**
	 * 
	 */
	void  ComponentManager::Update(const GameTime& gameTime_)
	{
		for (size_t i=0; i<m_Components.size(); i++)
		{
			m_Components[i]->Update(gameTime_);
		}
	}

	/**
	 * 
	 */
	void  ComponentManager::Draw()
	{
		for (size_t i=0; i<m_Components.size(); i++)
		{
			m_Components[i]->Draw();
		}
	}

	/**
	 * 
	 */
// 	void ComponentManager::HandleEvent(const EventArgs* pEvent_)
// 	{
// 		for (size_t i=0; i<m_Components.size(); i++)
// 		{
// 			m_Components[i]->HandleEvent(pEvent_);
// 		}
// 	}

	/**
	 * 
	 */
	void ComponentManager::Write(std::ostream& /*os*/) const
	{

	}

	/**
	 * 
	 */
	void ComponentManager::Read (std::ifstream& /*is*/)
	{

	}

	/**
	 * 
	 */
	void ComponentManager::AddComponent( Component* m_pComponent_ )
	{
		CA_ASSERT(m_pComponent_ != nullptr, "ComponentManager::AddComponent() : Component is nullptr");

		m_Components.push_back(m_pComponent_);
	}

	/**
	 * 
	 */
	void ComponentManager::RemoveComponent( Component* m_pComponent_ )
	{
		CA_ASSERT(m_pComponent_ != nullptr, "ComponentManager::RemoveComponent() : Component is nullptr");

		for (std::vector<Component *>::iterator it = m_Components.begin();
			it != m_Components.end();
			it++)
		{
			if ((*it) == m_pComponent_)
			{
				m_Components.erase(it);
				break;
			}
		}
	}

	/**
	 * 
	 */
	void ComponentManager::InitializeComponents()
	{
		for (size_t i=0; i<m_Components.size(); i++)
		{
			m_Components[i]->Initialize();
		}
	}

	/**
	 * 
	 */
	bool ComponentManager::HandleMessage( const Telegram& msg )
	{
		bool res = false;

		for (size_t i=0; i<m_Components.size(); i++)
		{
			res |= m_Components[i]->HandleMessage(msg);
		}

		return res;
	}

	/**
	 * 
	 */
	const std::vector<Component *> &ComponentManager::Components() const
	{
		return m_Components;
	}

}
