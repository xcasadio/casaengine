#pragma once

#include "CA_Export.h"
#include "Messaging/Telegram.h"
#include "GameTime.h"
#include "ComponentManager.h"
#include "EventHandler/EventSet.h"
#include "Physics/PhysicalEntity.h"
#include "Components/Coordinates.h"

namespace CasaEngine
{
	class CA_EXPORT BaseEntity :
		public EventSet
	{
	public:
		BaseEntity();
		~BaseEntity() override;

		BaseEntity* GetParent() const;
		void SetParent(BaseEntity* val);

		ComponentManager* GetComponentMgr();
		PhysicalEntity& GetPhysicalEntity();

		void Initialize();
		void Update(const GameTime& gameTime_);
		void Draw();

		bool HandleMessage(const Telegram& msg); //all entities can communicate using messages. They are sent using the MessageDispatcher singleton class

		unsigned int Id() const;
		const char* GetName() const;
		void SetName(const std::string& val);
		void SetName(const char* val);

		Coordinates& GetCoordinates();

		bool ToBeRemoved() const;
		void ToBeRemoved(bool val);

		bool IsEnabled() const;
		void IsEnabled(bool val);
		bool IsVisible() const;
		void IsVisible(bool val);

	private:
		static unsigned int _nextValidId;

		unsigned int _id;
		BaseEntity* _parent;
		ComponentManager* _componentManager;
		Coordinates _coordinates;
		PhysicalEntity _physicalEntity; // TODO : remove this

		std::string _name;
		bool _isEnabled;
		bool _isVisible;
		bool _toRemoved;

#ifdef EDITOR
	public:
		bool IsSelected() const;
		void IsSelected(bool val);

		bool IsPersistent() const;
		void IsPersistent(bool val);

	public:
		bool _isSelected;
		bool _isPersistent;
#endif
	};
}
