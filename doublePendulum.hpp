#pragma once

#include <utility>

class DoublePendulum
{
public:
  DoublePendulum(double g, double l1, double m1, double l2, double m2, double theta1, double theta2): 
    g_(g), 
    l1_(l1), 
    m1_(m1),
    l2_(l2),
    m2_(m2), 
    theta1_(theta1),
    theta2_(theta2),
    angularVelocity1_(0),
    angularVelocity2_(0) {}

  void update(double stepSize);

  double getTheta1() const;
  double getTheta2() const;
  double getLength1() const;
  double getLength2() const;

private:
  double g_;
  double l1_;
  double m1_;
  double l2_;
  double m2_;
  double theta1_;
  double theta2_;
  double angularVelocity1_;
  double angularVelocity2_;

  std::pair<double, double> calculateAngularAccelerations(double th1, double th2);
};