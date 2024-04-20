#include "individual_leptons.h"

// Electron Print function
void Electron::print(const std::string &name) const
{
  Lepton::print(name);
  std::cout << "Energies deposited in calorimeter layers : ";
  for (double energy : deposition_energies)
  {
    std::cout << energy << " ";
  }
  std::cout << "\n";
}

// Muon print function
void Muon::print(const std::string &name) const
{
  Lepton::print(name);
  std::cout << "Is isolated: " << (is_isolated ? "Yes" : "No") << "\n";
}

// Neutrino print function
void Neutrino::print(const std::string &name) const
{
  Lepton::print(name);
  std::cout << "Has interacted: " << (hasInteracted ? "Yes" : "No") << "\n";
}

// Tau Print Function
void Tau::print(const std::string &name) const
{
  Lepton::print(name);
  std::cout << "Decay flavour: " << decayFlavour << "\n";
if (decayFlavour == "electron" || decayFlavour == "muon")
  {
    std::cout << "Decay products:\n";
    std::cout << decayProduct1->get_type() << "\n"; // THESE PARTS ARE BUGGED
    std::cout << decayProduct2->get_type() << "\n";
    std::cout << decayProduct3->get_type() << "\n";
  }
}

// Overridden charge_conjugate method for Tau
Tau &Tau::charge_conjugate()
{
  Lepton::charge_conjugate(); // Call the base class charge_conjugate method
  if (decayProduct1)
    decayProduct1->charge_conjugate();
  if (decayProduct2)
    decayProduct2->charge_conjugate();
  if (decayProduct3)
    decayProduct3->charge_conjugate();
  return *this;
}
