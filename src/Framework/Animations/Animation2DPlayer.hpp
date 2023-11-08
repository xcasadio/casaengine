#pragma once

#include "CA_Export.hpp"
//#include  "Utilities\EventHandler.hpp"
#include <map>
#include  "Animation2D.hpp"

namespace CasaEngine
{
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
