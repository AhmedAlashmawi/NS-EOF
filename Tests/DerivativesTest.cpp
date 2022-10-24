#include "StdAfx.hpp"

#include "DataStructures.hpp"
#include "FlowField.hpp"
#include "Iterators.hpp"

#include "Stencils/StencilFunctions.hpp"

constexpr auto SIZE_X = 20;
constexpr auto SIZE_Y = 25;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  spdlog::info("Testing derivatives");

  Parameters parameters;
  parameters.solver.gamma = 0.5;
  RealType lv[81]{}; // Local velocity
  RealType lm[81]{}; // Local meshsize

  for (int i = 0; i < 81; i++) {
    lv[i] = 0;
    lm[i] = 1;
  }

  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      for (int k = -1; k < 2; k++) {
        for (int c = 0; c < 3; c++) {
          lv[Stencils::mapd(i, j, k, c)] = 1;
        }
      }
    }
  }

  for (int i = 0; i < 81; i++) {
    if (!lv[i]) {
      spdlog::error("Failed accessing all elements from coordinates and components");
      return EXIT_FAILURE;
    }
  }

  lv[Stencils::mapd(1, 0, 0, 0)]  = 3;
  lv[Stencils::mapd(0, 0, 0, 0)]  = 2;
  lv[Stencils::mapd(-1, 0, 0, 0)] = 1;

  std::stringstream ss;

  ss
    << "dudx:      " << Stencils::dudx(lv, lm) << std::endl
    << "dvdy:      " << Stencils::dvdy(lv, lm) << std::endl
    << "dwdz:      " << Stencils::dwdz(lv, lm) << std::endl
    <<

    "d2udx2:    " << Stencils::d2udx2(lv, lm) << std::endl
    << "d2udy2:    " << Stencils::d2udy2(lv, lm) << std::endl
    << "d2udz2:    " << Stencils::d2udz2(lv, lm) << std::endl
    << "d2vdx2:    " << Stencils::d2vdx2(lv, lm) << std::endl
    << "d2vdy2:    " << Stencils::d2vdy2(lv, lm) << std::endl
    << "d2vdz2:    " << Stencils::d2vdz2(lv, lm) << std::endl
    << "d2wdx2:    " << Stencils::d2wdx2(lv, lm) << std::endl
    << "d2wdy2:    " << Stencils::d2wdy2(lv, lm) << std::endl
    << "d2wdz2:    " << Stencils::d2wdz2(lv, lm) << std::endl
    <<

    "duvdx:     " << Stencils::duvdx(lv, parameters, lm) << std::endl
    << "duvdy:     " << Stencils::duvdy(lv, parameters, lm) << std::endl
    << "duwdx:     " << Stencils::duwdx(lv, parameters, lm) << std::endl
    << "duwdz:     " << Stencils::duwdz(lv, parameters, lm) << std::endl
    << "dvwdy:     " << Stencils::dvwdy(lv, parameters, lm) << std::endl
    << "dvwdz:     " << Stencils::dvwdz(lv, parameters, lm) << std::endl
    <<

    "du2dx:     " << Stencils::du2dx(lv, parameters, lm) << std::endl
    << "dv2dy:     " << Stencils::dv2dy(lv, parameters, lm) << std::endl
    << "dw2dz:     " << Stencils::dw2dz(lv, parameters, lm) << std::endl;

  spdlog::info(ss.str());

  spdlog::info("Test for derivatives completed successfully");

  return EXIT_SUCCESS;
}
