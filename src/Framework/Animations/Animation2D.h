#pragma once

#include "CA_Export.h"
#include "Animation.h"
#include <Datas/Animation2DData.h>

namespace CasaEngine
{
	class CA_EXPORT Animation2D : 
		public Animation
	{
	public:
		Animation2D(Animation2DData& data);

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
	public:
		Animation2DData* GetAnimation2DData();

	private:
		static const int m_Version; // load version

#endif
		
	};
}
