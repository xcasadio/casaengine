#pragma once

#include "CA_Export.hpp"
#include  "Maths/Vector3.hpp"
#include  "IShape.hpp"

namespace CasaEngine
{
	class CA_EXPORT Box :
		public IShape
	{
	public:
		Box(Vector3 size_ = Vector3::One(), Vector3 center_ = Vector3::Zero());
		Box(const Box& rsh);
		Box& operator=(const Box& rsh);

		IShape* Copy() override;

		Vector3 Size() const;
		void Size(Vector3 val);
		Vector3 Center() const;
		void Center(Vector3 val);

		bool operator==(const IShape& rsh) const override;

	private:
		Vector3 m_Center, m_Size;
	};
}
