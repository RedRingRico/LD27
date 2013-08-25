#include <World.hpp>
#include <GameEntity.hpp>

namespace LD27
{
	World::World( )
	{
		m_pRenderer = ZED_NULL;
	}

	World::~World( )
	{
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

		return ZED_OK;
	}

	void World::Update( const ZED_UINT64 p_ElapsedTime )
	{
	}

	void World::Render( )
	{
	}
}

