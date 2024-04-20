#ifndef FOUR_MOMENTUM_H
#define FOUR_MOMENTUM_H

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class FourMomentum
{

private:
  std::vector<double> four_momentum;

protected:
  static const double ELECTRON_MASS;
  static const double MUON_MASS;
  static const double TAU_MASS;

public:
  // Constructor
  FourMomentum(double E, double px, double py, double pz) : four_momentum{E, px, py, pz}
  {
    if (E < 0)
    {
      throw std::invalid_argument("Energy must be positive.");
    }
  }

  // Copy constructor
  FourMomentum(const FourMomentum &other) : four_momentum(other.four_momentum) {}

  // Copy assignment operator
  FourMomentum &operator=(const FourMomentum &other)
  {
    if (this != &other)
    {
      four_momentum = other.four_momentum;
    }
    return *this;
  }

  // Move constructor
  FourMomentum(FourMomentum &&other) noexcept : four_momentum(std::move(other.four_momentum)) {}

  // Move assignment operator
  FourMomentum &operator=(FourMomentum &&other) noexcept
  {
    if (this != &other)
    {
      four_momentum = std::move(other.four_momentum);
    }
    return *this;
  }

  // Destructor
  ~FourMomentum() {
    // std::cout << "Destroying Four Momentum\n";
    }

  // Getters
  double get_E() const { return four_momentum[0]; }
  double get_px() const { return four_momentum[1]; }
  double get_py() const { return four_momentum[2]; }
  double get_pz() const { return four_momentum[3]; }

  // Setters
  void set_E(double E)
  {
    if (E <= 0)
    {
      throw std::invalid_argument("Energy must be positive.");
    }
    four_momentum[0] = E;
  }
  void set_px(double px) { four_momentum[1] = px; }
  void set_py(double py) { four_momentum[2] = py; }
  void set_pz(double pz) { four_momentum[3] = pz; }

  // Friend functions for sum and dot product of four-momenta
  friend FourMomentum operator+(const FourMomentum &p1, const FourMomentum &p2);
  friend FourMomentum operator-(const FourMomentum &p1, const FourMomentum &p2);
  friend double dotProduct(const FourMomentum &p1, const FourMomentum &p2);

  // Function that returns a number to calculate invariant mass of four-vector (itself)
  double invariant_mass() const;
};

#endif
