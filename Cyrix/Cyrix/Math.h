#pragma once
#include "includes.h"

#define ANGLE2SHORT(x) ((int)((x)*65536/360) & 65535)
#define M_PI 3.14159265358979323846
#define DegreesToRadians(a) ((a)*((float)M_PI/180.0f))
#define RadiansToDegrees(a) ((a)*(180.0f/(float)M_PI))
#define ShortToAngle(a) ((float)((a)*(360.0f/65536)))

struct Vector2 {
	float x, y;
};

struct vec3_t {
    float x, y, z;
};

struct vec2_t {
    float x, y;
};

struct Angle {
    float yaw, pitch;
};

struct IVec3 {
    int x, y, z;
};

struct Vector3 {
	float x, y, z;
};

struct ViewMatrix {
	float matrix[16];
};

struct Vector4 {
	float x, y, z, w;
};

struct IntVector2 {
	int x, y;
};

typedef class Math {
public:
    void VectorNormalize(Vector3& direction)
    {
        float flLen = VectorLength3D(direction, direction);

        if (flLen == 0.0f)
        {
            direction.x = 0.0f;
            direction.y = 0.0f;
            direction.z = 1.0f;
        }

        else
        {
            flLen = 1.0f / flLen;

            direction.x *= flLen;
            direction.y *= flLen;
            direction.z *= flLen;
        }
    }
    float DotProduct3D(Vector3 left, Vector3 right)
    {
        return (left.x * right.x + left.y * right.y + left.z * right.z);
    }
    /*
    //=====================================================================================
    */
    float DotProduct2D(Vector2 left, Vector2 right)
    {
        return (left.x * right.x + left.y * right.y);
    }
    float VectorLength3D(Vector3 left, Vector3 right)
    {
        return sqrtf(DotProduct3D(left, right));
    }
    char ClampMove(char value)
    {
        if (value < -128)
            return -128;

        if (value > 127)
            return 127;

        return value;
    }
    void GetAngleToTarget(Vector3& vTargetPos, Vector3& vCameraPos, Vector3& vAngles)
    {
        Vector3 vDelta;
        vDelta.x = vTargetPos.x - vCameraPos.x;
        vDelta.y = vTargetPos.y - vCameraPos.y;
        vDelta.z = vTargetPos.z - vCameraPos.z;

        VectorAngles(vDelta, vAngles);
    }

    void VectorAngles(const Vector3& forward, Vector3& angles)
    {
        float tmp, yaw, pitch;

        if (forward.y == 0 && forward.x == 0)
        {
            yaw = 0;
            if (forward.z > 0)
                pitch = 270;
            else
                pitch = 90;
        }
        else
        {
            yaw = (atan2f(forward.y, forward.x) * 180.0 / M_PI);
            if (yaw < 0)
                yaw += 360;

            tmp = sqrtf(forward.x * forward.x + forward.y * forward.y);
            pitch = (atan2f(-forward.z, tmp) * 180.0 / M_PI);
            if (pitch < 0)
                pitch += 360;
        }

        angles.x = yaw;
        angles.y = pitch;
        angles.z = 0;
    }
    Angle ToAngle(Vector3 vec) {
        Angle angle;
        angle.yaw = atan2(sqrt((vec.y * vec.y) + (vec.z * vec.z)), vec.x);
        angle.pitch = atan2(sqrt((vec.z * vec.z) + (vec.x * vec.x)), vec.y);
        return angle;
    }
    float Dist2D(Vector2 from, Vector2 to) {
        float val = ((from.x - to.x) * (from.x - to.x) + ((from.y - to.y) * (from.y - to.y)));

        return sqrt(val);
    }

    float Dist3D(Vector3 from, Vector3 to) {
        float val = ((to.x - from.x) * (to.x - from.x)) + ((to.y - from.y) * (to.y - from.y)) + ((to.z - from.z) * (to.z - from.z));

        return sqrt(val);
    }
    Vector2 Add2D(Vector2 from, Vector2 to) {
        Vector2 result;
        float x = from.x + to.x;
        float y = from.y + to.y;
        result.x = x; result.y = y;

        return result;
    }
    Vector3 Add3D(Vector3 from, Vector3 to) {
        Vector3 result;
        float x = from.x + to.x;
        float y = from.y + to.y;
        float z = from.z + to.z;
        result.x = x; result.y = y; result.z = z;

        return result;
    }
    Vector2 Sub2D(Vector2 from, Vector2 to) {
        Vector2 result;
        float x = from.x - to.x;
        float y = from.y - to.y;
        result.x = x; result.y = y;

        return result;
    }
    Vector3 Sub3D(Vector3 from, Vector3 to) {
        Vector3 result;
        float x = from.x - to.x;
        float y = from.y - to.y;
        float z = from.z - to.z;
        result.x = x; result.y = y; result.z = z;

        return result;
    }
} VecMath;

Vector3 WorldToScreen(Vector3, ViewMatrix, int, int);

float Dist3D(Vector3, Vector3);

void AimAtPos(float x, float y, int Width, int Height, int);