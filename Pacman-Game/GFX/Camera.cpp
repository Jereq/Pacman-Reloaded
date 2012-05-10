#include "Camera.h"

const D3DXVECTOR3 Camera::dV(0, 0, 1);
const D3DXVECTOR3 Camera::dU(0, 1, 0);

Camera::Camera():	eye( D3DXVECTOR3(0,0,0) ),
					target( D3DXVECTOR3(0,0,1) ),
					up( D3DXVECTOR3(0,1,0) ),
					forward( D3DXVECTOR3(0,0,1) ),
					heading(0),
					pitch(0)
{	
	//set matrices to identity
	D3DXMatrixIdentity( &viewMatrix );
	D3DXMatrixIdentity( &projectionMatrix );
}

Camera::~Camera()
{
}

/*******************************************************************
* create perspective projection
********************************************************************/
void Camera::setPerspectiveProjectionLH(float FOV, float aspectRatio, float zNear, float zFar)
{
	//convert FOV from degrees to radians
	FOV *= (float)DEG_TO_RAD;

	D3DXMatrixPerspectiveFovLH( &projectionMatrix, FOV, aspectRatio, zNear, zFar );
}

/*******************************************************************
* update view from Camera heading and pitch
********************************************************************/
void Camera::updateView()
{	
	//create rotation matrix
	D3DXMatrixRotationYawPitchRoll( &rotationMatrix, heading, pitch, 0 );

	//create new forward and up vectors
	D3DXVec3TransformCoord( &forward, &dV, &rotationMatrix );
	D3DXVec3TransformCoord( &up, &dU, &rotationMatrix );

	//take into account eye position
	target = eye + forward;
	
	//update view matrix
	D3DXMatrixLookAtLH( &viewMatrix, &eye, &target, &up );
}

/*******************************************************************
* position Camera
********************************************************************/
void Camera::setPositionAndView(float x, float y, float z, float hDeg, float pDeg)
{
	//set eye coordinates
	eye.x = x;
	eye.y = y;
	eye.z = z;

	//set heading and pitch
	adjustHeadingPitch( hDeg * (float) DEG_TO_RAD, pDeg * (float) DEG_TO_RAD );
	
	//update view 
	updateView();
}

/*******************************************************************
* adjust heading and pitch
********************************************************************/
void Camera::adjustHeadingPitch( float hRad, float pRad )
{
	heading = hRad;
	pitch = pRad;

	//value looping - keep heading and pitch between 0 and 2 pi
	while (heading >= TWO_PI) heading -= (float) TWO_PI;
	while (heading < 0) heading += (float) TWO_PI;

	while (pitch >= TWO_PI) pitch -= (float) TWO_PI;
	while (pitch < 0) pitch += (float) TWO_PI;
}

/*******************************************************************
* update Camera
********************************************************************/
void Camera::update()
{
	//update view
	updateView();
}