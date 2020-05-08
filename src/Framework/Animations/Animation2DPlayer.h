
#ifndef _ANIMATION2DPLAYER_H_
#define _ANIMATION2DPLAYER_H_

#include "CA_Export.h"
//#include "Utilities\EventHandler.h"
#include <map>
#include "Animation2D.h"

namespace CasaEngine
{
	/**
	 * 
	 */
	class CA_EXPORT Animation2DPlayer
	{
		public:

#if !FINAL
		/// <summary>
		/// Use for debugging
		/// </summary>
		static float m_sAnimationSpeed;
#endif
	
		Animation2DPlayer();
		~Animation2DPlayer();

		//EventHandler<> OnEndAnimationReached;
		//EventHandler<Animation2DFrameChangedEventArgs> OnFrameChanged;

		void Advance(float elapsedTime_);
		void SetCurrentAnimationByID(int id_);
		void SetCurrentAnimationByName(std::string name_);

	private:
		std::map<int, Animation2D*> m_Animations;

		Animation2D* m_pCurrentAnimation;

		// use to detected if we change animation
		int m_iCurrentAnimationIndex;
};

}

#endif // _ANIMATION2DPLAYER_H_
