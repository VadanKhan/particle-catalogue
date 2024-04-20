// # Lepton Physics Simulation

// This project simulates lepton physics interactions using C++. It includes the creation of various
// leptons, calculation of their four-momenta, and operations such as sum and dot product of
// four-momenta.

// For more details, please refer to the "README.md"

#include "four_momentum.h"
#include "individual_leptons.h"
#include "lepton.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using std::string;

const double Lepton::LEPTON_SPIN = 0.5; // Setting spin const static variable for leptons
const double FourMomentum::ELECTRON_MASS = 0.51099;      // MeV
const double FourMomentum::MUON_MASS = 105.66;         // MeV
const double FourMomentum::TAU_MASS = 1776.9;         // MeV, there is higher uncertainty as much rarer

// Main program
int main()
{
  // CREATING ALL THE APPROPRIATE PARTICLES
  std::vector<std::unique_ptr<Lepton>> particles;

  // Create two electrons
  particles.push_back(
      std::make_unique<Electron>(1.0, 0.0, 0.0, 0.0, std::vector<double>{0.25, 0.25, 0.25, 0.25}));
  particles.push_back(
      std::make_unique<Electron>(1.0, 0.0, 0.0, 0.0, std::vector<double>{0.25, 0.25, 0.25, 0.25}));

  // Create four muons
  for (int i = 0; i < 4; ++i)
  {
    particles.push_back(std::make_unique<Muon>(1.0, 0.0, 0.0, 0.0, true));
  }

  // Create one antielectron and one antimuon with positive energy
  auto antielectron =
      std::make_unique<Electron>(1.0, 0.5, 0.5, 0.0, std::vector<double>{0.25, 0.25, 0.25, 0.25});
  antielectron->charge_conjugate();
  particles.push_back(std::move(antielectron));
  auto antimuon = std::make_unique<Muon>(1.0, 0.5, 0.0, 0.5, true);
  antimuon->charge_conjugate();
  particles.push_back(std::move(antimuon));

  // Create one muon neutrino and one electron neutrino
  particles.push_back(std::make_unique<Neutrino>("muon", 1.0, 0.0, 0.0, 0.0, false));
  particles.push_back(std::make_unique<Neutrino>("electron", 1.0, 0.0, 0.0, 0.0, false));

  // Create one tau decaying into a muon, a muon antineutrino and a tau neutrino
  particles.push_back(std::make_unique<Tau>(1.0, 0.0, 0.0, 0.0, "muon"));

  // Create one antitau decaying into an antielectron, an electron neutrino and a tau antineutrino
  auto antitau = std::make_unique<Tau>(1.0, 0.0, 0.0, 0.0, "electron");
  antitau->charge_conjugate();
  particles.push_back(std::move(antitau));

  // Call the print functions of all the particles in the vector
  int i = 1;
  for (const auto &particle : particles)
  {
    particle->print("Particle " + std::to_string(i));
    ++i;
  }

  // FRIEND FUNCTIONS AND POINTERS
  std::cout << "=========================================================================="
            << "\n";

  // Sum the four-vectors of the two electrons and print the result on screen
  FourMomentum sum = *particles[0]->get_four_momentum() + *particles[1]->get_four_momentum();
  std::cout << "Sum of four-vectors of the two electrons (particle 1 and 2): (" << sum.get_E()
            << ", " << sum.get_px() << ", " << sum.get_py() << ", " << sum.get_pz() << ")\n\n";

  // Take the dot products of the antielectron and antimuon four-vector and print the result on
  // screen
  double dot_product =
      dotProduct(*particles[6]->get_four_momentum(), *particles[7]->get_four_momentum());
  std::cout << "Dot product of the four-vectors of the antielectron (particle 7) and antimuon "
               "(particle 8): "
            << dot_product << "\n\n";

  // Create a unique pointer for a new electron (outside the original vector) and then move its data
  // to another electron using std::move
  std::unique_ptr<Lepton> new_electron =
      std::make_unique<Electron>(1.0, 0.0, 0.0, 0.0, std::vector<double>{0.25, 0.25, 0.25, 0.25});
  std::cout << "Created a new electron with address: " << new_electron.get() << "\n";
  std::unique_ptr<Lepton> another_electron = std::move(new_electron);
  std::cout << "Moved the new electron to another electron with address: " << another_electron.get()
            << "\n";
  std::cout << "The address of the original electron after moving: " << new_electron.get() << "\n\n";

  // Create a shared pointer for a tau lepton that is owned by multiple variables
  std::shared_ptr<Lepton> tau = std::make_shared<Tau>(1.0, 0.0, 0.0, 0.0, "muon");
  std::cout << "Created a tau lepton with address: " << tau.get() << ", shared by "
            << tau.use_count() << " pointers\n";
  std::shared_ptr<Lepton> tau_copy = tau;
  std::cout << "Copied the tau lepton to tau_copy with address: " << tau_copy.get()
            << ", now shared by " << tau.use_count() << " pointers\n";

  std::cout << "=========================================================================="
            << "\n";

  return 0;
}