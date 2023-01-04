////////////////////////////////////////////////////////////////////////////////
//
// File: virtualLego.cpp
//
// Original Author: 박창현 Chang-hyeon Park, 
// Modified by Bong-Soo Sohn and Dong-Jun Kim
// 
// Originally programmed for Virtual LEGO. 
// Modified later to program for Virtual Billiard.
//        
////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include"CSphere.h"
#include"CWall.h"
#include"CLight.h"

IDirect3DDevice9* Device = NULL;

// window size
const int Width = 1024;
const int Height = 768;

const int count = 22; // number of balls
float spherePos[count][2];//array that store the position of each ball
D3DXCOLOR sphereColor[count];// array that store the color of each ball

// -----------------------------------------------------------------------------
// Transform matrices
// -----------------------------------------------------------------------------
D3DXMATRIX g_mWorld;
D3DXMATRIX g_mView;
D3DXMATRIX g_mProj;

#define M_RADIUS 0.21   // ball radius
#define PI 3.14159265
#define M_HEIGHT 0.01

int select_map = 1;
bool game_start = false;

// -----------------------------------------------------------------------------
// Global variables
// -----------------------------------------------------------------------------
CWall	g_legoPlane;
CWall	g_legowall[4];
CSphere	g_sphere[count];
CSphere	g_target_whiteball;
CSphere red_ball;
CLight	g_light;
double g_camera_pos[3] = { 0.0, 5.0, -8.0 };

// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------


void destroyAllLegoBlock(void)
{
}

