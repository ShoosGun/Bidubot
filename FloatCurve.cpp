#include "VectorMath.hpp"

class SimpleFloatCurve
{
public:
  typedef float (*FloatCurveFuncPtr)(float);
  
  SimpleFloatCurve(FloatCurveFuncPtr floatCurveFuncPtr, float phase = 0.f, float coeficient = 1.f):m_floatCurveFuncPtr{floatCurveFuncPtr}, m_phase{phase}, m_coeficient{coeficient}
  {}

  float Evaluate(float f)
  {
    return (*m_floatCurveFuncPtr)(f*m_coeficient + m_phase);
  }
private:
  float m_phase;
  float m_coeficient;
  FloatCurveFuncPtr m_floatCurveFuncPtr;

};

class Vector3FloatCurve
{
public:
  typedef Vector3 (*Vector3CurveFuncPtr)(float);
  
  Vector3FloatCurve(Vector3CurveFuncPtr vector3CurveFuncPtr, float phase = 0.f, float coeficient = 1.f):m_vector3CurveFuncPtr{vector3CurveFuncPtr}, m_phase{phase}, m_coeficient{coeficient}
  {}

  Vector3 Evaluate(float f)
  {
    return (*m_vector3CurveFuncPtr)(f*m_coeficient + m_phase);
  }
private:
  float m_phase;
  float m_coeficient;
  Vector3CurveFuncPtr m_vector3CurveFuncPtr;

};
