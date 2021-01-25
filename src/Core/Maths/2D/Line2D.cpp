#include "Base.h"
#include "Line2D.h"

namespace CasaEngine
{
	void Line2D::CalculateNormal()
	{
		Vector2F temp = m_vB - m_vA;
		temp.Normalize();

		m_vN.x = -temp.y;
		m_vN.y = temp.x;
	}

	Line2D::Line2D() {}

	Line2D::Line2D(Vector2F A, Vector2F B) :m_vA(A), m_vB(B)
	{
		CalculateNormal();
	}

	Line2D::Line2D(Vector2F A, Vector2F B, Vector2F N) : m_vA(A), m_vB(B), m_vN(N)
	{ }

	Line2D::Line2D(std::ifstream& in)
	{
		Read(in);
	}

	void Line2D::Render(bool /*RenderNormals*/) const
	{
		/*gdi->Line(m_vA, m_vB);

		//render the normals if rqd
		if (RenderNormals)
		{
		  int MidX = (int)((m_vA.x+m_vB.x)/2);
		  int MidY = (int)((m_vA.y+m_vB.y)/2);

		  gdi->Line(MidX, MidY, (int)(MidX+(m_vN.x * 5)), (int)(MidY+(m_vN.y * 5)));
		}*/
	}

	Vector2F Line2D::From()const { return m_vA; }
	void     Line2D::SetFrom(Vector2F v) { m_vA = v; CalculateNormal(); }

	Vector2F Line2D::To()const { return m_vB; }
	void     Line2D::SetTo(Vector2F v) { m_vB = v; CalculateNormal(); }

	Vector2F Line2D::Normal()const { return m_vN; }
	void     Line2D::SetNormal(Vector2F n) { m_vN = n; }

	Vector2F Line2D::Center()const { return (m_vA + m_vB) / 2.0; }

	std::ostream& Line2D::Write(std::ostream& os)const
	{
		os << std::endl;
		os << From() << ",";
		os << To() << ",";
		os << Normal();
		return os;
	}

	void Line2D::Read(std::ifstream& in)
	{
		float x, y;

		in >> x >> y;
		SetFrom(Vector2F(x, y));

		in >> x >> y;
		SetTo(Vector2F(x, y));

		in >> x >> y;
		SetNormal(Vector2F(x, y));
	}
}