#ifdef PARABOLA_EQUATION_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void* ParabolaEquationHandle;

DLL_API ParabolaEquationHandle CreateParabolaEquationHandle();

DLL_API void InputThreePoints(ParabolaEquationHandle* handle,
                              double x1,
                              double y1,
                              double x2,
                              double y2,
                              double x3,
                              double y3);



#ifdef __cplusplus
};
#endif
