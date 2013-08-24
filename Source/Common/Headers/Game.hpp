#ifndef __LD27_GAME_HPP__
#define __LD27_GAME_HPP__

#include <System/DataTypes.hpp>
#include <Renderer/Renderer.hpp>
#include <System/Window.hpp>
#include <Renderer/CanvasDescription.hpp>

namespace LD27
{
	class Game
	{
	public:
		Game( );
		~Game( );

		ZED_UINT32 Initialise( );
		ZED_UINT32 Execute( );

	private:
		void Update( const ZED_UINT64 p_ElapsedTime );
		void Render( );

		ZED::System::Window					*m_pWindow;
		ZED::Renderer::Renderer				*m_pRenderer;
		ZED::Renderer::CanvasDescription	m_Canvas;

		ZED_BOOL	m_Running;
		ZED_BOOL	m_FullScreen;
	};
}

#endif

