#ifndef _ANIMATION2D_H_
#define _ANIMATION2D_H_

#include <string>
#include "CA_Export.h"
#include <vector>
#include "Animation.h"
#include "Entities\Events\BaseEntityEvents.h"
#include "EventHandler\EventSet.h"
#include <Datas/Animation2DData.h>

namespace CasaEngine
{
	class CA_EXPORT Animation2D : 
		public Animation
	{
	public:
		Animation2D(Animation2DData& data);
		~Animation2D();

		//EventHandler<Animation2DFrameChangedEventArgs> OnFrameChanged;
		//EventHandler OnEndAnimationReached;

		void Initialize() override;
		void Reset();
		
		const char* CurrentFrame() const;
		void CurrentFrame(const char* val);

	private:
		void NotifyFrameListener(const char* frameID_);

		const char* m_CurrentFrame;
		Animation2DData* m_pAnimation2DData;

#if EDITOR
	private:
		static const int m_Version; // load version

#endif
		
	};
}

#endif
