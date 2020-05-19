#include "Base.h"
#include "CA_Assert.h"
#include "Box.h"

namespace CasaEngine
{
	Box::Box(Vector3F size_, Vector3F center_) :
		IShape(BOX)
	{
		m_Center = center_;
		m_Size = size_;
	}

	Box::~Box()
	{

	}

	Vector3F Box::Size() const
	{
		return m_Size;
	}

	void Box::Size(Vector3F val)
	{
		m_Size = val;
	}

	Vector3F Box::Center() const
	{
		return m_Center;
	}

	void Box::Center(Vector3F val)
	{
		m_Center = val;
	}

	void Box::Read(const tinyxml2::XMLElement& node_)
	{

	}

	void Box::Read(std::ifstream& /*in*/)
	{
	}

	void Box::Write(const tinyxml2::XMLElement& node_)
	{
	}

	void Box::Write(std::ostream& os)
	{
	}
}
