#include <cmath>
#include <string>

#include "image.hpp"
#include "doublePendulum.hpp"

int main()
{
  Image img{512, 512};
  DoublePendulum pendulum{9.81, 0.2, 2, 0.2, 2, M_PI/4, M_PI/2};

  const unsigned int SIMULATION_STEPS = 1000;
  const double STEP_SIZE = 0.01;
  const double PIXELS_PER_METER = 1000;

  const double anchorX = 0.5*img.getWidth();
  const double anchorY = 0.0;

  for(unsigned int step = 0; step < SIMULATION_STEPS; ++step)
  {
    pendulum.update(STEP_SIZE);

    const double theta1 = pendulum.getTheta1();
    const double theta2 = pendulum.getTheta2();

    const int x1 = anchorX + PIXELS_PER_METER*pendulum.getLength1()*std::sin(theta1) + 0.5;
    const int y1 = anchorY + PIXELS_PER_METER*pendulum.getLength1()*std::cos(theta1) + 0.5;
    const int x2 = x1 + PIXELS_PER_METER*pendulum.getLength2()*std::sin(theta2) + 0.5;
    const int y2 = y1 + PIXELS_PER_METER*pendulum.getLength2()*std::cos(theta2) + 0.5;

    img.clear(Color::White);
    img.drawLine(anchorX, anchorY, x1, y1, Color::Black);
    img.drawLine(x1, y1, x2, y2, Color::Black);
    img.fillCircle(x1, y1, 10, Color::Black);
    img.fillCircle(x2, y2, 10, Color::Black);

    const std::string fileName = "frames/frame" + std::to_string(step) + ".ppm";
    img.save(fileName.c_str());
  }

  return 0;
}