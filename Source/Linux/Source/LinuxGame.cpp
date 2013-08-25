#include <Game.hpp>
#include <Renderer/LinuxRendererOGL3.hpp>
#include <System/LinuxWindow.hpp>

namespace LD27
{
	ZED_UINT32 Game::Initialise( )
	{
		ZED_UINT32 X = 0, Y = 0, Width = 0, Height = 0;
		ZED::System::ZED_SCREENSIZE	NativeSize;
		ZED::System::ZED_SCREENSIZE *pScreenSizes = ZED_NULL;
		ZED_MEMSIZE ScreenSizeCount = 0;
		ZED_UINT32 WindowStyle = 0;

		ZED::System::EnumerateScreenSizes( &pScreenSizes, &ScreenSizeCount, 0,
			ZED::System::GetCurrentScreenNumber( ) );

		if( ZED::System::GetNativeScreenSize( 0,
			ZED::System::GetCurrentScreenNumber( ), NativeSize ) != ZED_OK )
		{
			zedTrace( "[LD27::Game::Initialise] <ERROR> "
				"Failed to get native screen size\n" );

			return ZED_FAIL;
		}

		if( m_FullScreen == ZED_TRUE )
		{
			X = 0;
			Y = 0;
			Width = NativeSize.Width;
			Height = NativeSize.Height;

			WindowStyle |= ZED_WINDOW_STYLE_FULLSCREEN;
		}
		else
		{
#if defined ZED_BUILD_DEBUG
			Width = 1280;
			Height = 720;

			X = ( NativeSize.Width / 2 ) - ( Width / 2 );
			Y = ( NativeSize.Height / 2 ) - ( Height / 2 );
#else
			Width = 1280;
			Height = 720;

			X = ( NativeSize.Width / 2 ) - ( Width / 2 );
			Y = ( NativeSize.Height / 2 ) - ( Height / 2 );
#endif
			WindowStyle |= ZED_WINDOW_STYLE_ALL;
		}

		m_pWindow = new ZED::System::LinuxWindow( );
		m_pRenderer = new ZED::Renderer::LinuxRendererOGL3( );

		m_pWindow->Create( X, Y, Width, Height, 0,
			ZED::System::GetCurrentScreenNumber( ), WindowStyle );

		m_Canvas.Width( Width );
		m_Canvas.Height( Height );
		m_Canvas.BackBufferCount( 1 );
		m_Canvas.ColourFormat( ZED_FORMAT_ARGB8 );
		m_Canvas.DepthStencilFormat( ZED_FORMAT_D24S8 );

		m_pRenderer->Create( m_Canvas, ( *m_pWindow ) );

		m_pRenderer->ClearColour( 1.0f, 0.0f, 1.0f );

#if defined ZED_BUILD_DEBUG
// REMINDER!
// Cullmode should be CCW
		m_pRenderer->SetRenderState( ZED_RENDERSTATE_CULLMODE,
			ZED_CULLMODE_NONE );
// !REMINDER
#endif
		m_pRenderer->SetRenderState( ZED_RENDERSTATE_DEPTH, ZED_ENABLE );
		m_pRenderer->SetClippingPlanes( 1.0f, 100000.0f );
		m_pRenderer->PerspectiveProjectionMatrix( 45.0f,
			static_cast< ZED_FLOAT32 >( Width ) /
			static_cast< ZED_FLOAT32 >( Height ) );

		return ZED_OK;
	}
}

