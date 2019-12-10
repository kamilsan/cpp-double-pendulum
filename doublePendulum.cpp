#include "doublePendulum.hpp"

#include <cmath>

void DoublePendulum::update(double stepSize)
{
  const double K10 = stepSize*angularVelocity1_;
  const double L10 = stepSize*calculateAngularAcceleration1(theta1_, theta2_);
  const double K20 = stepSize*angularVelocity2_;
  const double L20 = stepSize*calculateAngularAcceleration2(theta1_, theta2_);
  
  const double K11 = stepSize*(angularVelocity1_ + 0.5*L10);
  const double L11 = stepSize*calculateAngularAcceleration1(theta1_ + 0.5*K10, theta2_ + 0.5*K20);
  const double K21 = stepSize*(angularVelocity2_ + 0.5*L20);
  const double L21 = stepSize*calculateAngularAcceleration2(theta1_ + 0.5*K10, theta2_ + 0.5*K20);

  const double K12 = stepSize*(angularVelocity1_ + 0.5*L11);
  const double L12 = stepSize*calculateAngularAcceleration1(theta1_ + 0.5*K11, theta2_ + 0.5*K21);
  const double K22 = stepSize*(angularVelocity2_ + 0.5*L21);
  const double L22 = stepSize*calculateAngularAcceleration2(theta1_ + 0.5*K11, theta2_ + 0.5*K21);

  const double K13 = stepSize*(angularVelocity1_ + L12);
  const double L13 = stepSize*calculateAngularAcceleration1(theta1_ + K12, theta2_ + K22);
  const double K23 = stepSize*(angularVelocity2_ + L22);
  const double L23 = stepSize*calculateAngularAcceleration2(theta1_ + K12, theta2_ + K22);

  theta1_ += 1.0/6.0*(K10+2.0*K11+2.0*K12+K13);
  angularVelocity1_ += 1.0/6.0*(L10+2.0*L11+2.0*L12+L13);
  theta2_ += 1.0/6.0*(K20+2.0*K21+2.0*K22+K23);
  angularVelocity2_ += 1.0/6.0*(L20+2.0*L21+2.0*L22+L23);
}

double DoublePendulum::getTheta1() const
{
  return theta1_;
}

double DoublePendulum::getTheta2() const
{
  return theta2_;
}

double DoublePendulum::getLength1() const
{
  return l1_;
}

double DoublePendulum::getLength2() const
{
  return l2_;
}

double DoublePendulum::calculateAngularAcceleration1(double th1, double th2)
{
  const double sinAdiff = std::sin(th1-th2);
  const double cosAdiff = std::cos(th1-th2);
  const double det = (m1_+m2_)*m2_*l1_*l2_ - m2_*m2_*l1_*l2_*cosAdiff*cosAdiff;
  const double A = -m2_*l2_*angularVelocity2_*angularVelocity2_*sinAdiff - (m1_+m2_)*g_*std::sin(th1);
  const double B = m2_*l1_*angularVelocity1_*angularVelocity1_*sinAdiff - m2_*g_*std::sin(th2);

  return (m2_*l2_*A - m2_*l2_*cosAdiff*B)/det;
}

double DoublePendulum::calculateAngularAcceleration2(double th1, double th2)
{
  const double sinAdiff = std::sin(th1-th2);
  const double cosAdiff = std::cos(th1-th2);
  const double det = (m1_+m2_)*m2_*l1_*l2_ - m2_*m2_*l1_*l2_*cosAdiff*cosAdiff;
  const double A = -m2_*l2_*angularVelocity2_*angularVelocity2_*sinAdiff - (m1_+m2_)*g_*std::sin(th1);
  const double B = m2_*l1_*angularVelocity1_*angularVelocity1_*sinAdiff - m2_*g_*std::sin(th2);

  return (-m2_*l1_*cosAdiff*A + (m1_+m2_)*l1_*B)/det;
}