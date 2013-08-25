#include <Player.hpp>
#include <System/Memory.hpp>
#include <Renderer/OGL/GLModel.hpp>
#include <Renderer/OGL/GLShader.hpp>
#include <System/File.hpp>
#include <Arithmetic/Matrix4x4.hpp>
#include <cstring>

namespace LD27
{
	Player::Player( )
	{
		m_pRenderer = ZED_NULL;
		m_pModel = ZED_NULL;
		m_pShader = ZED_NULL;
	}

	Player::~Player( )
	{
		zedSafeDelete( m_pShader );
		zedSafeDelete( m_pModel );
	}

	ZED_UINT32 Player::Initialise( const ZED::Renderer::Renderer *p_pRenderer )
	{
		m_pRenderer = const_cast< ZED::Renderer::Renderer * >( p_pRenderer );

		if( m_pRenderer == ZED_NULL )
		{
			return ZED_FAIL;
		}

		switch( m_pRenderer->BackEnd( ) )
		{
			case ZED_RENDERER_BACKEND_OPENGL:
			{
				m_pModel = new ZED::Renderer::GLModel( m_pRenderer );
				m_pShader = new ZED::Renderer::GLShader( );

				break;
			}
			default:
			{
				zedTrace( "[LD27::Player::Initialise] <ERROR> "
					"Unknown renderer backend\n" );
				return ZED_FAIL;
			}
		}

		if( m_pModel == ZED_NULL )
		{
			zedTrace( "[LD27::Player::Initialise] <ERROR> "
				"Failed to initialise the model\n" );

			return ZED_FAIL;
		}
		if( m_pShader == ZED_NULL )
		{
			zedTrace( "[LD27::Player::Initialise] <ERROR> "
				"Failed to initialise the shader\n" );

			return ZED_FAIL;
		}

		ZED_CHAR8 *pBinDir = new ZED_CHAR8[ 256 ];
		ZED_CHAR8 *pModelPath = new ZED_CHAR8[ 256 ];
		ZED_CHAR8 *pFragmentShader = new ZED_CHAR8[ 256 ];
		ZED_CHAR8 *pVertexShader = new ZED_CHAR8[ 256 ];

		ZED::System::GetExecutablePath( &pBinDir, 256 );

		memset( pVertexShader, '\0', 256 );
		memset( pFragmentShader, '\0', 256 );
		memset( pModelPath, '\0', 256 );
		
		strcat( pVertexShader, pBinDir );
		strcat( pFragmentShader, pBinDir );
		strcat( pModelPath, pBinDir );

		strcat( pVertexShader, "Game Media/Shaders/Player.vsh" );
		strcat( pFragmentShader, "Game Media/Shaders/Player.fsh" );
		strcat( pModelPath, "Game Media/Models/Player.zed" );

		zedSafeDeleteArray( pBinDir );

		if( m_pShader->Compile(
			const_cast< const ZED_CHAR8 ** >( &pVertexShader ),
			ZED_VERTEX_SHADER, ZED_TRUE ) != ZED_OK )
		{
			zedSafeDeleteArray( pVertexShader );
			zedSafeDeleteArray( pFragmentShader );
			zedSafeDeleteArray( pModelPath );

			return ZED_FAIL;
		}

		zedSafeDeleteArray( pVertexShader );

		if( m_pShader->Compile(
			const_cast< const ZED_CHAR8 ** >( &pFragmentShader ),
			ZED_FRAGMENT_SHADER, ZED_TRUE ) != ZED_OK )
		{
			zedSafeDeleteArray( pFragmentShader );
			zedSafeDeleteArray( pModelPath );

			return ZED_FAIL;
		}

		zedSafeDeleteArray( pFragmentShader );

		if( m_pModel->Load( pModelPath ) != ZED_OK )
		{
			zedTrace( "[LD27::Player::Initialise] <ERROR> "
				"Failed to load player model\n" );
			
			zedSafeDeleteArray( pModelPath );

			return ZED_FAIL;
		}

		zedSafeDeleteArray( pModelPath );

		ZED_SHADER_VERTEXATTRIBUTE_GL	Attributes[ 2 ];
		ZED_SHADER_CONSTANT_MAP			Constants[ 10 ];

		Attributes[ 0 ].Index = 0;
		Attributes[ 0 ].pName = "vPosition";
		Attributes[ 1 ].Index = 1;
		Attributes[ 1 ].pName = "vNormal";

		m_pShader->SetVertexAttributeTypes( Attributes, 2 );

		zedSetConstant( Constants, 0, ZED_MAT4X4, "uWVP" );
		zedSetConstant( Constants, 1, ZED_FLOAT3, "uGlobalAmbient" );
		zedSetConstant( Constants, 2, ZED_FLOAT3, "uLightColour" );
		zedSetConstant( Constants, 3, ZED_FLOAT3, "uLightPos" );
		zedSetConstant( Constants, 4, ZED_FLOAT3, "uEyePos" );
		zedSetConstant( Constants, 5, ZED_FLOAT3, "uEmissive" );
		zedSetConstant( Constants, 6, ZED_FLOAT3, "uAmbient" );
		zedSetConstant( Constants, 7, ZED_FLOAT3, "uDiffuse" );
		zedSetConstant( Constants, 8, ZED_FLOAT3, "uSpecular" );
		zedSetConstant( Constants, 9, ZED_FLOAT1, "uShininess" );

		m_pShader->SetConstantTypes( Constants, 10 );

		ZED::Arithmetic::Vector3 GlobalAmbient( 0.0001f, 0.0001f, 0.0001f );
		ZED::Arithmetic::Vector3 LightColour( 0.5f, 0.5f, 0.5f );
		ZED::Arithmetic::Vector3 LightPosition( 0.0f, 200.0f, 0.0f );
		ZED::Arithmetic::Vector3 Emissive( 0.0f, 0.0f, 0.0f );
		ZED::Arithmetic::Vector3 Ambient( 0.0f, 0.0f, 0.0f );
		ZED::Arithmetic::Vector3 Diffuse( 0.0f, 1.0f, 0.0f );
		ZED::Arithmetic::Vector3 Specular( 0.0f, 0.0f, 0.0f );
		ZED_FLOAT32 Shininess = 0.0f;

		// Just using a single light for now
		m_pShader->Activate( );
		m_pShader->SetConstantData( 1, ( void * )( &GlobalAmbient ) );
		m_pShader->SetConstantData( 2, ( void * )( &LightColour ) );
		m_pShader->SetConstantData( 3, ( void * )( &LightPosition ) );
		m_pShader->SetConstantData( 5, ( void * )( &Emissive ) );
		m_pShader->SetConstantData( 6, ( void * )( &Ambient ) );
		m_pShader->SetConstantData( 7, ( void * )( &Diffuse ) );
		m_pShader->SetConstantData( 8, ( void * )( &Specular ) );
		m_pShader->SetConstantData( 9, ( void * )( &Shininess ) );

		return ZED_OK;
	}

	void Player::Update( )
	{
	}

	void Player::Render( )
	{
		ZED::Arithmetic::Matrix4x4 WVP;
		ZED::Arithmetic::Matrix4x4 Perspective;
		ZED::Arithmetic::Matrix4x4 World;
		ZED::Arithmetic::Vector3 Origin( 0.0f, 0.0f, 0.0f );
		ZED::Arithmetic::Vector3 CameraPosition( 0.0f, 2000.0f, 300.0f );
		ZED::Arithmetic::Vector3 Up( 0.0f, 1.0f, 0.0f );
		ZED_FLOAT32 Matrix[ 16 ];

		m_pRenderer->SetViewLookAt( CameraPosition, Origin, Up );
		m_pRenderer->PerspectiveProjectionMatrix( &Perspective );
		m_pRenderer->GetWVP( &World );

		WVP = Perspective*World;
		WVP.AsFloat( Matrix );

		m_pShader->Activate( );
		m_pShader->SetConstantData( 4, ( void * )( &CameraPosition ) );
		m_pShader->SetConstantData( 0, Matrix );

		m_pModel->Render( );
	}
}

