#ifndef __LD27_GAMEENTITY_HPP__
#define __LD27_GAMEENTITY_HPP__

#include <Arithmetic/Vector3.hpp>
#include <Renderer/Renderer.hpp>
#include <System/DataTypes.hpp>

namespace LD27
{
	// Represents any entity in the game (triggers, enemies, weapons)
	class GameEntity
	{
	public:
		virtual ~GameEntity( ){ }

		void ID( const ZED_UINT32 p_ID ){ m_ID = p_ID; }

		virtual ZED_UINT32 Initialise(
			const ZED::Renderer::Renderer *p_pRenderer ) = 0;
		virtual void Update( ) = 0;
		virtual void Render( ) = 0;

	protected:
		ZED_UINT32	m_ID;
		ZED::Arithmetic::Vector3	m_Position;
	};
}

#endif

