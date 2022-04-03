#ifndef BOX_H
#define BOX_H

#include "CA_Export.h"
#include "Maths/Vector3.h"
#include "IShape.h"

namespace CasaEngine
{
	class CA_EXPORT Box :
		public IShape
	{
	public:
		Box(Vector3F size_ = Vector3F::One(), Vector3F center_ = Vector3F::Zero());
		Box(const Box& rsh);
		Box& operator=(const Box& rsh);

		virtual IShape* Copy() override;

		Vector3F Size() const;
		void Size(Vector3F val);
		Vector3F Center() const;
		void Center(Vector3F val);

	private:
		Vector3F m_Center, m_Size;
	};
}
/*
#include <cereal/types/polymorphic.hpp>

CEREAL_REGISTER_TYPE_WITH_NAME(CasaEngine::Box, "box");

CEREAL_REGISTER_POLYMORPHIC_RELATION(CasaEngine::IShape, CasaEngine::Box);
*/
#endif
