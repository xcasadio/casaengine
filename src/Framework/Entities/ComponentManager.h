#pragma once

#include <iosfwd>
#include <vector>

#include "CA_Export.h"

#include "Messaging/Telegram.h"
#include "GameTime.h"
#include "Entities/Component.h"


namespace CasaEngine
{
	class BaseEntity;

	class CA_EXPORT ComponentManager
	{
	private:
		BaseEntity* m_pEntity;
		std::vector<Component*> m_Components;
	public:
		ComponentManager(BaseEntity* entity);
		~ComponentManager();

		void InitializeComponents();
		void Update(const GameTime& gameTime_);
		void Draw();
		bool HandleMessage(const Telegram& msg);

		void AddComponent(Component* m_pComponent_);
		void RemoveComponent(Component* m_pComponent_);
		const std::vector<Component*>& Components() const;
		template <class T> T* GetComponent() const;
		template <class T> std::vector<T*> GetComponents() const;

		BaseEntity* GetEntity() const;

		virtual void Write(std::ostream& os)const;
		virtual void Read(std::ifstream& is);
	};

	template <class T>
	std::vector<T*>
		CasaEngine::ComponentManager::GetComponents() const
	{
		std::vector<T*> res;

		for (size_t i = 0; i < m_Components.size(); i++)
		{
			T* c = dynamic_cast<T*>(m_Components[i]);

			if (c != nullptr)
			{
				res.push_back(c);
			}
		}

		return res;
	}

	template <class T>
	T* CasaEngine::ComponentManager::GetComponent() const
	{
		for (size_t i = 0; i < m_Components.size(); i++)
		{
			T* res = dynamic_cast<T*>(m_Components[i]);

			if (res != nullptr)
			{
				return res;
			}
		}

		return nullptr;
	}

}
