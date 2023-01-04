#include "d3dUtility.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include"CSphere.h"
#include"CWall.h"


CWall::CWall(void)
{
	D3DXMatrixIdentity(&m_mLocal);
	ZeroMemory(&m_mtrl, sizeof(m_mtrl));
	m_width = 0;
	m_depth = 0;
	m_pBoundMesh = NULL;
}
CWall::~CWall(void) {}

bool CWall::create(IDirect3DDevice9* pDevice, float ix, float iz, float iwidth, float iheight, float idepth, D3DXCOLOR color = d3d::WHITE)
{
	if (NULL == pDevice)
		return false;

	m_mtrl.Ambient = color;
	m_mtrl.Diffuse = color;
	m_mtrl.Specular = color;
	m_mtrl.Emissive = d3d::BLACK;
	m_mtrl.Power = 5.0f;

	m_width = iwidth;
	m_depth = idepth;

	if (FAILED(D3DXCreateBox(pDevice, iwidth, iheight, idepth, &m_pBoundMesh, NULL)))
		return false;
	return true;
}

void CWall::destroy(void)
{
	if (m_pBoundMesh != NULL) {
		m_pBoundMesh->Release();
		m_pBoundMesh = NULL;
	}
}

void CWall::draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld)
{
	if (NULL == pDevice)
		return;
	pDevice->SetTransform(D3DTS_WORLD, &mWorld);
	pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
	pDevice->SetMaterial(&m_mtrl);
	m_pBoundMesh->DrawSubset(0);
}

bool CWall::hasIntersected(CSphere& ball)
{
	D3DXVECTOR3 center = ball.getCenter();
	// If red ball position goes out of range -> true
	if (center.x >= 3.0f - ball.getRadius() || center.x <= -3.0f + ball.getRadius() || center.z >= 4.50f - ball.getRadius() || center.z <= -4.50f + ball.getRadius()) {
		return true;
	}
	return false;
}

void CWall::hitBy(CSphere& ball)
{
	if (this->hasIntersected(ball) == false) {
		return;
	}

	//If ball is crash with corner->xand z velocity is reversed
	if (ball.getCenter().x >= 3.00f - ball.getRadius() && ball.getCenter().z >= 4.50f - ball.getRadius())
		ball.setPower(-ball.getVelocity_X(), -ball.getVelocity_Z());
	else if (ball.getCenter().x <= -3.00f + ball.getRadius() && ball.getCenter().z >= 4.50f - ball.getRadius())
		ball.setPower(-ball.getVelocity_X(), -ball.getVelocity_Z());
	//else if ball is crash with right / left wall->x velocity is reversed
	else if (ball.getCenter().x >= 3.00f - ball.getRadius())
		ball.setPower(-ball.getVelocity_X(), ball.getVelocity_Z());
	else if (ball.getCenter().x <= -3.00f + ball.getRadius())
		ball.setPower(-ball.getVelocity_X(), ball.getVelocity_Z());
	//else if ball is crash with top wall->z velocity is reversed
	else if (ball.getCenter().z >= 4.50f - ball.getRadius())
		ball.setPower(ball.getVelocity_X(), -ball.getVelocity_Z());
	else if (ball.getCenter().z <= -4.50f + ball.getRadius()) {
		ball.setPower(0, 0);
		ball.setCenter(0.0f, ball.getCenter().y, -2.56);
	}
}

void CWall::setPosition(float x, float y, float z)
{
	D3DXMATRIX m;
	this->m_x = x;
	this->m_z = z;

	D3DXMatrixTranslation(&m, x, y, z);
	setLocalTransform(m);
}

float CWall::getHeight(void) const { return M_HEIGHT; }
void CWall::setLocalTransform(const D3DXMATRIX& mLocal) { m_mLocal = mLocal; }
