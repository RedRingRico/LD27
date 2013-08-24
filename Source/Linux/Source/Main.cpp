#include <Game.hpp>
#include <System/Debugger.hpp>


int main( int p_Argc, char **p_ppArgv )
{
	LD27::Game TheGame;

	if( TheGame.Initialise( ) != ZED_OK )
	{
		zedTrace( "[LD27::main] <ERROR> Failed to initialise the game "
			"instance\n" );
		return ZED_FAIL;
	}

	return TheGame.Execute( );
}

