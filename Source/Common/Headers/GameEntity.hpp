#ifndef __LD27_GAMEENTITY_HPP__
#define __LD27_GAMEENTITY_HPP__

#include <Arithmetic/Vector3.hpp>
#include <System/DataTypes.hpp>

namespace LD27
{
	// Represents any entity in the game (triggers, enemies, weapons)
	class GameEntity
	{
	public:
		virtual ~GameEntity( ){ }

		void ID( const ZED_UINT32 p_ID ){ m_ID = p_ID; }

	private:
		ZED_UINT32	m_ID;
		ZED::Arithmetic::Vector3	m_Position;
	};
}

#endif

