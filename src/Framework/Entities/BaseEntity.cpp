#include "Base.h"
#include "BaseEntity.h"

//#include "Utilities/EventHandler.h"
#include "ComponentMessageEnum.h"
#include "Events/BaseEntityEvents.h"
#include "EntityManager.h"
#include <sstream>

#include "Game/Game.h"
#include "Memory/MemoryAllocation.h"
#include "Log/LogManager.h"


namespace CasaEngine
{
	EntityId BaseEntity::m_iNextValidID = 0;

	/**
	 *	setting the ID and incrementing
	 *	the next valid ID
	 */
	BaseEntity::BaseEntity() :
		m_PhysicalEntity(this)
	{
		m_ID = m_iNextValidID;    
		m_iNextValidID++;

		std::ostringstream s;
		s << "entity_" << m_ID;
		m_szName = _strdup(s.str().c_str());
		m_pComponentManager = NEW_AO ComponentManager(this);
		m_bIsEnabled = true;
		m_bIsVisible = true;
		m_pParent = nullptr;

		addEvent(EntityParentChangeEvent::GetEventName());
		Game::Instance().GetEntityManager().RegisterEntity(this);

#ifdef EDITOR
		m_IsSelected = false;
#endif
	}

	/**
	 *	
	 */
	BaseEntity::~BaseEntity()
	{
		//EntityMgr.RemoveEntity(this);
		DELETE_AO m_pComponentManager;
		::free((void *)m_szName);
	}

	EntityId BaseEntity::ID() const
	{
		return m_ID;
	}

	/**
	 *	
	 */
	BaseEntity* BaseEntity::GetParent() const 
	{ 
		return m_pParent; 
	}

	/**
	 *	
	 */
	void BaseEntity::SetParent(BaseEntity* val) 
	{ 
		m_pParent = val;

		EntityParentChangeEvent event(this, m_pParent);
		fireEvent(EntityParentChangeEvent::GetEventName(), event);
	}

	/**
	 *	
	 */
	ComponentManager* BaseEntity::GetComponentMgr()
	{ 
		return m_pComponentManager;
	}

	/**
	 * 
	 */
	bool BaseEntity::HandleMessage(const Telegram& msg)
	{
		return m_pComponentManager->HandleMessage(msg);
	}

	/**
	 * 
	 */
	void BaseEntity::Update(const GameTime& gameTime_)
	{
		if (m_bIsEnabled == false)
		{
			return;
		}

		m_PhysicalEntity.Update(gameTime_);
		m_pComponentManager->Update(gameTime_);
	}

	/**
	 * 
	 */
	void BaseEntity::Draw()
	{
		if (m_bIsVisible == false)
		{
			return;
		}

		m_pComponentManager->Draw();
	}

	/**
	 * 
	 */
	const char *BaseEntity::GetName() const 
	{ 
		return m_szName; 
	}

	/**
	 * 
	 */
	void BaseEntity::SetName(const char * val) 
	{ 
		::free((void *)m_szName);
		m_szName = strdup(val); 
	}

	/**
	 * 
	 */
	void BaseEntity::Initialize()
	{
		m_pComponentManager->InitializeComponents();
	}

	/**
	 * 
	 */
	bool BaseEntity::IsEnabled() const
	{
		return m_bIsEnabled;
	}

	/**
	 * 
	 */
	void BaseEntity::IsEnabled( bool val )
	{
		m_bIsEnabled = val;
	}

	/**
	 * 
	 */
	bool BaseEntity::IsVisible() const
	{
		return m_bIsVisible;
	}

	/**
	 * 
	 */
	void BaseEntity::IsVisible( bool val )
	{
		m_bIsVisible = val;
	}
	

	/**
	 * 
	 */
	void BaseEntity::Read (std::ifstream& /*is*/)
	{

	}

	/**
	 * 
	 */
	void BaseEntity::Read (const tinyxml2::XMLElement& xmlElt)
	{

	}

	/**
	 * 
	 */
	void BaseEntity::Write(std::ostream& /*os*/)
	{

	}

	/**
	 * 
	 */
	void BaseEntity::Write(tinyxml2::XMLElement& xmlElt)
	{

	}

	PhysicalEntity & BaseEntity::GetPhysicalEntity()
	{
		return m_PhysicalEntity;
	}
	
//#ifdef EDITOR
	
	void BaseEntity::IsSelected(bool val)
	{
		m_IsSelected = val;
	}

	bool BaseEntity::IsSelected() const
	{
		return m_IsSelected;
	}
	
//#endif	

}