// initialization
bool Setup()
{
	int i;

	if (select_map == 1) {	//ball position ( SW )
		spherePos[0][0] = -2.3; spherePos[0][1] = -1;
		spherePos[1][0] = -1.7; spherePos[1][1] = -1;
		spherePos[2][0] = -1.1; spherePos[2][1] = -1;
		spherePos[3][0] = -1.1; spherePos[3][1] = 0;
		spherePos[4][0] = -1.1; spherePos[4][1] = 1;
		spherePos[5][0] = -1.7; spherePos[5][1] = 1;
		spherePos[6][0] = -2.3; spherePos[6][1] = 1;
		spherePos[7][0] = -2.3; spherePos[7][1] = 2;
		spherePos[8][0] = -2.3; spherePos[8][1] = 3;
		spherePos[9][0] = -1.7; spherePos[9][1] = 3;
		spherePos[10][0] = -1.1; spherePos[10][1] = 3;
		spherePos[11][0] = 0.1; spherePos[11][1] = 3;
		spherePos[12][0] = 0.1; spherePos[12][1] = 2;
		spherePos[13][0] = 0.1; spherePos[13][1] = 1;
		spherePos[14][0] = 0.1; spherePos[14][1] = 0;
		spherePos[15][0] = 0.7; spherePos[15][1] = -1;
		spherePos[16][0] = 1.3; spherePos[16][1] = 0;
		spherePos[17][0] = 1.9; spherePos[17][1] = -1;
		spherePos[18][0] = 2.5; spherePos[18][1] = 0;
		spherePos[19][0] = 2.5; spherePos[19][1] = 1;
		spherePos[20][0] = 2.5; spherePos[20][1] = 2;
		spherePos[21][0] = 2.5; spherePos[21][1] = 3;
	}
	else if (select_map == 2) {	//ball position ( cau )
		spherePos[0][0] = -1.1; spherePos[0][1] = 3;
		spherePos[1][0] = -1.7; spherePos[1][1] = 3;
		spherePos[2][0] = -2.3; spherePos[2][1] = 2;
		spherePos[3][0] = -2.3; spherePos[3][1] = 1;
		spherePos[4][0] = -1.7; spherePos[4][1] = 0;
		spherePos[5][0] = -1.1; spherePos[5][1] = 0;
		spherePos[6][0] = 0.1; spherePos[6][1] = 3;
		spherePos[7][0] = 0.7; spherePos[7][1] = 3;
		spherePos[8][0] = 0.7; spherePos[8][1] = 2;
		spherePos[9][0] = 0.7; spherePos[9][1] = 1;
		spherePos[10][0] = 0.1; spherePos[10][1] = 1;
		spherePos[11][0] = -0.5; spherePos[11][1] = 1;
		spherePos[12][0] = -0.5; spherePos[12][1] = 0;
		spherePos[13][0] = 0.1, spherePos[13][1] = 0;
		spherePos[14][0] = 0.7; spherePos[14][1] = 0;
		spherePos[15][0] = 1.3; spherePos[15][1] = 3;
		spherePos[16][0] = 1.3; spherePos[16][1] = 2;
		spherePos[17][0] = 1.3; spherePos[17][1] = 1;
		spherePos[18][0] = 1.9; spherePos[18][1] = 0;
		spherePos[19][0] = 2.5; spherePos[19][1] = 1;
		spherePos[20][0] = 2.5; spherePos[20][1] = 2;
		spherePos[21][0] = 2.5; spherePos[21][1] = 3;
	}
	else if (select_map == 3) {	//ball position ( khy )
		spherePos[0][0] = -2.3; spherePos[0][1] = -1;
		spherePos[1][0] = -2.3; spherePos[1][1] = 0;
		spherePos[2][0] = -2.3; spherePos[2][1] = 1;
		spherePos[3][0] = -2.3; spherePos[3][1] = 2;
		spherePos[4][0] = -2.3; spherePos[4][1] = 3;
		spherePos[5][0] = -1.7; spherePos[5][1] = 1;
		spherePos[6][0] = -1.1; spherePos[6][1] = 2;
		spherePos[7][0] = -0.5; spherePos[7][1] = 2;
		spherePos[8][0] = -0.5; spherePos[8][1] = 1;
		spherePos[9][0] = -1.1; spherePos[9][1] = 0;
		spherePos[10][0] = -0.5; spherePos[10][1] = 0;
		spherePos[11][0] = -0.5; spherePos[11][1] = 1;
		spherePos[12][0] = 0.1; spherePos[12][1] = 1;
		spherePos[13][0] = 0.7, spherePos[13][1] = 2;
		spherePos[14][0] = 1.3; spherePos[14][1] = 2;
		spherePos[15][0] = 0.7; spherePos[15][1] = 1;
		spherePos[16][0] = 0.7; spherePos[16][1] = 0;
		spherePos[17][0] = 2.0; spherePos[17][1] = 1;
		spherePos[18][0] = 2.0; spherePos[18][1] = 0;
		spherePos[19][0] = 2.6; spherePos[19][1] = 2;
		spherePos[20][0] = 2.6; spherePos[20][1] = 3;
		spherePos[21][0] = -0.5; spherePos[21][1] = -1;
	}
	else if (select_map == 4) {	//ball position ( jjy )
		spherePos[0][0] = -2.3; spherePos[0][1] = 0;
		spherePos[1][0] = -2.3; spherePos[1][1] = -1;
		spherePos[2][0] = -1.7; spherePos[2][1] = -1;
		spherePos[3][0] = -1.1; spherePos[3][1] = -1;
		spherePos[4][0] = -1.1; spherePos[4][1] = 0;
		spherePos[5][0] = -1.1; spherePos[5][1] = 1;
		spherePos[6][0] = -1.1; spherePos[6][1] = 2;
		spherePos[7][0] = -1.1; spherePos[7][1] = 3;
		spherePos[8][0] = -0.5; spherePos[8][1] = 0;
		spherePos[9][0] = -0.5; spherePos[9][1] = -1;
		spherePos[10][0] = 0.1; spherePos[10][1] = -1;
		spherePos[11][0] = 0.7; spherePos[11][1] = -1;
		spherePos[12][0] = 0.7; spherePos[12][1] = 0;
		spherePos[13][0] = 0.7, spherePos[13][1] = 1;
		spherePos[14][0] = 0.7; spherePos[14][1] = 2;
		spherePos[15][0] = 0.7; spherePos[15][1] = 3;
		spherePos[16][0] = 1.3; spherePos[16][1] = 3;
		spherePos[17][0] = 2.5; spherePos[17][1] = 3;
		spherePos[18][0] = 1.9; spherePos[18][1] = 2;
		spherePos[19][0] = 1.9; spherePos[19][1] = 1;
		spherePos[20][0] = 1.9; spherePos[20][1] = 0;
		spherePos[21][0] = 1.9; spherePos[21][1] = -1;
	}
	else if (select_map == 5) {	//ball position ( syw )
		spherePos[0][0] = -2.3; spherePos[0][1] = -1;
		spherePos[1][0] = -1.7; spherePos[1][1] = -1;
		spherePos[2][0] = -1.1; spherePos[2][1] = 0;
		spherePos[3][0] = -1.1; spherePos[3][1] = 1;
		spherePos[4][0] = -1.7; spherePos[4][1] = 1;
		spherePos[5][0] = -2.3; spherePos[5][1] = 1;
		spherePos[6][0] = -2.3; spherePos[6][1] = 2;
		spherePos[7][0] = -1.7; spherePos[7][1] = 3;
		spherePos[8][0] = -1.1; spherePos[8][1] = 3;
		spherePos[9][0] = -0.5; spherePos[9][1] = 2;
		spherePos[10][0] = 0.1; spherePos[10][1] = 1;
		spherePos[11][0] = 0.1; spherePos[11][1] = 0;
		spherePos[12][0] = 0.7; spherePos[12][1] = 2;
		spherePos[13][0] = 1.3, spherePos[13][1] = 2;
		spherePos[14][0] = 1.3; spherePos[14][1] = 1;
		spherePos[15][0] = 1.3; spherePos[15][1] = 0;
		spherePos[16][0] = 1.3; spherePos[16][1] = -1;
		spherePos[17][0] = 1.9; spherePos[17][1] = 0;
		spherePos[18][0] = 2.5; spherePos[18][1] = -1;
		spherePos[19][0] = 2.5; spherePos[19][1] = 0;
		spherePos[20][0] = 2.5; spherePos[20][1] = 1;
		spherePos[21][0] = 2.5; spherePos[21][1] = 2;
	}
	else if (select_map == 6) {	//ball position ( jhs )
		spherePos[0][0] = -2.3; spherePos[0][1] = 0;
		spherePos[1][0] = -2.3; spherePos[1][1] = -1;
		spherePos[2][0] = -1.7; spherePos[2][1] = -1;
		spherePos[3][0] = -1.1; spherePos[3][1] = -1;
		spherePos[4][0] = -1.1; spherePos[4][1] = 0;
		spherePos[5][0] = -1.1; spherePos[5][1] = 1;
		spherePos[6][0] = -1.1; spherePos[6][1] = 2;
		spherePos[7][0] = -0.5; spherePos[7][1] = 2;
		spherePos[8][0] = -0.5; spherePos[8][1] = 1;
		spherePos[9][0] = -0.5; spherePos[9][1] = 0;
		spherePos[10][0] = 0.1; spherePos[10][1] = 1;
		spherePos[11][0] = 0.7; spherePos[11][1] = 2;
		spherePos[12][0] = 0.7; spherePos[12][1] = 1;
		spherePos[13][0] = 0.7, spherePos[13][1] = 0;
		spherePos[14][0] = 1.3; spherePos[14][1] = 2;
		spherePos[15][0] = 1.9; spherePos[15][1] = 3;
		spherePos[16][0] = 2.5; spherePos[16][1] = 3;
		spherePos[17][0] = 1.9; spherePos[17][1] = 1;
		spherePos[18][0] = 2.5; spherePos[18][1] = 1;
		spherePos[19][0] = 2.5; spherePos[19][1] = 0;
		spherePos[20][0] = 1.3; spherePos[20][1] = -1;
		spherePos[21][0] = 1.9; spherePos[21][1] = -1;
	}

	D3DXMatrixIdentity(&g_mWorld);
	D3DXMatrixIdentity(&g_mView);
	D3DXMatrixIdentity(&g_mProj);

	// create plane and set the position
	if (false == g_legoPlane.create(Device, -1, -1, 6, 0.03f, 9, d3d::GREEN)) return false;
	g_legoPlane.setPosition(0.0f, -0.0006f / 5, 0.0f);

	// create walls and set the position. note that there are four walls
	if (false == g_legowall[0].create(Device, -1, -1, 0.12f, 0.3f, 9, d3d::BLUE)) return false;
	g_legowall[0].setPosition(3.06f, 0.12f, 0.0f);
	if (false == g_legowall[1].create(Device, -1, -1, 0.12f, 0.3f, 9, d3d::BLUE)) return false;
	g_legowall[1].setPosition(-3.06f, 0.12f, 0.0f);
	if (false == g_legowall[2].create(Device, -1, -1, 6.24f, 0.3f, 0.12f, d3d::BLUE)) return false;
	g_legowall[2].setPosition(0.0f, 0.12f, 4.56f);
	if (false == g_legowall[3].create(Device, -1, -1, 6.24f, 0.3f, 0.12f, d3d::RED)) return false;
	g_legowall[3].setPosition(0.0f, 0.12f, -3.56f);

	// initialize the color of each ball
	for (int i = 0; i < count; i++) {
		sphereColor[i] = d3d::YELLOW;
	}
	// create balls and set the position
	for (i = 0; i < count; i++) {
		if (false == g_sphere[i].create(Device, sphereColor[i])) return false;
		g_sphere[i].setCenter(spherePos[i][0], (float)M_RADIUS, spherePos[i][1]);
		g_sphere[i].setPower(0, 0);
	}

	// create white ball for set direction
	if (false == g_target_whiteball.create(Device, d3d::WHITE)) return false;
	g_target_whiteball.setCenter(.0f, (float)M_RADIUS, -3.56f);

	// create red ball
	if (false == red_ball.create(Device, d3d::RED)) return false;
	red_ball.setCenter(.0f, (float)M_RADIUS, -2.56f);

	// light setting 
	D3DLIGHT9 lit;
	::ZeroMemory(&lit, sizeof(lit));
	lit.Type = D3DLIGHT_POINT;
	lit.Diffuse = d3d::WHITE;
	lit.Specular = d3d::WHITE * 0.9f;
	lit.Ambient = d3d::WHITE * 0.9f;
	lit.Position = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	lit.Range = 100.0f;
	lit.Attenuation0 = 0.0f;
	lit.Attenuation1 = 0.9f;
	lit.Attenuation2 = 0.0f;
	if (false == g_light.create(Device, lit))
		return false;

	// Position and aim the camera.
	D3DXVECTOR3 pos(0.0f, 5.0f, -8.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 2.0f, 0.0f);
	D3DXMatrixLookAtLH(&g_mView, &pos, &target, &up);
	Device->SetTransform(D3DTS_VIEW, &g_mView);

	// Set the projection matrix.
	D3DXMatrixPerspectiveFovLH(&g_mProj, D3DX_PI / 4,
		(float)Width / (float)Height, 1.0f, 100.0f);
	Device->SetTransform(D3DTS_PROJECTION, &g_mProj);

	// Set render states.
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);
	Device->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	Device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	g_light.setLight(Device, g_mWorld);
	return true;
}

