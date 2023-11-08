#ifndef LINE2D_H
#define LINE2D_H

#include  "Base.hpp"
#include  "Maths/Vector2.hpp"

namespace CasaEngine
{
	class CA_EXPORT Line2D
	{
	public:
		Line2D();
		Line2D(Vector2 A, Vector2 B);
		Line2D(Vector2 A, Vector2 B, Vector2 N);
		Line2D(std::ifstream& in);

		virtual void Render(bool RenderNormals = false) const;

		Vector2 From() const;
		void     SetFrom(Vector2 v);

		Vector2 To() const;
		void     SetTo(Vector2 v);

		Vector2 Normal() const;
		void     SetNormal(Vector2 n);

		Vector2 Center() const;

		std::ostream& Write(std::ostream& os) const;
		void Read(std::ifstream& in);

	protected:

		Vector2 m_vA, m_vB, m_vN;
		void CalculateNormal();
	};
}

#endif
