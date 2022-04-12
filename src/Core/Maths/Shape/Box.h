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
		Box(Vector3 size_ = Vector3::One(), Vector3 center_ = Vector3::Zero());
		Box(const Box& rsh);
		Box& operator=(const Box& rsh);

		virtual IShape* Copy() override;

		Vector3 Size() const;
		void Size(Vector3 val);
		Vector3 Center() const;
		void Center(Vector3 val);

	private:
		Vector3 m_Center, m_Size;
	};
}
/*
#include <cereal/types/polymorphic.hpp>

CEREAL_REGISTER_TYPE_WITH_NAME(CasaEngine::Box, "box");

CEREAL_REGISTER_POLYMORPHIC_RELATION(CasaEngine::IShape, CasaEngine::Box);
*/
#endif
