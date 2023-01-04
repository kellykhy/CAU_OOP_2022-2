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
#include"CSphere.h"

#define M_RADIUS 0.21   // ball radius
#define PI 3.14159265
#define M_HEIGHT 0.01
#define DECREASE_RATE 1

CSphere::CSphere(void)
{
	D3DXMatrixIdentity(&m_mLocal);
	ZeroMemory(&m_mtrl, sizeof(m_mtrl));
	m_radius = 0;
	m_velocity_x = 0;
	m_velocity_z = 0;
	m_pSphereMesh = NULL;
	exist = true;
}
CSphere::~CSphere(void) {}

bool CSphere::getexist()
{
	return this->exist;
}

void CSphere::setexist(bool a)
{
	this->exist = a;
}

bool CSphere::create(IDirect3DDevice9* pDevice, D3DXCOLOR color = d3d::WHITE)
{
	if (NULL == pDevice)
		return false;

	m_mtrl.Ambient = color;
	m_mtrl.Diffuse = color;
	m_mtrl.Specular = color;
	m_mtrl.Emissive = d3d::BLACK;
	m_mtrl.Power = 5.0f;

	if (FAILED(D3DXCreateSphere(pDevice, getRadius(), 50, 50, &m_pSphereMesh, NULL)))
		return false;
	return true;
}

void CSphere::destroy(void)
{
	if (m_pSphereMesh != NULL) {
		m_pSphereMesh->Release();
		m_pSphereMesh = NULL;
	}
}

void CSphere::draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld)
{
	if (NULL == pDevice)
		return;
	pDevice->SetTransform(D3DTS_WORLD, &mWorld);
	pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
	pDevice->SetMaterial(&m_mtrl);
	m_pSphereMesh->DrawSubset(0);
}

bool CSphere::hasIntersected(CSphere& ball)
{
	double distance = sqrt(pow(this->center_x - ball.center_x, 2) + pow(this->center_z - ball.center_z, 2));
	float radious_sum = this->getRadius() + ball.getRadius();

	if (distance <= radious_sum) {
		return true;
	}
	// Insert your code here.
	return false;
}

bool CSphere::hitBy(CSphere& ball)
{
	if (this->hasIntersected(ball) == false) {
		return false;
	}

	// theta1 = angle between vector of center-to-center and x-axis
	double theta1 = acos(sqrt(pow(this->center_x - ball.center_x, 2))
		/ sqrt(pow(this->center_x - ball.center_x, 2) + pow(this->center_z - ball.center_z, 2)));      // 기본 1 사분면
	if (this->center_z - ball.center_z <= 0 && this->center_x - ball.center_x >= 0) { theta1 = -theta1; }   //4 사분면
	if (this->center_z - ball.center_z >= 0 && this->center_x - ball.center_x <= 0) { theta1 = PI - theta1; } //2 사분면
	if (this->center_z - ball.center_z <= 0 && this->center_x - ball.center_x <= 0) { theta1 = PI + theta1; } // 3 사분면

	// theta2 = angle between velocity before collision and x-axis
	double power_s = sqrt(pow(ball.getVelocity_X() - this->getVelocity_X(), 2) + pow(ball.getVelocity_Z() - this->getVelocity_Z(), 2));
	double theta2 = acos(sqrt(pow(ball.getVelocity_X(), 2)) / power_s);
	if (ball.getVelocity_X() <= 0 && ball.getVelocity_Z() >= 0) { theta2 = PI - theta2; }
	if (ball.getVelocity_X() <= 0 && ball.getVelocity_Z() <= 0) { theta2 = PI + theta2; }
	if (ball.getVelocity_X() >= 0 && ball.getVelocity_Z() <= 0) { theta2 = -theta2; }

	// calculate theta between velocity after collision and x-axis
	double theta = PI + 2 * theta1 - theta2;

	ball.setCenter(this->center_x - cos(theta1) * 2 * this->getRadius(), this->getCenter().y, this->center_z - sin(theta1) * 2 * this->getRadius());
	ball.setPower(power_s * cos(theta), power_s * sin(theta));
	return true;
}

void CSphere::ballUpdate(float timeDiff)
{
	const float TIME_SCALE = 3.3;
	D3DXVECTOR3 cord = this->getCenter();
	double vx = abs(this->getVelocity_X());
	double vz = abs(this->getVelocity_Z());

	if (vx > 0.01 || vz > 0.01)
	{
		float tX = cord.x + TIME_SCALE * timeDiff * m_velocity_x;
		float tZ = cord.z + TIME_SCALE * timeDiff * m_velocity_z;

		//correction of position of ball
		// Please uncomment this part because this correction of ball position is necessary when a ball collides with a wall
		if (tX >= (3.0 - M_RADIUS))
			tX = 3.0 - M_RADIUS;
		else if (tX <= (-3.0 + M_RADIUS))
			tX = -3.0 + M_RADIUS;
		else if (tZ <= (-4.5 + M_RADIUS))
			tZ = -4.5 + M_RADIUS;
		else if (tZ >= (4.5 - M_RADIUS))
			tZ = 4.5 - M_RADIUS;

		this->setCenter(tX, cord.y, tZ);
	}

	else { this->setPower(0, 0); }
	//this->setPower(this->getVelocity_X() * DECREASE_RATE, this->getVelocity_Z() * DECREASE_RATE);
	double rate = 1 - (1 - DECREASE_RATE) * timeDiff * 400;
	if (rate < 0)
		rate = 0;
	this->setPower(getVelocity_X() * rate, getVelocity_Z() * rate);
}// 시간에 따른 볼의 움직임 update

double CSphere::getVelocity_X() { return this->m_velocity_x; }
double CSphere::getVelocity_Z() { return this->m_velocity_z; }

void CSphere::setPower(double vx, double vz)
{
	this->m_velocity_x = vx;
	this->m_velocity_z = vz;
}

void CSphere::setCenter(float x, float y, float z)
{
	D3DXMATRIX m;
	center_x = x;	center_y = y;	center_z = z;
	D3DXMatrixTranslation(&m, x, y, z);
	setLocalTransform(m);
}

float CSphere::getRadius(void)  const { return (float)(M_RADIUS); }
const D3DXMATRIX& CSphere::getLocalTransform(void) const { return m_mLocal; }
void CSphere::setLocalTransform(const D3DXMATRIX& mLocal) { m_mLocal = mLocal; }
D3DXVECTOR3 CSphere::getCenter(void) const
{
	D3DXVECTOR3 org(center_x, center_y, center_z);
	return org;
}
