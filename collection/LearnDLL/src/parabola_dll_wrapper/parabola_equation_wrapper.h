#ifndef PARABOLA_DLL_WRAPPER_PARABOLA_EQUATION_WRAPPER_H_
#define PARABOLA_DLL_WRAPPER_PARABOLA_EQUATION_WRAPPER_H_

#include <string>

#include "windows.h"

namespace parabola_dll_wrapper {

typedef void* ParabolaHandle;

typedef ParabolaHandle (*Parabola_CreateHandle)();

typedef void (*Parabola_DeleteHandle)(ParabolaHandle handle);

typedef void (*Parabola_InputThreePoints)(ParabolaHandle handle, double x1, double y1, double x2, double y2, double x3, double y3);

// False: 0, True: 1.
typedef int (*Parabola_IsCorrectParabola)(ParabolaHandle handle);

typedef int (*Parabola_OutputY)(ParabolaHandle handle, double x, double* y);

typedef int (*Parabola_OutputSlope)(ParabolaHandle handle, double x, double* slope);

typedef int (*Parabola_GetParabolaEquationString)(ParabolaHandle handle, char* buf, unsigned int buf_size);

typedef int (*Parabola_GetSlopeEquationString)(ParabolaHandle handle, char* buf, unsigned int buf_size);

typedef int (*Parabola_GetWeights)(ParabolaHandle handle, double* a, double* b, double* c);

//-----------------------------------------------------------------------------------------------

class ParabolaEquationWrapper {
public:
  static ParabolaEquationWrapper* Instance() {
    static ParabolaEquationWrapper wrapper;
    return &wrapper;
  }

  ~ParabolaEquationWrapper();

  bool Load();

  void Destroy();

  bool is_loaded() const {
    return is_loaded_;
  }

  void InputThreePoints(double x1, double y1, double x2, double y2, double x3, double y3);

  bool IsCorrectParabola() const;

  double OutputY(double x) const;

  double OutputSlope(double x) const;

  std::string GetParabolaEquationString() const;

  std::string GetSlopeEquationString() const;

  void GetWeights(double& a, double& b, double& c) const;

private:
  ParabolaEquationWrapper();

  ParabolaEquationWrapper(const ParabolaEquationWrapper&);
  ParabolaEquationWrapper& operator=(const ParabolaEquationWrapper&);

  void Init();

private:
  HMODULE dll_;
  bool is_loaded_;

  ParabolaHandle parabola_handle_;

  Parabola_CreateHandle create_handle_;
  Parabola_DeleteHandle delete_handle_;
  Parabola_InputThreePoints input_three_points_;
  Parabola_IsCorrectParabola is_correct_parabola_;
  Parabola_OutputY output_y_;
  Parabola_OutputSlope output_slope_;
  Parabola_GetParabolaEquationString get_parabola_equation_string_;
  Parabola_GetSlopeEquationString get_slope_equation_string_;
  Parabola_GetWeights get_weights_;
};

}  // namespace parabola_dll_wrapper

#endif  // PARABOLA_DLL_WRAPPER_PARABOLA_EQUATION_WRAPPER_H_
