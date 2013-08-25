#ifndef __LD27_WORLD_HPP__
#define __LD27_WORLD_HPP__

#include <list>
#include <Renderer/Renderer.hpp>
#include <System/DataTypes.hpp>

namespace LD27
{
	class GameEntity;

	class World
	{
	public:
		World( );
		~World( );

		ZED_UINT32 Initialise( const ZED::Renderer::Renderer *p_pRenderer );
		void Update( const ZED_UINT64 p_ElapsedTime );
		void Render( );

		ZED_UINT32 LoadLevel( const ZED_CHAR8 *p_pFileName );

	private:

		typedef std::list< GameEntity * > GameEntityList;
		typedef std::list< GameEntity * >::iterator GameEntityItr;

		GameEntityList				m_Entities;
		ZED::Renderer::Renderer		*m_pRenderer;
	};
}

#endif

