#include <World.hpp>
#include <GameEntity.hpp>
#include <Player.hpp>
#include <System/Memory.hpp>
#include <GameEntity.hpp>

namespace LD27
{
	World::World( )
	{
		m_pRenderer = ZED_NULL;
	}

	World::~World( )
	{
		std::list< GameEntity * >::iterator EntityItr = m_Entities.begin( );

		for( ; EntityItr != m_Entities.end( ); ++EntityItr )
		{
			zedSafeDelete( ( *EntityItr ) );
		}
	}

	ZED_UINT32 World::Initialise( const ZED::Renderer::Renderer *p_pRenderer )
	{
		m_pRenderer = const_cast< ZED::Renderer::Renderer * >( p_pRenderer );

		if( m_pRenderer == ZED_NULL )
		{
			zedTrace( "[LD27::World::Initialise] <ERROR> "
				"Renderer is not valid\n" );

			return ZED_FAIL;
		}

		Player *pNewPlayer = new Player( );
		m_Entities.push_back( pNewPlayer );

		if( pNewPlayer->Initialise( m_pRenderer ) != ZED_OK )
		{
			return ZED_FAIL;
		}

		return ZED_OK;
	}

	void World::Update( const ZED_UINT64 p_ElapsedTime )
	{
		// There should be some procedural method to spawn enemies here
	}

	void World::Render( )
	{
		GameEntityItr Itr = m_Entities.begin( );

		for( ; Itr != m_Entities.end( ); ++Itr )
		{
			( *Itr )->Render( );
		}
	}

	ZED_UINT32 World::LoadLevel( const ZED_CHAR8 *p_pFileName )
	{
		return ZED_FAIL;
	}
}

