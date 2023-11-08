#include  "Base.hpp"
#include  "Log/LogManager.hpp"
#include  "ComponentManager.hpp"
#include  "BaseEntity.hpp"
#include  "Component.hpp"
#include  "ContainerUtil.hpp"

#include  "CA_Assert.hpp"

namespace CasaEngine
{
	ComponentManager::ComponentManager(BaseEntity* entity)
	{
		CA_ASSERT(entity != nullptr, "ComponentManager::ComponentManager() : BaseEntity is nullptr")

			m_pEntity = entity;
	}

	ComponentManager::~ComponentManager()
	{
		DeleteSTLContainer(m_Components);
	}

	BaseEntity* ComponentManager::GetEntity() const
	{
		return m_pEntity;
	}

	void  ComponentManager::Update(const GameTime& gameTime_)
	{
		for (const auto& component : m_Components)
		{
			component->Update(gameTime_);
		}
	}

	void  ComponentManager::Draw()
	{
		for (const auto& component : m_Components)
		{
			component->Draw();
		}
	}

	// 	void ComponentManager::HandleEvent(const EventArgs* pEvent_)
	// 	{
	// 		for (size_t i=0; i<m_Components.size(); i++)
	// 		{
	// 			m_Components[i]->HandleEvent(pEvent_);
	// 		}
	// 	}

	void ComponentManager::Write(std::ostream& /*os*/) const
	{

	}

	void ComponentManager::Read(std::ifstream& /*is*/)
	{

	}

	void ComponentManager::AddComponent(Component* m_pComponent_)
	{
		CA_ASSERT(m_pComponent_ != nullptr, "ComponentManager::AddComponent() : Component is nullptr");

		m_Components.push_back(m_pComponent_);
	}

	void ComponentManager::RemoveComponent(Component* m_pComponent_)
	{
		CA_ASSERT(m_pComponent_ != nullptr, "ComponentManager::RemoveComponent() : Component is nullptr");

		for (auto it = m_Components.begin();
			it != m_Components.end();
			++it)
		{
			if (*it == m_pComponent_)
			{
				m_Components.erase(it);
				break;
			}
		}
	}

	void ComponentManager::InitializeComponents()
	{
		for (const auto& component : m_Components)
		{
			component->Initialize();
		}
	}

	bool ComponentManager::HandleMessage(const Telegram& msg)
	{
		bool res = false;

		for (const auto& m_Component : m_Components)
		{
			res |= m_Component->HandleMessage(msg);
		}

		return res;
	}

	const std::vector<Component*>& ComponentManager::Components() const
	{
		return m_Components;
	}

}
