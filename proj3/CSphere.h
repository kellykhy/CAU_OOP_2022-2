#pragma once
// -----------------------------------------------------------------------------
// CSphere class definition
// -----------------------------------------------------------------------------
#include "d3dUtility.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>

#define M_RADIUS 0.21   // ball radius
#define PI 3.14159265
#define M_HEIGHT 0.01
#define DECREASE_RATE 0.9999

class CSphere {
private:
	float					center_x, center_y, center_z;
	float                   m_radius;
	float					m_velocity_x;
	float					m_velocity_z;
	bool					exist;   //the ball is exist or not

	D3DXMATRIX              m_mLocal;
	D3DMATERIAL9            m_mtrl;
	ID3DXMesh* m_pSphereMesh;
public:
	CSphere(void);
	~CSphere(void);

	bool getexist();
	void setexist(bool);
	bool create(IDirect3DDevice9* pDevice, D3DXCOLOR color);
	void destroy(void);
	void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld);
	bool hasIntersected(CSphere& ball);

	bool hitBy(CSphere& ball);
	void ballUpdate(float timeDiff);

	double getVelocity_X();
	double getVelocity_Z();
	void setPower(double vx, double vz);
	void setCenter(float x, float y, float z);
	float getRadius(void)  const;
	const D3DXMATRIX& getLocalTransform(void) const;
	void setLocalTransform(const D3DXMATRIX& mLocal);
	D3DXVECTOR3 getCenter(void) const;
};
