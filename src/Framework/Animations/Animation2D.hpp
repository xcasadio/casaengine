#pragma once

#include "CA_Export.hpp"
#include  "Animation.hpp"
#include <Datas/Animation2DData.hpp>

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
		void Reset() override;

		const char* CurrentFrame() const;
		void CurrentFrame(const char* val);

		Animation2DData* GetAnimation2DData();

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
