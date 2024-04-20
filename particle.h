#ifndef PARTICLE_H
#define PARTICLE_H

#include "four_momentum.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class Particle
{
protected:
  std::string type;
  std::unique_ptr<FourMomentum> four_momentum;

public:
  // Default constructor
  Particle() : type{"Ghost"}, four_momentum(std::make_unique<FourMomentum>(0, 0, 0, 0)) {}

  // Parameterized constructor
  Particle(std::string particle_type, double E, double px, double py, double pz)
      : type{particle_type}, four_momentum(std::make_unique<FourMomentum>(E, px, py, pz))
  {
  }

  // Copy constructor
  Particle(const Particle &other)
      : type{other.type}, four_momentum(std::make_unique<FourMomentum>(*other.four_momentum))
  {
    std::cout << "Calling copy constructor\n";
  }

  // Copy assignment operator
  Particle &operator=(const Particle &other)
  {
    std::cout << "Calling copy assignment operator\n";
    if (this != &other)
    {
      type = other.type;
      four_momentum = std::make_unique<FourMomentum>(*other.four_momentum);
    }
    return *this;
  }

  // Move constructor
  Particle(Particle &&other) noexcept
      : type{std::move(other.type)}, four_momentum{std::move(other.four_momentum)}
  {
    std::cout << "Calling move constructor\n";
  }

  // Move assignment operator
  Particle &operator=(Particle &&other) noexcept
  {
    std::cout << "Calling move assignment operator\n";
    if (this != &other)
    {
      type = std::move(other.type);
      four_momentum = std::move(other.four_momentum);
    }
    return *this;
  }

  // Virtual destructor
  virtual ~Particle() {}

  // CLASS METHODS
  // Getters and Setters: Type
  std::string get_type() const { return type; }
  void set_type(const std::string& new_type) { type = new_type; }

  // Getters and Setters: 4momentum
  FourMomentum *get_four_momentum() const { return four_momentum.get(); }
  void set_four_momentum(FourMomentum* new_four_momentum) { four_momentum.reset(new_four_momentum); }

  // Print function prototype
  virtual void print(const std::string &name = "Particle Details") const = 0; // Pure virtual function
};

#endif