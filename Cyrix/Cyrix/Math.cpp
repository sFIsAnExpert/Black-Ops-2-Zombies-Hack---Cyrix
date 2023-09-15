#include "Math.h"

Vector3 WorldToScreen(Vector3 pos, ViewMatrix vm, int screenX, int screenY) {
	Vector4 clipCoords; Vector3 screen;
	clipCoords.x = pos.x * vm.matrix[0] + pos.y * vm.matrix[4] + pos.z * vm.matrix[8] + vm.matrix[12];
	clipCoords.y = pos.x * vm.matrix[1] + pos.y * vm.matrix[5] + pos.z * vm.matrix[9] + vm.matrix[13];
	clipCoords.z = pos.x * vm.matrix[2] + pos.y * vm.matrix[6] + pos.z * vm.matrix[10] + vm.matrix[14];
	clipCoords.w = pos.x * vm.matrix[3] + pos.y * vm.matrix[7] + pos.z * vm.matrix[11] + vm.matrix[15];

	Vector3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (screenX / 2 * NDC.x) + (NDC.x + screenX / 2);
	screen.y = -(screenY / 2 * NDC.y) + (NDC.y + screenY / 2);
	screen.z = NDC.z;
	return screen;
}

float Dist3D(Vector3 from, Vector3 to) {
	float val = ((to.x - from.x) * (to.x - from.x)) + ((to.y - from.y) * (to.y - from.y)) + ((to.z - from.z) * (to.z - from.z));

	return (sqrt(val) / 31);
}

void AimAtPos(float x, float y, int Width, int Height, int smooth)
{
    float ScreenCenterX = (Width / 2);
    float ScreenCenterY = (Height / 2);
    float TargetX = 0;
    float TargetY = 0;
    if (x != 0)
    {
        if (x > ScreenCenterX)
        {
            TargetX = -(ScreenCenterX - x);
            TargetX /= smooth;
            if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
        }

        if (x < ScreenCenterX)
        {
            TargetX = x - ScreenCenterX;
            TargetX /= smooth;
            if (TargetX + ScreenCenterX < 0) TargetX = 0;
        }
    }
    if (y != 0)
    {
        if (y > ScreenCenterY)
        {
            TargetY = -(ScreenCenterY - y);
            TargetY /= smooth;
            if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
        }

        if (y < ScreenCenterY)
        {
            TargetY = y - ScreenCenterY;
            TargetY /= smooth;
            if (TargetY + ScreenCenterY < 0) TargetY = 0;
        }
    }

    TargetX /= 10;
    TargetY /= 10;
    if (abs(TargetX) < 1)
    {
        if (TargetX > 0)
        {
            TargetX = 1;
        }
        if (TargetX < 0)
        {
            TargetX = -1;
        }
    }
    if (abs(TargetY) < 1)
    {
        if (TargetY > 0)
        {
            TargetY = 1;
        }
        if (TargetY < 0)
        {
            TargetY = -1;
        }
    }
    mouse_event(MOUSEEVENTF_MOVE, (DWORD)TargetX, (DWORD)TargetY, 0, 0);
}

