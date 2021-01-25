#include "Base.h"

#include "Animations/Animation2D.h"
#include <string>
#include "SetFrameEvent.h"
#include <ostream>
#include "Parsers/Xml/tinyxml2.h"
#include <sstream>
#include <fstream>
#include "Memory/MemoryAllocation.h"
#include "Entities/EntityManager.h"
#include "Entities/Events/BaseEntityEvents.h"

namespace CasaEngine
{
	Animation2D::Animation2D() :
		Animation(),
		m_Animation2DType(Animation2DType::Loop),
		m_CurrentFrame(nullptr)
	{
		addEvent(FrameChangeEvent::GetEventName());
	}

	Animation2D::Animation2D(const Animation2D& rsh)
	{
		*this = rsh;
	}

	const Animation2D& Animation2D::operator = (const Animation2D& rsh)
	{
		addEvent(FrameChangeEvent::GetEventName());
		this->Animation::operator=(rsh);
		this->m_Animation2DType = rsh.m_Animation2DType;

		return *this;
	}

	Animation2D::~Animation2D()
	{

	}

	Animation2D* Animation2D::Copy()
	{
		return NEW_AO Animation2D(*this);
	}

	void Animation2D::Initialize()
	{
		Animation::Initialize();
		Reset();
	}

	Animation2DType::TAnimation2DType Animation2D::Animation2DType() const
	{ 
		return m_Animation2DType; 
	}

	void Animation2D::SetType(Animation2DType::TAnimation2DType val)
	{
		m_Animation2DType = val;
	}

	void Animation2D::Reset()
	{
		for (unsigned int i=0; i<m_Events.size(); i++)
		{
			SetFrameEvent *pFrameEvent = dynamic_cast<SetFrameEvent *>(m_Events[i]);
			if (pFrameEvent != nullptr)
			{
				CurrentFrame(pFrameEvent->FrameID());
				break;
			}
		}
	}

	const char* Animation2D::CurrentFrame() const 
	{ 
		return m_CurrentFrame; 
	}

	void Animation2D::CurrentFrame(const char* val) 
	{ 
		m_CurrentFrame = val;

		fireEvent(FrameChangeEvent::GetEventName(), FrameChangeEvent(m_CurrentFrame));
	}
}
