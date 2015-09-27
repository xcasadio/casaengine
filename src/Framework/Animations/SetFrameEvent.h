
#ifndef _CHANGEFRAMEEVENT_H_
#define _CHANGEFRAMEEVENT_H_

#include <string>
#include "CA_Export.h"
#include <vector>
#include "AnimationEvent.h"
#include "Parsers\Xml\tinyxml2.h"

namespace CasaEngine
{
	/**
	 * 
	 */
	class CA_EXPORT SetFrameEvent : 
		public AnimationEvent
	{
	public:
		SetFrameEvent();
		SetFrameEvent(const SetFrameEvent& rsh);
		const SetFrameEvent& operator = (const SetFrameEvent& rsh);
		~SetFrameEvent();

		void Activate(Animation *pAnim_);

		const char* FrameID() const;

		void Read(std::ifstream& /*is*/);
		void Read(tinyxml2::XMLElement *el_);

	private:
		std::string m_FrameID;
		
#if EDITOR
	public:
		void FrameID(const char* val);

		void Write(std::ostream& /*os*/) const;
		void Write(tinyxml2::XMLElement *el_) const;

	private:
		static const int m_Version; // load version

#endif
		
	};
} // namespace CasaEngine

#endif // _CHANGEFRAMEEVENT_H_
