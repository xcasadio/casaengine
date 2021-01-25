#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "CA_Export.h"
#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"

#include "IShape.h"
#include "Parsers/Xml/tinyxml2.h"

namespace CasaEngine
{
	class CA_EXPORT Circle :
		public IShape
	{
	public:
		Circle(float radius_ = 1.0f, Vector3F center_ = Vector3F::Zero());
		~Circle();

		Vector3F Center() const;
		void Center(Vector3F val);
		float Radius() const;
		void Radius(float val);

	private:
		Vector3F m_Center;
		float m_Radius;
	};
}

#endif // CIRCLE_H_
