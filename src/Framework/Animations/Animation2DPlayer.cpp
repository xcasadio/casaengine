
#include  "Base.hpp"
#include  "Animation2DPlayer.hpp"


namespace CasaEngine
{

	float Animation2DPlayer::m_sAnimationSpeed = 1.0f;

	/**
	 *
	 */
	Animation2DPlayer::Animation2DPlayer() :
		m_pCurrentAnimation(NULL),
		m_iCurrentAnimationIndex(-1)
	{
	}

	/**
	 *
	 */
	Animation2DPlayer::~Animation2DPlayer()
		= default;

	void Animation2DPlayer::SetCurrentAnimationByID(int id_)
	{
		if (m_iCurrentAnimationIndex != id_)
		{
			m_iCurrentAnimationIndex = id_;
			m_pCurrentAnimation = m_Animations[id_];
			//m_pCurrentAnimation->ResetTime();
		}
	}

	/**
	 *
	 */
	void Animation2DPlayer::SetCurrentAnimationByName(std::string name_)
	{
		int index = -1;

		std::map<int, Animation2D*>::const_iterator it;

		for (it = m_Animations.cbegin(); it != m_Animations.cend(); it++)
		{
			if (it->second->GetAnimationData()->GetName() == name_)
			{
				index = it->first;
			}
		}

		if (m_iCurrentAnimationIndex != index)
		{
			m_iCurrentAnimationIndex = index;
			m_pCurrentAnimation = m_Animations[index];
			//m_pCurrentAnimation->ResetTime();
		}
	}

	/**
	 *
	 */
	void Animation2DPlayer::Advance(float elapsedTime_)
	{
#if !FINAL	
		elapsedTime_ *= m_sAnimationSpeed;
#endif


	}

}
