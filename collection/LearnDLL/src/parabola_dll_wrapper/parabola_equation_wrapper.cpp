#include "parabola_dll_wrapper/parabola_equation_wrapper.h"

#include <cassert>

namespace parabola_dll_wrapper {

static const char* kParabolaDllPath = "..\\parabola_equation_dll\\Debug\\parabola_equation_api.dll";

ParabolaEquationWrapper::ParabolaEquationWrapper() {
  Init();
}

ParabolaEquationWrapper::~ParabolaEquationWrapper() {
  Destroy();
}

bool ParabolaEquationWrapper::Load() {
  dll_ = LoadLibrary(kParabolaDllPath);
  if (dll_ == NULL) {
    return false;
  }

  create_handle_ = (Parabola_CreateHandle)GetProcAddress(dll_, "Parabola_CreateHandle");
  if (create_handle_ == NULL) {
    return false;
  }

  delete_handle_ = (Parabola_DeleteHandle)GetProcAddress(dll_, "Parabola_DeleteHandle");
  if (delete_handle_ == NULL) {
    return false;
  }

  input_three_points_ = (Parabola_InputThreePoints)GetProcAddress(dll_, "Parabola_InputThreePoints");
  if (input_three_points_ == NULL) {
    return false;
  }

  is_correct_parabola_ = (Parabola_IsCorrectParabola)GetProcAddress(dll_, "Parabola_IsCorrectParabola");
  if (is_correct_parabola_ == NULL) {
    return false;
  }

  output_y_ = (Parabola_OutputY)GetProcAddress(dll_, "Parabola_OutputY");
  if (is_correct_parabola_ == NULL) {
    return false;
  }

  output_slope_ = (Parabola_OutputSlope)GetProcAddress(dll_, "Parabola_OutputSlope");
  if (output_slope_ == NULL) {
    return false;
  }

  get_parabola_equation_string_ = (Parabola_GetParabolaEquationString)GetProcAddress(dll_, "Parabola_GetParabolaEquationString");
  if (get_parabola_equation_string_ == NULL) {
    return false;
  }

  get_slope_equation_string_ = (Parabola_GetSlopeEquationString)GetProcAddress(dll_, "Parabola_GetSlopeEquationString");
  if (get_slope_equation_string_ == NULL) {
    return false;
  }

  get_weights_ = (Parabola_GetWeights)GetProcAddress(dll_, "Parabola_GetWeights");
  if (get_weights_ == NULL) {
    return false;
  }

  is_loaded_ = true;

  parabola_handle_ = create_handle_();
  if (parabola_handle_ == NULL) {
    return false;
  }

  return true;
}

void ParabolaEquationWrapper::Destroy() {
  if (parabola_handle_ != NULL) {
    delete_handle_(parabola_handle_);
  }

  if (dll_ != NULL) {
    FreeLibrary(dll_);
  }

  Init();
}

void ParabolaEquationWrapper::InputThreePoints(double x1, double y1, double x2, double y2, double x3, double y3) {
  assert(dll_ != NULL && parabola_handle_ != NULL);

  input_three_points_(parabola_handle_, x1, y1, x2, y2, x3, y3);
}

bool ParabolaEquationWrapper::IsCorrectParabola() const {
  assert(dll_ != NULL && parabola_handle_ != NULL);

  int ret = is_correct_parabola_(parabola_handle_);
  if (ret == 0) {
    return false;
  }

  return true;
}

double ParabolaEquationWrapper::OutputY(double x) const {
  assert(dll_ != NULL && parabola_handle_ != NULL);

  double y = 0.0;
  output_y_(parabola_handle_, x, &y);

  return y;
}

double ParabolaEquationWrapper::OutputSlope(double x) const {
  assert(dll_ != NULL && parabola_handle_ != NULL);

  double slope = 0.0;
  output_slope_(parabola_handle_, x, &slope);

  return slope;
}

std::string ParabolaEquationWrapper::GetParabolaEquationString() const {
  assert(dll_ != NULL && parabola_handle_ != NULL);

  char buf[256] = { 0 };
  get_parabola_equation_string_(parabola_handle_, buf, 256);

  return buf;
}

std::string ParabolaEquationWrapper::GetSlopeEquationString() const {
  assert(dll_ != NULL && parabola_handle_ != NULL);

  char buf[256] = { 0 };
  get_slope_equation_string_(parabola_handle_, buf, 256);

  return buf;
}

void ParabolaEquationWrapper::GetWeights(double& a, double& b, double& c) const {
  assert(dll_ != NULL && parabola_handle_ != NULL);

  get_weights_(parabola_handle_, &a, &b, &c);
}

void ParabolaEquationWrapper::Init() {
  is_loaded_ = false;
  dll_ = NULL;
  parabola_handle_ = NULL;
  create_handle_ = NULL;
  delete_handle_ = NULL;
  input_three_points_ = NULL;
  is_correct_parabola_ = NULL;
  output_y_ = NULL;
  output_slope_ = NULL;
  get_parabola_equation_string_ = NULL;
  get_slope_equation_string_ = NULL;
  get_weights_ = NULL;
}

}  // namespace parabola_dll_wrapper
