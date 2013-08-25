#ifndef __LD27_WORLD_HPP__
#define __LD27_WORLD_HPP__

#include <list>

namespace LD27
{
	class GameEntity;

	class World
	{
	public:
		World( );
		~World( );

	private:
		std::list< GameEntity * > m_Entities;		
	};
}

#endif

