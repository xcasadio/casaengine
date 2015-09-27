
#ifndef _ANIMATION2D_H_
#define _ANIMATION2D_H_

#include <string>
#include "CA_Export.h"
//#include "Utilities\EventHandler.h"
#include "Animation2DTypes.h"
#include "Frame2D.h"
#include <vector>
#include <sstream>
#include "Animation.h"
#include "Entities\Events\BaseEntityEvents.h"
#include "EventHandler\EventSet.h"

namespace CasaEngine
{
	/**
	 * 
	 */
	class CA_EXPORT Animation2D : 
		public Animation
	{
	public:
		Animation2D();
		Animation2D(const Animation2D& rsh);
		const Animation2D& operator = (const Animation2D& rsh);
		~Animation2D();

		//EventHandler<Animation2DFrameChangedEventArgs> OnFrameChanged;
		//EventHandler OnEndAnimationReached;

		void Reset();

		Animation2DType::TAnimation2DType Animation2DType() const;
		const char* CurrentFrame() const;
		void CurrentFrame(const char* val);

		void Read (std::ifstream& is);
		void Read (const tinyxml2::XMLElement& el_);

	private:
		void NotifyFrameListener(const char* frameID_);

	private:
		Animation2DType::TAnimation2DType m_Animation2DType;
		const char* m_CurrentFrame;

#if EDITOR

	public:

		void Write(tinyxml2::XMLElement& el_);
		void Write(std::ostream&  os);

		void SetType(Animation2DType::TAnimation2DType val);

	private:
		static const int m_Version; // load version

#endif
		
	};
} // namespace CasaEngine

#endif // _ANIMATION2D_H_
