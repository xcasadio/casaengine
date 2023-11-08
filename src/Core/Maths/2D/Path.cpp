#include  "Base.hpp"
#include  "Log/LogManager.hpp"

#include  "Path.hpp"
#include  "Transformations.hpp"
#include  "Maths/Random.hpp"
#include  "CA_Assert.hpp"

namespace CasaEngine
{
	Path::Path() :
		m_bLooped(false)
	{
	}

	//constructor for creating a path with initial random waypoints. MinX/Y
	//& MaxX/Y define the bounding box of the path.
	Path::Path(std::list<Vector2> path_, bool looped) :
		m_bLooped(looped)
	{
		Set(path_);
	}

	//returns the current waypoint
	Vector2 Path::CurrentWaypoint() const
	{
		return *m_CurWaypoint;
	}

	//returns true if the end of the list has been reached
	bool Path::Finished()
	{
		return !(m_CurWaypoint != m_WayPoints.end());
	}

	//moves the iterator on to the next waypoint in the list
	inline void Path::SetNextWaypoint()
	{
		CA_ASSERT(m_WayPoints.size() > 0, "Path::SetNextWaypoint()")

			if (++m_CurWaypoint == m_WayPoints.end())
			{
				if (m_bLooped)
				{
					m_CurWaypoint = m_WayPoints.begin();
				}
			}
	}

	void Path::LoopOn()
	{
		m_bLooped = true;
	}

	void Path::LoopOff()
	{
		m_bLooped = false;
	}

	//adds a waypoint to the end of the path
	void Path::AddWayPoint(Vector2 new_point)
	{
		m_WayPoints.push_back(new_point);
	}

	//methods for setting the path with either another Path or a list of vectors
	void Path::Set(std::list<Vector2> new_path)
	{
		m_WayPoints = new_path;
		m_CurWaypoint = m_WayPoints.begin();
	}

	void Path::Set(const Path& path)
	{
		m_WayPoints = path.GetPath();
		m_CurWaypoint = m_WayPoints.begin();
	}

	void Path::Clear()
	{
		m_WayPoints.clear();
	}

	std::list<Vector2> Path::GetPath() const
	{
		return m_WayPoints;
	}

	void Path::Render()const
	{
		/*gdi->OrangePen();

		std::list<Vector2>::const_iterator it = m_WayPoints.begin();

		Vector2 wp = *it++;

		while (it != m_WayPoints.end())
		{
		  gdi->Line(wp, *it);

		  wp = *it++;
		}

		if (m_bLooped) gdi->Line(*(--it), *m_WayPoints.begin());*/
	}
}