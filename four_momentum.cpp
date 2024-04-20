#include "four_momentum.h"

FourMomentum operator+(const FourMomentum &p1, const FourMomentum &p2)
{
  double E = p1.get_E() + p2.get_E();
  double px = p1.get_px() + p2.get_px();
  double py = p1.get_py() + p2.get_py();
  double pz = p1.get_pz() + p2.get_pz();
  return FourMomentum(E, px, py, pz);
}

FourMomentum operator-(const FourMomentum &p1, const FourMomentum &p2)
{
  double E = p1.get_E() - p2.get_E();
  double px = p1.get_px() - p2.get_px();
  double py = p1.get_py() - p2.get_py();
  double pz = p1.get_pz() - p2.get_pz();
  return FourMomentum(E, px, py, pz);
}

double dotProduct(const FourMomentum &p1, const FourMomentum &p2)
{
  return p1.get_E() * p2.get_E() - p1.get_px() * p2.get_px() - p1.get_py() * p2.get_py() -
         p1.get_pz() * p2.get_pz();
}

double FourMomentum::invariant_mass() const
{
  double E = four_momentum[0];
  double px = four_momentum[1];
  double py = four_momentum[2];
  double pz = four_momentum[3];
  return std::sqrt(E*E - px*px - py*py - pz*pz);
}