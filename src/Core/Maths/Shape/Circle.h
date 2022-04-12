#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "CA_Export.h"
#include "Maths/Vector3.h"

#include "IShape.h"

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
		
	private:
		Vector3 m_Center;
		float m_Radius;
	};
}

#endif // CIRCLE_H_
