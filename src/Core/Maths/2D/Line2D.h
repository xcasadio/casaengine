#ifndef LINE2D_H
#define LINE2D_H

#include "Base.h"
#include "Maths\Vector2.h"

namespace CasaEngine
{
	class CA_EXPORT Line2D
	{
	public:
		Line2D();
		Line2D(Vector2F A, Vector2F B);
		Line2D(Vector2F A, Vector2F B, Vector2F N);
		Line2D(std::ifstream& in);

		virtual void Render(bool RenderNormals = false) const;

		Vector2F From() const;
		void     SetFrom(Vector2F v);

		Vector2F To() const;
		void     SetTo(Vector2F v);

		Vector2F Normal() const;
		void     SetNormal(Vector2F n);

		Vector2F Center() const;
		
		std::ostream& Write(std::ostream& os) const;
		void Read(std::ifstream& in);

	protected:

		Vector2F m_vA, m_vB, m_vN;
		void CalculateNormal();
	};
}

#endif
