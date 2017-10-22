#include "parabola_equation_dll/parabola_equation_api.h"

#include <string>
#include <cassert>

#include "parabola_equation_sdk/parabola_equation.h"
#include "parabola_equation_sdk/point.h"

using namespace parabola_equation_sdk;

ParabolaHandle Parabola_CreateHandle() {
  ParabolaHandle handle = new ParabolaEquation();
  return handle;
}

void Parabola_DeleteHandle(ParabolaHandle* handle) {
  assert(handle != NULL);

  ParabolaEquation* parabola = (ParabolaEquation*)handle;
  delete parabola;
}

void Parabola_InputThreePoints(ParabolaHandle* handle,
                               double x1,
                               double y1,
                               double x2,
                               double y2,
                               double x3,
                               double y3) {
  assert(handle != NULL);

  ParabolaEquation* parabola = (ParabolaEquation*)handle;
  parabola->InputThreePoints(Point(x1, y1), Point(x2, y2), Point(x3, y3));
}

int Parabola_IsCorrectParabola(ParabolaHandle* handle) {
  assert(handle != NULL);

  ParabolaEquation* parabola = (ParabolaEquation*)handle;
  if (parabola->is_parabola()) {
    return 1;
  }

  return 0;
}

int Parabola_OutputY(ParabolaHandle* handle, double x, double* y) {
  assert(handle != NULL);

  if (y == NULL) {
    return 0;
  }

  ParabolaEquation* parabola = (ParabolaEquation*)handle;
  *y = parabola->OutputY(x);

  return 1;
}

int Parabola_OutputSlope(ParabolaHandle* handle, double x, double* slope) {
  assert(handle != NULL);

  if (slope == NULL) {
    return 0;
  }

  ParabolaEquation* parabola = (ParabolaEquation*)handle;
  *slope = parabola->OutputSlope(x);

  return 1;
}

int Parabola_GetParabolaEquationString(ParabolaHandle* handle, char* buf, unsigned int buf_size) {
  assert(handle != NULL);

  if (buf == NULL) {
    return 0;
  }

  ParabolaEquation* parabola = (ParabolaEquation*)handle;
  std::string equation = parabola->ToParabolaEquationString();
  if (equation.size() >= buf_size) {
    return 0;
  }

  strcpy(buf, equation.c_str());

  return 1;
}

int Parabola_GetSlopeEquationString(ParabolaHandle* handle, char* buf, unsigned int buf_size) {
  assert(handle != NULL);

  if (buf == NULL) {
    return 0;
  }

  ParabolaEquation* parabola = (ParabolaEquation*)handle;
  std::string equation = parabola->ToSlopeEquationString();
  if (equation.size() >= buf_size) {
    return 0;
  }

  strcpy(buf, equation.c_str());

  return 1;
}

int Parabola_GetWeights(ParabolaHandle* handle, double* a, double* b, double* c) {
  assert(handle != NULL);

  if (a == NULL || b == NULL || c == NULL) {
    return 0;
  }

  ParabolaEquation* parabola = (ParabolaEquation*)handle;
  *a = parabola->a();
  *b = parabola->b();
  *c = parabola->c();

  return 1;
}
