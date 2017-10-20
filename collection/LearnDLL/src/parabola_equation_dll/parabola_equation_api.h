#ifndef PARABOLA_EQUATION_DLL_PARABOLA_EQUATION_API_H_
#define PARABOLA_EQUATION_DLL_PARABOLA_EQUATION_API_H_

#ifdef PARABOLA_EQUATION_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void* ParabolaHandle;

DLL_API ParabolaHandle Parabola_CreateHandle();

DLL_API void Parabola_DeleteHandle(ParabolaHandle* handle);

DLL_API void Parabola_InputThreePoints(ParabolaHandle* handle,
                                       double x1,
                                       double y1,
                                       double x2,
                                       double y2,
                                       double x3,
                                       double y3);

// False: 0, True: 1.
DLL_API int Parabola_IsCorrectParabola(ParabolaHandle* handle);

DLL_API int Parabola_OutputY(ParabolaHandle* handle, double x, double* y);

DLL_API int Parabola_OutputSlope(ParabolaHandle* handle, double x, double* slope);

DLL_API int Parabola_GetParabolaEquationString(ParabolaHandle* handle, char* buf, unsigned int buf_size);

DLL_API int Parabola_GetSlopeEquationString(ParabolaHandle* handle, char* buf, unsigned int buf_size);

DLL_API int Parabola_GetWeights(ParabolaHandle* handle, double* a, double* b, double* c);

#ifdef __cplusplus
};
#endif

#endif  // PARABOLA_EQUATION_DLL_PARABOLA_EQUATION_API_H_
