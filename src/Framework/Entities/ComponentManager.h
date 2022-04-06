#ifndef COMPONENTMANAGER_H_
#define COMPONENTMANAGER_H_

#include <iosfwd>
#include <vector>

#include "CA_Export.h"

#include "AI/Messaging/Telegram.h"
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
		ComponentManager(BaseEntity* pEntity_);
		~ComponentManager();

		const std::vector<Component*>& Components() const;

		template <class T>
		T* GetComponent() const
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

		template <class T>
		std::vector<T*> GetComponents() const
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

		//all entities must implement an update function
		void Update(const GameTime& gameTime_);
		void Draw();

		void AddComponent(Component* m_pComponent_);
		void RemoveComponent(Component* m_pComponent_);

		BaseEntity* GetEntity() const;
		//entities should be able to read/write their data to a stream
		virtual void Write(std::ostream& os)const;
		virtual void Read(std::ifstream& is);

		void InitializeComponents();
		bool HandleMessage(const Telegram& msg);
	};
}

#endif
