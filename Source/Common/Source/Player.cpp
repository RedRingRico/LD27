#include <Player.hpp>
#include <System/Memory.hpp>

namespace LD27
{
	Player::Player( )
	{
		m_pRenderer = ZED_NULL;
		m_pModel = ZED_NULL;
	}

	Player::~Player( )
	{
		zedSafeDelete( m_pModel );
	}

	ZED_UINT32 Player::Initialise( const ZED::Renderer::Renderer *p_pRenderer )
	{
		m_pRenderer = const_cast< ZED::Renderer::Renderer * >( p_pRenderer );

		if( m_pRenderer == ZED_NULL )
		{
			return ZED_FAIL;
		}

		return ZED_OK;
	}

	void Player::Update( )
	{
	}

	void Player::Render( )
	{
		m_pModel->Render( );
	}
}

