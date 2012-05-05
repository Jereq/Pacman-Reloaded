#pragma once

#include <d3dx10.h>

const double TWO_PI = D3DX_PI * 2;
const double DEG_TO_RAD = D3DX_PI / 180;

class Camera
{	
	/*******************************************************************
	* Members
	********************************************************************/	
private:
		
	//view parameters
	float heading, pitch;					//in radians

	//matrices
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projectionMatrix;	
	D3DXMATRIX rotationMatrix;				//Rotation matrix
		
	//view vectors
	const static D3DXVECTOR3 dV, dU;		//default view and up vectors
	D3DXVECTOR3 eye, target, up;

	//movement vectors and movement toggles
	D3DXVECTOR3 forward;
		
	/*******************************************************************
	* Methods
	********************************************************************/	
public:

	//constructor and destructor
	Camera();
	virtual ~Camera();

	//set projection methods
	void setPerspectiveProjectionLH( float FOV, float aspectRatio, float zNear, float zFar );
			
	//camera positioning methods
	void setPositionAndView( float x, float y, float z, float hDeg, float pDeg );
	void adjustHeadingPitch( float hRad, float pRad );

	//update camera view/position
	void update();	

	//get methods	
	D3DXMATRIX&		getViewMatrix(){ return viewMatrix; }
	D3DXMATRIX&		getProjectionMatrix(){ return projectionMatrix; }
	D3DXVECTOR3&	getCameraPosition(){ return eye; }
	D3DXVECTOR3&	getCameraTarget(){ return target; }
	D3DXVECTOR3&	getCameraForward(){ return forward; }
	D3DXVECTOR3&	getCameraUp(){ return up; }

private:

	//create view, forward, strafe vectors from heading/pitch
	void updateView();
};