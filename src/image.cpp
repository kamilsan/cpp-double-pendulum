#include <cmath>
#include <cstring>
#include <fstream>

#include "image.hpp"

Image::Image(unsigned width, unsigned height): width_(width), height_(height), len_(3*width*height)
{
  pixels_ = std::make_unique<unsigned char[]>(len_);
  memset(pixels_.get(), 0, len_*sizeof(unsigned char));
}

Image::Image(const Image& other)
{
  width_ = other.width_;
  height_ = other.height_;
  len_ = other.len_;

  pixels_ = std::make_unique<unsigned char[]>(len_);
  memcpy(pixels_.get(), other.pixels_.get(), len_ * sizeof(unsigned char));
}

Image::Image(Image&& other) noexcept
{
  width_ = other.width_;
  height_ = other.height_;
  len_ = other.len_;
  pixels_ = std::move(other.pixels_);
}

Image& Image::operator=(const Image& other)
{
  if(&other != this)
  {
    width_ = other.width_;
    height_ = other.height_;
    len_ = other.len_;

    pixels_ = std::make_unique<unsigned char[]>(len_);
    memcpy(pixels_.get(), other.pixels_.get(), len_ * sizeof(unsigned char));
  }

  return *this;
}

Image& Image::operator=(Image&& other) noexcept
{
  if(&other != this)
  {
    width_ = other.width_;
    height_ = other.height_;
    len_ = other.len_;
    pixels_ = std::move(other.pixels_);
  }

  return *this;
}

void Image::clear(const Color& color)
{
  for(unsigned y = 0; y < height_; ++y)
  {
    for(unsigned x = 0; x < width_; ++x)
    {
      const int index = 3*(y*width_ + x);
      pixels_[index]   = color.r;
      pixels_[index+1] = color.g;
      pixels_[index+2] = color.b;
    }
  }
}

void Image::drawCircle(const Point& center, unsigned int r, const Color& color)
{
  unsigned int x = 0;
  unsigned int y = r;
  int m = 5 - 4 * r;

  while(x <= y)
  {
    setPixel(center.x + x, center.y + y, color);
    setPixel(center.x - x, center.y + y, color);
    setPixel(center.x + x, center.y - y, color);
    setPixel(center.x - x, center.y - y, color);

    setPixel(center.x + y, center.y + x, color);
    setPixel(center.x - y, center.y + x, color);
    setPixel(center.x + y, center.y - x, color);
    setPixel(center.x - y, center.y - x, color);

    if(m > 0)
    {
      y -= 1;
      m -= 8 * y;
    }
    x += 1;
    m += 8 * x + 4;
  }
}

void Image::fillCircle(const Point& center, unsigned int r, const Color& color)
{
  unsigned int x = 0;
  unsigned int y = r;
  int m = 5 - 4 * r;

  while(x <= y)
  {
    fillLine(center.x - x, center.x + x, center.y + y, color);
    fillLine(center.x - x, center.x + x, center.y - y, color);

    fillLine(center.x - y, center.x + y, center.y + x, color);
    fillLine(center.x - y, center.x + y, center.y - x, color);

    if(m > 0)
    {
      y -= 1;
      m -= 8 * y;
    }
    x += 1;
    m += 8 * x + 4;
  }
}

void Image::fillLine(int xMin, int xMax, int y, const Color& color)
{
  for(int x = xMin; x <= xMax; ++x)
  {
    setPixel(x, y, color);
  }
}

void Image::plot(int x, int y, const Color& color, float a)
{
  // Note: casting to unsigned is probably safe here
  //       because pos.x >= 0 is ensured before
  if(x >= 0 && y >= 0 && (unsigned)x < width_ && (unsigned)y < height_)
  {
    const int i = 3*(y*width_ + x);

    const auto r = a*color.r + (1.0f - a)*pixels_[i] + 0.5f;
    const auto g = a*color.g + (1.0f - a)*pixels_[i+1] + 0.5f;
    const auto b = a*color.b + (1.0f - a)*pixels_[i+2] + 0.5f;

    pixels_[i] = std::min(255.0f, std::max(0.0f, r));
    pixels_[i+1] = std::min(255.0f, std::max(0.0f, g));
    pixels_[i+2] = std::min(255.0f, std::max(0.0f, b));
  }
}

void Image::drawLine(const Point& pt1, const Point& pt2, const Color& color)
{
  const bool steep = abs(pt2.y - pt1.y) > abs(pt2.x - pt1.x);
  float x0 = pt1.x;
  float y0 = pt1.y;
  float x1 = pt2.x;
  float y1 = pt2.y;

  if(steep)
  {
    std::swap(x0, y0);
    std::swap(x1, y1);
  }
  if(x0 > x1)
  {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }
  
  const int dx = x1 - x0;
  const int dy = y1 - y0;
  float m = (float)dy/dx;
  if(dx == 0)
    m = 1;

  float x = x0;
  float y = y0;

  if(steep)
  {
    while(x < x1)
    {
      const int yy = floor(y);
      const float a = y - yy;

      plot(yy, x, color, 1.0f - a);
      plot(yy + 1, x, color, a);

      y += m;
      x += 1;
    }
  }
  else
  {
    while(x < x1)
    {
      const int yy = floor(y);
      const float a = y - yy;

      plot(x, yy, color, 1.0f - a);
      plot(x, yy + 1, color, a);

      y += m;
      x += 1;
    }
  }
}

void Image::setPixel(const Point& pos, const Color& color)
{
  if(pos.x >= 0 && pos.y >= 0 && (unsigned)pos.x < width_ && (unsigned)pos.y < height_)
  {
    const int index = 3*(pos.y*width_ + pos.x);
    pixels_[index]   = color.r;
    pixels_[index+1] = color.g;
    pixels_[index+2] = color.b;
  }
}

void Image::setPixel(int x, int y, const Color& color)
{
  if(x >= 0 && y >= 0 && (unsigned)x < width_ && (unsigned)y < height_)
  {
    const int index = 3*(y*width_ + x);
    pixels_[index]   = color.r;
    pixels_[index+1] = color.g;
    pixels_[index+2] = color.b;
  }
}

void Image::save(const char* filename) const
{
  std::ofstream file;
  file.open(filename, std::ios::binary);
  file << "P6\n" << width_ << " " << height_ << "\n255\n";
  file.write(reinterpret_cast<char*>(pixels_.get()), len_);
  file.close();
}

Color Image::getPixel(const Point& pos) const
{
  if(pos.x >= 0 && pos.y >= 0 && (unsigned)pos.x < width_ && (unsigned)pos.y < height_)
  {
    const int index = 3*(pos.y*width_ + pos.x);
    return Color{pixels_[index], pixels_[index+1], pixels_[index+2]};
  }
  return Color{0, 0, 0};
}

Color Image::getPixel(unsigned int x, unsigned int y) const
{
  if(x < width_ && y < height_)
  {
    const int index = 3*(y*width_ + x);
    return Color{pixels_[index], pixels_[index+1], pixels_[index+2]};
  }
  return Color{0, 0, 0};
}
