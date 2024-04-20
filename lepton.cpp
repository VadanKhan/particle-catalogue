#include "lepton.h"



// Print function
void Lepton::print(const std::string &name) const
{
  std::cout << "==========================================================" << "\n";
  std::cout << name << "\n";
  std::cout << "Type: " << type << "\n";
//   std::cout << "Spin: " << LEPTON_SPIN << "\n";
  std::cout << "Lepton Number: " << lepton_number << "\n";
  std::cout << "Charge: " << charge << "\n";
  std::cout << "Four-momentum: (" << four_momentum->get_E() << ", " << four_momentum->get_px()
            << ", " << four_momentum->get_py() << ", " << four_momentum->get_pz() << ")\n";
}

// Implementation of flipping to antiparticle, that returns a pointers to be called in chain.
Lepton& Lepton::charge_conjugate() {
    if (type.rfind("anti-", 0) == 0) {
        // If the type starts with "anti-", remove it
        type = type.substr(5);
    } else {
        // If the type doesn't start with "anti-", add it
        type = "anti-" + type;
    }
    charge = -charge;
    lepton_number = -lepton_number;
    return *this;
}