#ifndef LEPTON_H
#define LEPTON_H

#include "particle.h"

class Lepton : public Particle
{
protected:
  std::string type;
  int charge = -1;
  std::unique_ptr<FourMomentum> four_momentum;
  int lepton_number = 1;

  static const double LEPTON_SPIN;

public:
  // Default constructor
  Lepton() : Particle(), charge{1} {}

  // Parameterized constructor
  Lepton(std::string lepton_type, double E, double px, double py, double pz)
      : type{lepton_type}, charge{1}, four_momentum(std::make_unique<FourMomentum>(E, px, py, pz))
  {
  }

  // Destructor
  virtual ~Lepton() {
      // std::cout << "Base Class Destroying " << type << " Lepton \n";
      }

  // Getters Lepton Number: Lepton Number
  int get_lepton_number() const { return lepton_number; }

  // Getters and Setters: Charge
  int get_charge() const { return charge; }
  void set_charge(int new_charge)
  {
    if(new_charge != -1 && new_charge != 1)
    {
      throw std::invalid_argument("Charge must be either -1 or 1.");
    }
    charge = new_charge;
  }
  // Getters and Setters: Type
  std::string get_type() const { return type; }
  void set_type(const std::string& new_type) { type = new_type; }

  // Getters and Setters: 4momentum
  FourMomentum *get_four_momentum() const { return four_momentum.get(); }
  void set_four_momentum(FourMomentum* new_four_momentum) { four_momentum.reset(new_four_momentum); }

  // CLASS METHODS

  // Print function prototype
  virtual void print(const std::string &name = "Particle Details") const;

  // charge conjugate prototype
  virtual Lepton& charge_conjugate();
};

#endif