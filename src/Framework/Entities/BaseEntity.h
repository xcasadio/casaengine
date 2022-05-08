#pragma once

#include "CA_Export.h"
#include "Messaging/Telegram.h"
#include "GameTime.h"
#include "ComponentManager.h"
#include "EventHandler/EventSet.h"
#include "Physics/PhysicalEntity.h"

#include <iosfwd>

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
		PhysicalEntity &GetPhysicalEntity();
		
		void Initialize();
		void Update(const GameTime& gameTime_);
		void Draw();

		//all entities can communicate using messages. They are sent
		//using the MessageDispatcher singleton class
		bool HandleMessage(const Telegram& msg);

		unsigned int Id() const;

		const char *GetName() const;
		void SetName(std::string &val);
		void SetName(const char *val);

		bool IsEnabled() const;
		void IsEnabled(bool val);
		bool IsVisible() const;
		void IsVisible(bool val);
		
		virtual void Read (std::ifstream& is);
		virtual void Write(std::ostream&  os);

	private:

		//this is the next valid Id. Each time a BaseEntity is instantiated
		//this value is updated
		static unsigned int _nextValidId;

		//every entity must have a unique identifying number
		unsigned int _id;
		// if the object depend on an other object (transform)
		BaseEntity* _parent; 
		// manager of all components of this BaseEntity
		ComponentManager* _componentManager;
		PhysicalEntity _physicalEntity;

		std::string _name;
		bool _isEnabled;
		bool _isVisible;

#ifdef EDITOR
	public:
		bool IsSelected() const;
		void IsSelected(bool val);

	public:
		bool m_IsSelected;
#endif
	};

}
