#include "Base.h"

#include "BaseEntity.h"
#include "Events/BaseEntityEvents.h"
#include "EntityManager.h"
#include "Game/Game.h"

#include <sstream>

namespace CasaEngine
{
	unsigned int BaseEntity::_nextValidId = 0;
	
	BaseEntity::BaseEntity() :
		_id(_nextValidId), _parent(nullptr),
		_componentManager(new ComponentManager(this)),
		_physicalEntity(this),
		_isEnabled(true),
		_isVisible(true)
	{
		_nextValidId++;

		std::ostringstream s;
		s << "entity_" << _id;
		_name = s.str();

		addEvent(EntityParentChangeEvent::GetEventName());
		Game::Instance().GetEntityManager().RegisterEntity(this);

#ifdef EDITOR
		_isSelected = false;
		_isPersistent = true;
#endif
	}

	BaseEntity::~BaseEntity()
	{
		delete _componentManager;
	}

	unsigned int BaseEntity::Id() const
	{
		return _id;
	}

	BaseEntity* BaseEntity::GetParent() const 
	{ 
		return _parent; 
	}

	void BaseEntity::SetParent(BaseEntity* val) 
	{ 
		_parent = val;
		_coordinates.SetParent(_parent != nullptr ? &_parent->GetCoordinates() : nullptr);

		EntityParentChangeEvent event(this, _parent);
		fireEvent(EntityParentChangeEvent::GetEventName(), event);
	}

	ComponentManager* BaseEntity::GetComponentMgr()
	{ 
		return _componentManager;
	}

	bool BaseEntity::HandleMessage(const Telegram& msg)
	{
		return _componentManager->HandleMessage(msg);
	}

	void BaseEntity::Update(const GameTime& gameTime_)
	{
		if (_isEnabled == false)
		{
			return;
		}

		_physicalEntity.Update(gameTime_);
		_componentManager->Update(gameTime_);
	}

	void BaseEntity::Draw()
	{
		if (_isVisible == false)
		{
			return;
		}

		_componentManager->Draw();
	}

	const char *BaseEntity::GetName() const 
	{ 
		return _name.c_str();
	}

	void BaseEntity::SetName(std::string &val)
	{
		_name = val;
	}

	void BaseEntity::SetName(const char * val) 
	{
		_name = val;
	}

	Coordinates& BaseEntity::GetCoordinates()
	{
		return _coordinates;
	}

	void BaseEntity::Initialize()
	{
		_componentManager->InitializeComponents();
	}

	bool BaseEntity::IsEnabled() const
	{
		return _isEnabled;
	}

	void BaseEntity::IsEnabled( bool val )
	{
		_isEnabled = val;
	}

	bool BaseEntity::IsVisible() const
	{
		return _isVisible;
	}

	void BaseEntity::IsVisible( bool val )
	{
		_isVisible = val;
	}

	void BaseEntity::Read (std::ifstream& /*is*/)
	{

	}

	void BaseEntity::Write(std::ostream& /*os*/)
	{

	}

	PhysicalEntity & BaseEntity::GetPhysicalEntity()
	{
		return _physicalEntity;
	}
	
#ifdef EDITOR
	void BaseEntity::IsSelected(bool val)
	{
		_isSelected = val;
	}

	bool BaseEntity::IsSelected() const
	{
		return _isSelected;
	}

	void BaseEntity::IsPersistent(bool val)
	{
		_isSelected = val;
	}

	bool BaseEntity::IsPersistent() const
	{
		return _isSelected;
	}
#endif
}
