#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "CA_Export.h"

#include <string>
#include <iosfwd>

#include "AI/Messaging/Telegram.h"
#include "GameTime.h"
#include "Parsers/Xml/tinyxml2.h"

#include "Memory/MemoryAllocation.h"


namespace CasaEngine
{
	class BaseEntity;

	/*
	 *	
	 */
	class CA_EXPORT Component :
		public AllocatedObject<Component>
	{
	private:
		BaseEntity* m_pEntity;
		int m_Type;

	protected:
		Component(BaseEntity* pEntity_, int type_);

	public:
		virtual ~Component();

		/**
		 * 
		 */
		int Type() const;

		/**
		 * 
		 */
		virtual bool HandleMessage(const Telegram& msg );

		/**
		 * 
		 */
		virtual void Initialize() = 0;

		/**
		 * 
		 */
		virtual void Update(const GameTime& gameTime_) = 0;

		/**
		 * 
		 */
		virtual void Draw();

		//all entities can communicate using messages. They are sent
		//using the MessageDispatcher singleton class
		//virtual void HandleEvent(const int msg_) = 0;

		/**
		 * Get the entity which contains this component
		 */
		BaseEntity* GetEntity();

		/**
		 * Editor
		 */
		virtual void ShowDebugWidget();

		virtual void Read (const tinyxml2::XMLElement& xmlElt);
		virtual void Read (std::ifstream& is);
		virtual void Write(tinyxml2::XMLElement& xmlElt);
		virtual void Write(std::ostream& os);
	};

}

#endif // COMPONENT_H_


