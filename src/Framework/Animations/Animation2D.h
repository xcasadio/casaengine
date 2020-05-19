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
	class CA_EXPORT Animation2D : 
		public Animation
	{
	public:
		Animation2D();
		Animation2D(const Animation2D& rsh);
		const Animation2D& operator = (const Animation2D& rsh);
		~Animation2D();
		
		Animation2D* Copy();

		//EventHandler<Animation2DFrameChangedEventArgs> OnFrameChanged;
		//EventHandler OnEndAnimationReached;

		void Initialize() override;
		void Reset();

		Animation2DType::TAnimation2DType Animation2DType() const;
		void SetType(Animation2DType::TAnimation2DType val);
		
		const char* CurrentFrame() const;
		void CurrentFrame(const char* val);

	private:
		void NotifyFrameListener(const char* frameID_);

		Animation2DType::TAnimation2DType m_Animation2DType;
		const char* m_CurrentFrame;

	private:
		friend class cereal::access;

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<Animation>(this));
			ar(cereal::make_nvp("animation_type", m_Animation2DType));
			
		}

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<Animation>(this));
			ar(cereal::make_nvp("animation_type", m_Animation2DType));
		}

#if EDITOR
	private:
		static const int m_Version; // load version

#endif
		
	};
}

#endif
