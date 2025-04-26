#ifndef ANDROIDGLINVESTIGATIONS_UTILITY_H
#define ANDROIDGLINVESTIGATIONS_UTILITY_H

#include <cassert>

union Vector3 {
    struct {
        float x, y, z;
    };
    float idx[3];
};

union Vector2 {
    struct {
        float x, y;
    };
    struct {
        float u, v;
    };
    float idx[2];
};

struct Vertex {
    constexpr Vertex(const Vector3 &inPosition, const Vector2 &inUV) : position(inPosition),
                                                                       uv(inUV) {}

    Vector3 position;
    Vector2 uv;
};

class Utility {
public:
    static bool checkAndLogGlError(bool alwaysLog = false);

    static inline void assertGlError() { assert(checkAndLogGlError()); }


    static float *buildOrthographicMatrix(
            float *outMatrix,
            float halfHeight,
            float aspect,
            float near,
            float far);

    static float *buildPerspectiveMatrix(
            float *outMatrix,
            float verticalFovDegrees,
            float aspect,
            float near,
            float far);

    static float *buildLookAtMatrix(float *outMatrix, const Vector3 eye, const Vector3 target, const Vector3 up);

    static float *buildIdentityMatrix(float *outMatrix);
};

#endif //ANDROIDGLINVESTIGATIONS_UTILITY_H