#ifndef __LD27_PLAYER_HPP__
#define __LD27_PLAYER_HPP__

#include <GameEntity.hpp>
#include <Renderer/Model.hpp>
#include <Renderer/Shader.hpp>

namespace LD27
{
	class Player : public GameEntity
	{
	public:
		Player( );
		virtual ~Player( );

		virtual ZED_UINT32 Initialise(
			const ZED::Renderer::Renderer *p_pRenderer );
		virtual void Update( );
		virtual void Render( );

	private:
		ZED::Renderer::Model	*m_pModel;
		ZED::Renderer::Renderer	*m_pRenderer;
		ZED::Renderer::Shader	*m_pShader;
	};
}

#endif

