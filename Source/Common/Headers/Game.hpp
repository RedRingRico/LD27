#ifndef __LD27_GAME_HPP__
#define __LD27_GAME_HPP__

#include <System/DataTypes.hpp>

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
	};
}

#endif

