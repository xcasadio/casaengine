//==========================================================
// En-têtes
//==========================================================
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
	/**
	 * 
	 */
	Animation2D::Animation2D() :
		Animation(),
		m_Animation2DType(Animation2DType::Loop),
		m_CurrentFrame(nullptr)
	{
		addEvent(FrameChangeEvent::GetEventName());
	}

	/**
	 * 
	 */
	Animation2D::Animation2D(const Animation2D& rsh)
	{
		addEvent(FrameChangeEvent::GetEventName());
		*this = rsh;
	}

	/**
	 * 
	 */
	const Animation2D& Animation2D::operator = (const Animation2D& rsh)
	{
		this->Animation::operator=(rsh);
		this->m_Animation2DType = rsh.m_Animation2DType;

		return *this;
	}

	/**
	 * 
	 */
	Animation2D::~Animation2D()
	{

	}

	/**
	 * 
	 */
	Animation2DType::TAnimation2DType Animation2D::Animation2DType() const
	{ 
		return m_Animation2DType; 
	}

	/**
	 *
	 */
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

	/**
	 * 
	 */
	const char* Animation2D::CurrentFrame() const 
	{ 
		return m_CurrentFrame; 
	}

	/**
	 * 
	 */
	void Animation2D::CurrentFrame(const char* val) 
	{ 
		m_CurrentFrame = val;

		fireEvent(FrameChangeEvent::GetEventName(), FrameChangeEvent(m_CurrentFrame));
	}

	/**
	 * 
	 */
	void Animation2D::Read( std::ifstream& /*is*/ )
	{

	}

	/**
	 * 
	 */
	void Animation2D::Read(const tinyxml2::XMLElement& el_ )
	{
		Animation::Read(el_);

		const tinyxml2::XMLElement *pElemFrame = el_.FirstChildElement("EventList")->FirstChildElement("Event");

		//float totalTime = 0.0f;

		while (pElemFrame != nullptr)
		{
			SetFrameEvent *pFrameEvent = NEW_AO SetFrameEvent();
			pFrameEvent->Read(const_cast<tinyxml2::XMLElement *>(pElemFrame));
			AddEvent(pFrameEvent);

			pElemFrame = pElemFrame->NextSiblingElement();

			/*unsigned int spriteID;
			pElemFrame->QueryUnsignedAttribute("spriteID", &spriteID);
			float time;
			pElemFrame->QueryFloatAttribute("time", &time);

			std::ostringstream str;
			str << spriteID;

			SetFrameEvent *pFrameEvent = NEW_AO SetFrameEvent();
			pFrameEvent->FrameID(str.str().c_str());
			pFrameEvent->Time(time + totalTime);
			AddEvent(pFrameEvent);

			pElemFrame = pElemFrame->NextSiblingElement();
			totalTime += time;*/
		}
	}

#if EDITOR

	/**
	 * 
	 */
	void Animation2D::SetType(Animation2DType::TAnimation2DType val) 
	{ 
		m_Animation2DType = val; 
	}



	/**
	 * 
	 */
	void Animation2D::Write( tinyxml2::XMLElement& el_ )
	{

	}

	/**
	 * 
	 */
	void Animation2D::Write( std::ostream& os )
	{

	}

#endif

} // namespace CasaEngine
