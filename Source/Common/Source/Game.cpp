#include <Game.hpp>
#include <System/Memory.hpp>
#include <System/Time.hpp>
#include <GitVersion.hpp>
#include <cstring>

namespace LD27
{
	Game::Game( )
	{
		m_pRenderer = ZED_NULL;
		m_pWindow = ZED_NULL;

		memset( &m_Canvas, 0, sizeof( m_Canvas ) );

		m_Running = ZED_FALSE;
		m_FullScreen = ZED_FALSE;
	}

	Game::~Game( )
	{
		zedSafeDelete( m_pRenderer );
		zedSafeDelete( m_pWindow );
	}

	ZED_UINT32 Game::Execute( )
	{
		ZED_UINT64	ElapsedTime = 0ULL;
		ZED_UINT64	Accumulator = 0ULL;
		ZED_UINT64	OldTime = ZED::System::GetTimeMiS( );
		ZED_UINT64	FrameTime = ZED::System::GetTimeMiS( );
		ZED_UINT64	TimeStep = 16667ULL;
		ZED_MEMSIZE	FrameRate = 0;
		ZED::System::ZED_WINDOWDATA WinData = m_pWindow->WindowData( );
		char WindowTitle[ 1024 ] = "Red Ring Rico's Ludum Dare #27 Entry";
#if defined ZED_BUILD_DEBUG
		strcat( WindowTitle, " | [DEBUG] | [Ver. " );
		strcat( WindowTitle, GIT_COMMITHASH );
		strcat( WindowTitle, "]" );
#elif defined ZED_BUILD_RELEASE
		strcat( WindowTitle, " | [Ver. " );
		strcat( WindowTitle, GIT_COMMITHASH );
		strcat( WindowTitle, "]" );
#elif defined ZED_BUILD_PROFILE
		strcat( WindowTitle, " | [PROFILE] | [Ver. " );
		strcat( WindowTitle, GIT_COMMITHASH );
		strcat( WindowTitle, "]" );
#else
#error Unknown build target
#endif
// REMINDER!
// Non-cross platform!
		XEvent Event;
// !REMINDER
		m_pWindow->Title( WindowTitle );

		m_Running = ZED_TRUE;

		if( m_World.Initialise( m_pRenderer ) != ZED_OK )
		{
			zedTrace( "[LD27::Game::Execute] <ERROR> "
				"Failed to initialise the world\n" );
			m_Running = ZED_FALSE;
		}

		while( m_Running )
		{
			m_pWindow->Update( );

// REMINDER!
// Bad, non-cross platform code ahead!
			while( XPending( WinData.pX11Display ) > 0 )
			{
				XNextEvent( WinData.pX11Display, &Event );

				switch( Event.type )
				{
					default:
					{
						break;
					}
				}
			}
// !REMINDER
			
			if( m_pWindow->Closed( ) )
			{
				m_Running = ZED_FALSE;
				continue;
			}

			const ZED_UINT64 NewTime = ZED::System::GetTimeMiS( );
			ZED_UINT64 DeltaTime = NewTime - OldTime;

			if( DeltaTime > 250000ULL )
			{
				DeltaTime = 250000ULL;
			}

			OldTime = NewTime;
			Accumulator += DeltaTime;

			while( Accumulator >= TimeStep )
			{
				this->Update( TimeStep );

				ElapsedTime += TimeStep;
				Accumulator -= DeltaTime;
			}

			this->Render( );
			++FrameRate;

			if( ( NewTime - FrameTime ) > 1000000ULL )
			{
				zedTrace( "FPS: %d\n", FrameRate );
				FrameTime = ZED::System::GetTimeMiS( );
				FrameRate = 0;
			}
		}

		return ZED_OK;
	}

	void Game::Update( const ZED_UINT64 p_ElapsedTime )
	{
		m_World.Update( p_ElapsedTime );
	}

	void Game::Render( )
	{
		m_pRenderer->BeginScene( ZED_TRUE, ZED_TRUE, ZED_TRUE );
		m_pRenderer->EndScene( );
	}
}

