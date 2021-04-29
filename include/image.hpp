#pragma once

#include "color.hpp"
#include "point.hpp"

#include <memory>

class Image
{
  public:
    Image(unsigned width, unsigned height);
    Image(const Image& other);
    Image(Image&& other) noexcept;

    void clear(const Color& color);
    void fillCircle(const Point& center, unsigned int r, const Color& color);
    void drawLine(const Point& pt1, const Point& pt2, const Color& color);
    void setPixel(const Point& pos, const Color& color);
    void setPixel(int x, int y, const Color& color);

    void save(const char* filename) const;
    Color getPixel(const Point& pos) const;
    Color getPixel(unsigned int x, unsigned int y) const;
    unsigned int getWidth() const noexcept { return width_; }
    unsigned int getHeight() const noexcept { return height_; }

    Image& operator=(const Image& other);
    Image& operator=(Image&& other) noexcept;
  private:
    void plot(int x, int y, const Color& color, float a);

    std::unique_ptr<unsigned char[]> pixels_;
    unsigned width_;
    unsigned height_;
    unsigned len_;
};