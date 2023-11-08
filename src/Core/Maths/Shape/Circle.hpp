#pragma once

#include "CA_Export.hpp"
#include "Maths/Vector3.hpp"

#include "IShape.hpp"

namespace CasaEngine
{
	class CA_EXPORT Circle : public IShape
	{
	public:
		Circle();
		Circle(float radius);
		Circle(const Circle& rsh);
		Circle& operator=(const Circle& rsh);
		~Circle() override;

		Vector3 Center() const;
		void Center(Vector3 val);
		float Radius() const;
		void Radius(float val);

		IShape* Copy() override;
		bool operator==(const IShape& rsh) const override;

	private:
		Vector3 m_Center;
		float m_Radius;
	};
}
