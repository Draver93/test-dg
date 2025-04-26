#include "Utility.h"
#include "AndroidOut.h"

#include <GLES3/gl3.h>

#define CHECK_ERROR(e) case e: aout << "GL Error: "#e << std::endl; break;

bool Utility::checkAndLogGlError(bool alwaysLog) {
    GLenum error = glGetError();
    if (error == GL_NO_ERROR) {
        if (alwaysLog) {
            aout << "No GL error" << std::endl;
        }
        return true;
    } else {
        switch (error) {
            CHECK_ERROR(GL_INVALID_ENUM);
            CHECK_ERROR(GL_INVALID_VALUE);
            CHECK_ERROR(GL_INVALID_OPERATION);
            CHECK_ERROR(GL_INVALID_FRAMEBUFFER_OPERATION);
            CHECK_ERROR(GL_OUT_OF_MEMORY);
            default:
                aout << "Unknown GL error: " << error << std::endl;
        }
        return false;
    }
}

float *Utility::buildOrthographicMatrix(float *outMatrix, float halfHeight, float aspect, float near, float far) {
    float halfWidth = halfHeight * aspect;

    // column 1
    outMatrix[0] = 1.f / halfWidth;
    outMatrix[1] = 0.f;
    outMatrix[2] = 0.f;
    outMatrix[3] = 0.f;

    // column 2
    outMatrix[4] = 0.f;
    outMatrix[5] = 1.f / halfHeight;
    outMatrix[6] = 0.f;
    outMatrix[7] = 0.f;

    // column 3
    outMatrix[8] = 0.f;
    outMatrix[9] = 0.f;
    outMatrix[10] = -2.f / (far - near);
    outMatrix[11] = -(far + near) / (far - near);

    // column 4
    outMatrix[12] = 0.f;
    outMatrix[13] = 0.f;
    outMatrix[14] = 0.f;
    outMatrix[15] = 1.f;

    return outMatrix;
}

float *Utility::buildPerspectiveMatrix(float *outMatrix, float verticalFovDegrees, float aspect, float near, float far) {
    // set the basic projection matrix
    float scale = 1.0f / (float)tan(verticalFovDegrees * 0.5 * M_PI / 180);
    // Column 1
    outMatrix[0] = scale / aspect;
    outMatrix[1] = 0.f;
    outMatrix[2] = 0.f;
    outMatrix[3] = 0.f;

    // Column 2
    outMatrix[4] = 0.f;
    outMatrix[5] = scale;
    outMatrix[6] = 0.f;
    outMatrix[7] = 0.f;

    // Column 3
    outMatrix[8] = 0.f;
    outMatrix[9] = 0.f;
    outMatrix[10] = -far / (far - near);
    outMatrix[11] = -1.f;

    // Column 4
    outMatrix[12] = 0.f;
    outMatrix[13] = 0.f;
    outMatrix[14] = -far * near / (far - near);
    outMatrix[15] = 0.f;

    return outMatrix;
}

float *Utility::buildLookAtMatrix(float *outMatrix, const Vector3 eye, const Vector3 target, const Vector3 up)  {
    // Calculate forward vector (z axis)
    float fx = target.idx[0] - eye.idx[0];
    float fy = target.idx[1] - eye.idx[1];
    float fz = target.idx[2] - eye.idx[2];
    float rlf = 1.f / sqrtf(fx * fx + fy * fy + fz * fz);
    fx *= rlf;
    fy *= rlf;
    fz *= rlf;

    // Calculate right vector (x axis)
    float sx = fy * up.idx[2] - fz * up.idx[1];
    float sy = fz * up.idx[0] - fx * up.idx[2];
    float sz = fx * up.idx[1] - fy * up.idx[0];
    float rls = 1.f / sqrtf(sx * sx + sy * sy + sz * sz);
    sx *= rls;
    sy *= rls;
    sz *= rls;

    // Calculate true up vector (y axis)
    float ux = sy * fz - sz * fy;
    float uy = sz * fx - sx * fz;
    float uz = sx * fy - sy * fx;

    // column 1
    outMatrix[0] = sx;
    outMatrix[1] = ux;
    outMatrix[2] = -fx;
    outMatrix[3] = 0.f;

    // column 2
    outMatrix[4] = sy;
    outMatrix[5] = uy;
    outMatrix[6] = -fy;
    outMatrix[7] = 0.f;

    // column 3
    outMatrix[8] = sz;
    outMatrix[9] = uz;
    outMatrix[10] = -fz;
    outMatrix[11] = 0.f;

    // column 4
    outMatrix[12] = -(sx * eye.idx[0] + sy * eye.idx[1] + sz * eye.idx[2]);
    outMatrix[13] = -(ux * eye.idx[0] + uy * eye.idx[1] + uz * eye.idx[2]);
    outMatrix[14] = fx * eye.idx[0] + fy * eye.idx[1] + fz * eye.idx[2];
    outMatrix[15] = 1.f;

    return outMatrix;
}

float *Utility::buildIdentityMatrix(float *outMatrix) {
    // column 1
    outMatrix[0] = 1.f;
    outMatrix[1] = 0.f;
    outMatrix[2] = 0.f;
    outMatrix[3] = 0.f;

    // column 2
    outMatrix[4] = 0.f;
    outMatrix[5] = 1.f;
    outMatrix[6] = 0.f;
    outMatrix[7] = 0.f;

    // column 3
    outMatrix[8] = 0.f;
    outMatrix[9] = 0.f;
    outMatrix[10] = 1.f;
    outMatrix[11] = 0.f;

    // column 4
    outMatrix[12] = 0.f;
    outMatrix[13] = 0.f;
    outMatrix[14] = 0.f;
    outMatrix[15] = 1.f;

    return outMatrix;
}