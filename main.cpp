#include "image.hpp"

int main()
{
  Image img{512, 512};

  img.clear(Color{255, 255, 255});
  img.drawLine(256, 0, 256, 256, Color{0, 0, 0});
  img.fillCircle(256, 256, 10, Color{0, 0, 0});

  img.save("sample_image.ppm");

  return 0;
}