void Cleanup(void)
{
	g_legoPlane.destroy();
	for (int i = 0; i < 4; i++) {
		g_legowall[i].destroy();
	}
	destroyAllLegoBlock();
	g_light.destroy();
}


// timeDelta represents the time between the current image frame and the last image frame.
// the distance of moving balls should be "velocity * timeDelta"
bool Display(float timeDelta)
{
	int i = 0;
	int j = 0;

	if (Device)
	{
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00afafaf, 1.0f, 0);
		Device->BeginScene();

		// update the position of red and white ball. during update, check whether each ball hit by walls.
		for (i = 0; i < 4; i++) {
			g_target_whiteball.ballUpdate(timeDelta);
			red_ball.ballUpdate(timeDelta);
			g_legowall[count % 4].hitBy(red_ball);
		}

		// check whether any two balls hit together and update the direction of balls
		// if there's a collision, delete the yellow ball which bumped with white ball
		for (i = 0; i < count; i++) {
			if (g_sphere[i].getexist() == true) {
				if (g_sphere[i].hitBy(red_ball)) {
					g_sphere[i].setexist(false);
				}
			}
		}

		//check if a white ball collides with blue ball
		g_target_whiteball.hitBy(red_ball);

		// draw plane, walls, and spheres
		g_legoPlane.draw(Device, g_mWorld);
		for (int i = 0; i < 4; i++) {
			g_legowall[i].draw(Device, g_mWorld);
		}
		for (i = 0; i < count; i++) {
			if (g_sphere[i].getexist() == true) // draw only if the ball exists
				g_sphere[i].draw(Device, g_mWorld);
		}
		g_target_whiteball.draw(Device, g_mWorld);
		red_ball.draw(Device, g_mWorld);
		g_light.draw(Device);

		Device->EndScene();
		Device->Present(0, 0, 0, 0);
		Device->SetTexture(0, NULL);

	}
	return true;
}

LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static bool wire = false;
	static bool isReset = true;
	static int old_x = 0;
	static int old_y = 0;
	static enum { WORLD_MOVE, LIGHT_MOVE, BLOCK_MOVE } move = WORLD_MOVE;

	switch (msg) {
	case WM_DESTROY:
	{
		::PostQuitMessage(0);
		break;
	}
	case WM_KEYDOWN:
	{
		switch (wParam) {
		case VK_ESCAPE:
			::DestroyWindow(hwnd);
			break;
		case VK_RETURN:
			if (NULL != Device) {
				wire = !wire;
				Device->SetRenderState(D3DRS_FILLMODE,
					(wire ? D3DFILL_WIREFRAME : D3DFILL_SOLID));
			}
			break;
		case VK_F1:
			if (game_start == false) {
				select_map = 1;
				Cleanup();
				Setup();
				Display;
			}
			break;
		case VK_F2:
			if (game_start == false) {
				select_map = 2;
				Cleanup();
				Setup();
				Display;
			}
			break;
		case VK_F3:
			if (game_start == false) {
				select_map = 3;
				Cleanup();
				Setup();
				Display;
			}
			break;
		case VK_F4:
			if (game_start == false) {
				select_map = 4;
				Cleanup();
				Setup();
				Display;
			}
			break;
		case VK_F5:
			if (game_start == false) {
				select_map = 5;
				Cleanup();
				Setup();
				Display;
			}
			break;
		case VK_F6:
			if (game_start == false) {
				select_map = 6;
				Cleanup();
				Setup();
				Display;
			}
			break;
		case VK_LEFT: {
			D3DXVECTOR3 targetpos = g_target_whiteball.getCenter();
			g_target_whiteball.setCenter(targetpos.x - 0.3f, targetpos.y, targetpos.z);
		}break;// left-key pressed -> blue ball moves to the left

		case VK_RIGHT: {
			D3DXVECTOR3 targetpos = g_target_whiteball.getCenter();
			g_target_whiteball.setCenter(targetpos.x + 0.3f, targetpos.y, targetpos.z);
		}break;// right-key pressed- > blue ball moves to the right

		case VK_SPACE:
			game_start = true;
			D3DXVECTOR3 targetpos = g_target_whiteball.getCenter();
			D3DXVECTOR3	whitepos = red_ball.getCenter();

			if (whitepos.z == g_target_whiteball.getCenter().z + 1) {
				double theta = acos(sqrt(pow(targetpos.x - whitepos.x, 2)) / sqrt(pow(targetpos.x - whitepos.x, 2) +
					pow(targetpos.z - whitepos.z, 2)));		// 기본 1 사분면
				//target과 whitepos를 잇는 선과 x축 과의 각을 theta로 정한다.
				if (targetpos.z - whitepos.z <= 0 && targetpos.x - whitepos.x >= 0) { theta = -theta; }	//4 사분면
				if (targetpos.z - whitepos.z >= 0 && targetpos.x - whitepos.x <= 0) { theta = PI - theta; } //2 사분면
				if (targetpos.z - whitepos.z <= 0 && targetpos.x - whitepos.x <= 0) { theta = PI + theta; } // 3 사분면
				red_ball.setPower(cos(theta) / 1.5, sin(theta) / 1.5);
			}break;

		}
		break;
	}

	case WM_MOUSEMOVE:
	{
		int new_x = LOWORD(lParam);
		float dx;
		float dy;

		isReset = true;

		if (LOWORD(wParam) & MK_RBUTTON) {
			dx = (old_x - new_x);// * 0.01f;
			dy = (old_y);// * 0.01f;

			D3DXVECTOR3 coord3d = g_target_whiteball.getCenter();
			g_target_whiteball.setCenter(coord3d.x + dx * (-0.007f), coord3d.y, coord3d.z + dy * 0.007f);
		}
		old_x = new_x;

		move = WORLD_MOVE;

		break;
	}// using right_mouse_button, you can move the blue ball
	}

	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(
	_In_ HINSTANCE hinstance,
	_In_opt_ HINSTANCE prevInstance,
	_In_ PSTR cmdLine,
	_In_ int showCmd)
{
	srand(static_cast<unsigned int>(time(NULL)));

	if (!d3d::InitD3D(hinstance,
		Width, Height, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}

	if (!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}

	d3d::EnterMsgLoop(Display);

	Cleanup();

	Device->Release();

	return 0;
}