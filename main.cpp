//#define IS_FIRST_TASK
#include <iostream>
#include <cmath>

#ifdef IS_FIRST_TASK
#include "array"

class Point {
  private:
    int x;
    int y;
    int z;

  public:
    explicit Point(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}

    [[nodiscard]] int getX() const {
      return x;
    }

    void setX(int value) {
      Point::x = value;
    }

    [[nodiscard]] int getY() const {
      return y;
    }

    void setY(int value) {
      Point::y = value;
    }

    int getZ() const {
      return z;
    }

    void setZ(int value) {
      Point::z = value;
    }

    static double distance(Point a, Point b) {
      return sqrt(
          pow(b.x - a.x, 2)
          + pow(b.y - a.y, 2)
          + pow(b.z - a.z, 2)
        );
    }

    double distanceToZeroPoint() {
      return Point::distance(*this, Point{0, 0, 0});
    }
};

class Triangle {
  private:
    std::array<Point, 3> coords;

  public:
    explicit Triangle(const std::array<Point, 3> &coords) : coords(coords) {}

    double perimeter() {
      Point a = this->coords[0];
      Point b = this->coords[1];
      Point c = this->coords[2];

      double AB = Point::distance(a, b);
      double CB = Point::distance(c, b);
      double AC = Point::distance(a, c);

      return AB + CB + AC;
    }
};

int main() {
  Point x{-8, 6};

  std::cout << "distanceToZeroPoint: " << x.distanceToZeroPoint() << std::endl;

  std::array<Point, 3> vertices{
    Point{-1, -1, -1},
    Point{-1, 3, -1},
    Point{-1, -1, 2}
  };

  Triangle triangle{vertices};

  std::cout << "perimeter: " << triangle.perimeter();

  return 0;
}

#else

class Triangle {
  protected:
    double sideA;
    double sideB;
    double angle;

  public:
    Triangle(double sideA, double sideB, double angle)
      : sideA(sideA), sideB(sideB), angle(angle) {}

  public:
    virtual double perimeter() = 0;
};

class RightTriangle: public Triangle {
  public:
    RightTriangle(double sideA, double sideB)
      : Triangle(sideA, sideB, 90) {}

    double perimeter() override {
      double sideC = sqrt(pow(this->sideA, 2) + pow(this->sideB, 2));

      return sideA + sideB + sideC;
    }
};

class EquilateralTriangle: public Triangle {
  public:
    EquilateralTriangle(double sideA)
        : Triangle(sideA, sideA, 60) {}

    double perimeter() override {
      return sideA * 3;
    }
};

class IsoscelesTriangle: public Triangle {
  public:
    IsoscelesTriangle(double sideA, double angle)
        : Triangle(sideA, sideA, angle) {}

    double perimeter() override {
      double base = 2 * sideA * sin(angle / 2);

      return sideA + sideB + base;
    }
};

int main() {
  RightTriangle rightTriangle{10, 20};

  std::cout << "rightTriangle: " << rightTriangle.perimeter() << std::endl;

  IsoscelesTriangle isoscelesTriangle{10, 50};

  std::cout << "isoscelesTriangle: " << isoscelesTriangle.perimeter() << std::endl;

  EquilateralTriangle equilateralTriangle{10};

  std::cout << "equilateralTriangle: " << equilateralTriangle.perimeter() << std::endl;

  return 0;
}

#endif
