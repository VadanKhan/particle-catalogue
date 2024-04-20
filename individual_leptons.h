#ifndef INDIVIDUAL_LEPTON_H
#define INDIVIDUAL_LEPTON_H

#include "lepton.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

class Electron : public Lepton
{
private:
  std::vector<double> deposition_energies;

public:
  // Constructor
  Electron(double E, double px, double py, double pz,
           const std::vector<double> &deposition_energies)
      : Lepton("electron", E, px, py, pz), deposition_energies{deposition_energies}
  {
    // Check that the total energy deposited in the calorimeter layers is equal to the energy of the
    // electron
    double total_energy =
        std::accumulate(deposition_energies.begin(), deposition_energies.end(), 0.0);
    if (std::abs(total_energy - E) > 1e-6)
    {
      throw std::invalid_argument("The total energy deposited in the calorimeter layers must be "
                                  "equal to the energy of the electron.");
    }
  }

  // Destructor
  ~Electron () {
    // std::cout << "Derived Class Destroying " << type << "\n";
    }

  // Print function prototype
  void print(const std::string &name = "Particle Details") const override;
};

class Muon : public Lepton
{
private:
  bool is_isolated;

public:
  // Constructor
  Muon(double E, double px, double py, double pz, bool is_isolated)
      : Lepton("muon", E, px, py, pz), is_isolated{is_isolated}
  {
  }

  // Destructor
  ~Muon () {
    // std::cout << "Derived Class Destroying " << type << "\n";
    }

  // Print function prototype
  void print(const std::string &name = "Particle Details") const override;
};

class Neutrino : public Lepton
{
private:
  bool hasInteracted;

public:
  // Constructor
  Neutrino(std::string neutrino_flavour, double E, double px, double py, double pz,
           bool hasInteracted)
      : Lepton(neutrino_flavour + " neutrino", E, px, py, pz), hasInteracted{hasInteracted}
  {
    if (neutrino_flavour != "electron" && neutrino_flavour != "muon" && neutrino_flavour != "tau" &&
        neutrino_flavour != "general")
    {
      throw std::invalid_argument(
          "Decay type must be either 'electron', 'muon', 'tau' or 'general'.");
    }
  }

  // Destructor
  ~Neutrino () {
    // std::cout << "Derived Class Destroying " << type << "\n";
    }

  // Print function prototypTe
  void print(const std::string &name = "Particle Details") const override;
};

class Tau : public Lepton
{
private:
  std::string decayFlavour;
  std::unique_ptr<Lepton> decayProduct1; // Pointer to the first decay product
  std::unique_ptr<Lepton> decayProduct2; // Pointer to the second decay product
  std::unique_ptr<Lepton> decayProduct3; // Pointer to the third decay product
  // NB: Declaring these as pointers to Lepton mean the pointers can only have access to methods
  // from Lepton.

public:
  // Constructor
  Tau(double E, double px, double py, double pz, std::string decayFlavour)
      : Lepton("tau", E, px, py, pz), decayFlavour{decayFlavour}
  {
    if (decayFlavour != "electron" && decayFlavour != "muon" && decayFlavour != "hadron_first" &&
        decayFlavour != "hadron_second" && decayFlavour != "hadron_third")
    {
      throw std::invalid_argument("Decay flavour must be 'electron', 'muon', 'hadron_first', "
                                  "'hadron_second', or 'hadron_third'.");
    }

    if (decayFlavour == "electron")
    {
      // If the tau decays leptonically, create the decay products
      decayProduct1 = std::make_unique<Electron>(
          E / 3, px / 3, py / 3, pz / 3, std::vector<double>{E / 12, E / 12, E / 12, E / 12});
      decayProduct2 =
          std::make_unique<Neutrino>(decayFlavour, E / 3, px / 3, py / 3, pz / 3, false);
      decayProduct2->charge_conjugate(); // Convert the neutrino to an antineutrino
      decayProduct3 = std::make_unique<Neutrino>("tau", E / 3, px / 3, py / 3, pz / 3, false);
    }

    else if (decayFlavour == "muon")
    {
      // If the tau decays leptonically, create the decay products
      decayProduct1 = std::make_unique<Muon>(E / 3, px / 3, py / 3, pz / 3, false);
      decayProduct2 =
          std::make_unique<Neutrino>(decayFlavour, E / 3, px / 3, py / 3, pz / 3, false);
      decayProduct2->charge_conjugate(); // Convert the neutrino to an antineutrino
      decayProduct3 = std::make_unique<Neutrino>("tau", E / 3, px / 3, py / 3, pz / 3, false);
    }
  }

  // Destructor
  ~Tau () {
    // std::cout << "Derived Class Destroying " << type << "\n";
    }

  // Print function prototype
  void print(const std::string &name = "Particle Details") const override;

  // Overridden charge_conjugate method prototype
  Tau &charge_conjugate();
};

#endif