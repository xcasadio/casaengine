//==========================================================
// En-têtes
//==========================================================
#include "Base.h"

#include "Animations/SetFrameEvent.h"
#include <string>
#include "Animation.h"
#include "Animation2D.h"
#include "Log/LogManager.h"
#include "Parsers/Xml/tinyxml2.h"
#include <ostream>
#include <sstream>
#include <fstream>
#include "Macro.h"
#include "CA_Assert.h"

namespace CasaEngine
{
	/**
	 *
	 */
	SetFrameEvent::SetFrameEvent()
	{

	}

	/**
	 * 
	 */
	SetFrameEvent::SetFrameEvent(const SetFrameEvent& rsh)
	{
		*this = rsh;
	}

	/**
	 * 
	 */
	const SetFrameEvent& SetFrameEvent::operator = (const SetFrameEvent& rsh)
	{
		m_FrameID = rsh.m_FrameID;
		return *this;
	}

	/**
	 * 
	 */
	SetFrameEvent::~SetFrameEvent()
	{

	}

	/**
	 * 
	 */
	const char* SetFrameEvent::FrameID() const
	{
		return m_FrameID.c_str();
	}

	/**
	 * 
	 */
	void SetFrameEvent::Activate(Animation *pAnim_)
	{
		CA_ASSERT(pAnim_ != nullptr, "SetFrameEvent::Activate() : Animation is nullptr");

		Animation2D *pAnim2D = static_cast<Animation2D *>(pAnim_);

		if (pAnim2D != nullptr)
		{
			pAnim2D->CurrentFrame(m_FrameID.c_str());
		}
		else
		{
			CA_ERROR("SetFrameEvent.Activate() : Animation(%d - %s) is not a Animation2D\n", 
				pAnim_->ID(), pAnim_->GetName().c_str());
		}
	}

	/**
	 * 
	 */
	void SetFrameEvent::Read (std::ifstream& /*is*/)
	{

	}

	/**
	 * 
	 */
	void SetFrameEvent::Read(tinyxml2::XMLElement *el_)
	{
		AnimationEvent::Read(el_);

		unsigned int spriteID;
		el_->QueryUnsignedAttribute("spriteID", &spriteID);

		std::ostringstream str;
		str << spriteID;

		m_FrameID = str.str().c_str();
	}


#if EDITOR

	/**
	 * 
	 */
	void SetFrameEvent::FrameID( const char* val )
	{
		m_FrameID = val;
	}
	
	/**
	 * 
	 */
	void SetFrameEvent::Write(std::ostream& /*os*/) const
	{

	}

	/**
	 * 
	 */
	void SetFrameEvent::Write(tinyxml2::XMLElement *el_) const
	{

	}

#endif // EDITOR


} // namespace CasaEngine
