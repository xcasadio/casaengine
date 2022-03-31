#ifndef BASEENTITY_H
#define BASEENTITY_H
//------------------------------------------------------------------------
//
//  Name:   BaseEntity.h
//
//  Desc:   Base class for a game object
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#include "CA_Export.h"

#include <iosfwd>

#include "AI/Messaging/Telegram.h"
#include "GameTime.h"
#include "ComponentManager.h"
#include "EventHandler/EventSet.h"
#include "Parsers/Xml/tinyxml2.h"

#include "Memory/MemoryAllocation.h"
#include "Physics/PhysicalEntity.h"


namespace CasaEngine
{
	typedef unsigned int EntityId;					// Unique identifier for each entity instance.
	#define INVALID_ENTITYID ((EntityId)(0))

	/**
	 *	
	 */
	class CA_EXPORT BaseEntity :
		public EventSet,
		public AllocatedObject<BaseEntity>
	{  
	public:
		/*
		 *	setting the ID and incrementing
		 *	the next valid ID
		 */
		BaseEntity();
		~BaseEntity();

		BaseEntity* GetParent() const;
		void SetParent(BaseEntity* val);

		ComponentManager* GetComponentMgr();
		PhysicalEntity &GetPhysicalEntity();

		/**
		 * 
		 */
		void Initialize();

		/**
		 * 
		 */
		void Update(const GameTime& gameTime_);

		/**
		 * 
		 */
		void Draw();

		//all entities can communicate using messages. They are sent
		//using the MessageDispatcher singleton class
		bool HandleMessage(const Telegram& msg);

		EntityId ID() const; 

		const char *GetName() const;
		void SetName(std::string &val);
		void SetName(const char *val);

		bool IsEnabled() const;
		void IsEnabled(bool val);
		bool IsVisible() const;
		void IsVisible(bool val);

		virtual void Read (const tinyxml2::XMLElement& xmlElt);
		virtual void Read (std::ifstream& is);
		virtual void Write(tinyxml2::XMLElement& xmlElt);
		virtual void Write(std::ostream&  os);

	private:

		//this is the next valid ID. Each time a BaseEntity is instantiated
		//this value is updated
		static EntityId m_iNextValidID;

		//every entity must have a unique identifying number
		EntityId m_ID;
		// if the object depend on an other object (transform)
		BaseEntity* m_pParent; 
		// manager of all components of this BaseEntity
		ComponentManager* m_pComponentManager;
		PhysicalEntity m_PhysicalEntity;

		std::string m_Name;
		bool m_bIsEnabled, m_bIsVisible;

//#ifdef EDITOR
	public:
		bool IsSelected() const;
		void IsSelected(bool val);

	public:
		bool m_IsSelected;
//#endif
	};

}

#endif
