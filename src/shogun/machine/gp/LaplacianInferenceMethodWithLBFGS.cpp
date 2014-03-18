/*
 * Copyright (c) The Shogun Machine Learning Toolbox
 * Written (w) 2014 Wu Lin
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the Shogun Development Team.
 * Code adapted from Gaussian Process Machine Learning Toolbox
 * http://www.gaussianprocess.org/gpml/code/matlab/doc/
 */
#include <shogun/machine/gp/LaplacianInferenceMethodWithLBFGS.h>

#ifdef HAVE_EIGEN3
#include <shogun/mathematics/Math.h>
#include <shogun/optimization/lbfgs/lbfgs.h>

namespace shogun
{

CLaplacianInferenceMethodWithLBFGS::CLaplacianInferenceMethodWithLBFGS()
    : CLaplacianInferenceMethod()
{
      init();
}

CLaplacianInferenceMethodWithLBFGS::CLaplacianInferenceMethodWithLBFGS(
    CKernel* kern,
    CFeatures* feat,
    CMeanFunction* m,
    CLabels* lab,
    CLikelihoodModel* mod)
    : CLaplacianInferenceMethod(kern, feat, m, lab, mod)
{
      init();
}

void CLaplacianInferenceMethodWithLBFGS::set_lbfgs_parameter(
    int m,
    int max_linesearch,
    int linesearch,
    int max_iterations,
    float64_t delta,
    int past,
    float64_t epsilon,
    bool enable_newton_if_fail,
    float64_t min_step,
    float64_t max_step,
    float64_t ftol,
    float64_t wolfe,
    float64_t gtol,
    float64_t xtol,
    float64_t orthantwise_c,
    int orthantwise_start,
    int orthantwise_end)
{
  m_m = m;
  m_max_linesearch = max_linesearch;
  m_linesearch = linesearch;
  m_max_iterations = max_iterations;
  m_delta = delta;
  m_past = past;
  m_epsilon = epsilon;
  m_min_step = min_step;
  m_max_step = max_step;
  m_ftol = ftol;
  m_wolfe = wolfe;
  m_gtol = gtol;
  m_xtol = xtol;
  m_orthantwise_c = orthantwise_c;
  m_orthantwise_start = orthantwise_start;
  m_orthantwise_end = orthantwise_end;
  m_enable_newton_if_fail = enable_newton_if_fail;
}

void CLaplacianInferenceMethodWithLBFGS::init()
{
  set_lbfgs_parameter();
  m_mean_f = NULL;
  SG_ADD(&m_m, "m",
         "The number of corrections to approximate the inverse hessian matrix",
         MS_NOT_AVAILABLE);
  SG_ADD(&m_max_linesearch, "max_linesearch",
         "The maximum number of trials to do line search for each L-BFGS update",
         MS_NOT_AVAILABLE);
  SG_ADD(&m_linesearch, "linesearch",
         "The line search algorithm",
         MS_NOT_AVAILABLE);
  SG_ADD(&m_max_iterations, "max_iterations",
         "The maximum number of iterations for L-BFGS update",
         MS_NOT_AVAILABLE);
  SG_ADD(&m_delta, "delta",
         "Delta for convergence test based on the change of function value",
         MS_NOT_AVAILABLE);
  SG_ADD(&m_past, "past",
         "Distance for delta-based convergence test",
         MS_NOT_AVAILABLE);
  SG_ADD(&m_epsilon, "epsilon",
         "Epsilon for convergence test based on the change of gradient",
         MS_NOT_AVAILABLE);
  SG_ADD(&m_min_step, "min_step",
         "The minimum step of the line search",
         MS_NOT_AVAILABLE);
  SG_ADD(&m_max_step, "max_step",
         "The maximum step of the line search",
         MS_NOT_AVAILABLE);
  SG_ADD(&m_ftol, "ftol",
         "A parameter used in Armijo condition",
         MS_NOT_AVAILABLE);
  SG_ADD(&m_wolfe, "wolfe",
         "A parameter used in curvature condition",
         MS_NOT_AVAILABLE);
  SG_ADD(&m_gtol, "gtol",
         "A parameter used in Morethuente linesearch to control the accuracy",
         MS_NOT_AVAILABLE);
  SG_ADD(&m_xtol, "xtol",
         "The machine precision for floating-point values",
         MS_NOT_AVAILABLE);
  SG_ADD(&m_orthantwise_c, "orthantwise_c",
         "Coeefficient for the L1 norm of variables",
         MS_NOT_AVAILABLE);
  SG_ADD(&m_orthantwise_start, "orthantwise_start",
         "Start index for computing L1 norm of the variables",
         MS_NOT_AVAILABLE);
  SG_ADD(&m_orthantwise_end, "orthantwise_end",
         "End index for computing L1 norm of the variables",
         MS_NOT_AVAILABLE);
  SG_ADD(&m_enable_newton_if_fail, "enable_newton_if_fail",
         "Enable the original Newton method if the L-BFGS method fails",
         MS_NOT_AVAILABLE);
}

CLaplacianInferenceMethodWithLBFGS::~CLaplacianInferenceMethodWithLBFGS()
{
}

} /* namespace shogun */
#endif /* HAVE_EIGEN3 */
