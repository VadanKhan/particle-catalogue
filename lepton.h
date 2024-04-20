#ifndef LEPTON_H
#define LEPTON_H

//CHANGES suggestion using #pragma once is a lot easier

#include "particle.h"

class Lepton : public Particle
{
protected:
  //std::string type; //CHANGES - you're already inheriting this
  // ok with this then you've got a 'type' variable in this class, and 'type' in the Particle base class.
  // because you've overridden access Particle's variable 'type' it will print wrong
  // (you can still access the base type at 'Particle::type' however )
  int charge = -1;
  //std::unique_ptr<FourMomentum> four_momentum; //CHANGES again same as above
  int lepton_number = 1;

  static const double LEPTON_SPIN;

public:
  // Default constructor
  Lepton() : Particle(), charge{1} {}

  // Parameterized constructor
  Lepton(std::string lepton_type, double E, double px, double py, double pz)
      : Particle(lepton_type,E,px,py,pz) //CHANGES - you cant initialise members of a base class.
      //you can  use the constructor of the base class, you can assign to the base class members in this constructors code { type = something;}
      //: type{lepton_type}, charge{1}, four_momentum(std::make_unique<FourMomentum>(E, px, py, pz))
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
  /*
  std::string get_type() const {
    std::cout<<"T2"<<std::endl;
    return type; }
  void set_type(const std::string& new_type) { type = new_type; }
  */

  // Getters and Setters: 4momentum
/*
  FourMomentum *get_four_momentum() const { return four_momentum.get(); }
  void set_four_momentum(FourMomentum* new_four_momentum) { four_momentum.reset(new_four_momentum); }
*/

  // CLASS METHODS

  // Print function prototype
  //again you've already virtual'd this in the base class
  void print(const std::string &name) const override; //CHANGES - override isnt needed but its a good way to force checking that you're overriding a virtual function and not just declaring a new function here

  // charge conjugate prototype
  virtual Lepton& charge_conjugate();
};

#endif