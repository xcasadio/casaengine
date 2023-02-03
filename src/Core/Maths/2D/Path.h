#pragma once

//  Desc:   class to define, manage, and traverse a path (defined by a series of 2D vectors)
//  Author: Mat Buckland 2003 (fup@ai-junkie.com)

#include "CA_Export.h"
#include "Maths/Vector2.h"

#include <list>

namespace CasaEngine
{
	class CA_EXPORT Path
	{
	private:

		std::list<Vector2> m_WayPoints;

		//points to the current waypoint
		std::list<Vector2>::iterator m_CurWaypoint;

		//flag to indicate if the path should be looped
		//(The last waypoint connected to the first)
		bool m_bLooped;

	public:

		Path();

		//constructor for creating a path with initial random waypoints. MinX/Y
		//& MaxX/Y define the bounding box of the path.
		Path(std::list<Vector2> path_, bool looped);

		//returns the current waypoint
		Vector2    CurrentWaypoint() const;

		//returns true if the end of the list has been reached
		bool        Finished();

		//moves the iterator on to the next waypoint in the list
		inline void SetNextWaypoint();

		void LoopOn();
		void LoopOff();

		//adds a waypoint to the end of the path
		void AddWayPoint(Vector2 new_point);

		//methods for setting the path with either another Path or a list of vectors
		void Set(std::list<Vector2> new_path);
		void Set(const Path& path);

		void Clear();

		std::list<Vector2> GetPath() const;

		//renders the path in orange
		void Render()const;
	};
}
