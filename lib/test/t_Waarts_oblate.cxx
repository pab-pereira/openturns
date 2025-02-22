//                                               -*- C++ -*-
/**
 *  @brief The test file for Waarts oblate surface limit state
 *
 *  Copyright 2005-2022 Airbus-EDF-IMACS-ONERA-Phimeca
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include "openturns/OT.hxx"
#include "openturns/OTtestcode.hxx"

using namespace OT;
using namespace OT::Test;

int main(int, char *[])
{
  TESTPREAMBLE;
  OStream fullprint(std::cout);
  setRandomGenerator();
  try
  {

    Description inputFunction(10);
    inputFunction[0] = "S01";
    inputFunction[1] = "S02";
    inputFunction[2] = "S03";
    inputFunction[3] = "S04";
    inputFunction[4] = "S05";
    inputFunction[5] = "S06";
    inputFunction[6] = "S07";
    inputFunction[7] = "S08";
    inputFunction[8] = "S09";
    inputFunction[9] = "S10";

    Description formulas(outputFunction.getSize());
    formulas[0] = "10 - (S01^2/(1.0+1.0/10.0) + S02^2/(1.0+2.0/10.0) + S03^2/(1.0+3.0/10.0) + S04^2/(1.0+4.0/10.0) + S05^2/(1.0+5.0/10.0) + S06^2/(1.0+6.0/10.0) + S07^2/(1.0+7.0/10.0) + S08^2/(1.0+8.0/10.0) + S09^2/(1.0+9.0/10.0) + S10^2/(1.0+10.0/10.0))";

    SymbolicFunction EtatLimite(inputFunction, formulas);

    UnsignedInteger dim = EtatLimite.getInputDimension();
    fullprint << dim << std::endl;

    //   #########################################################################################################;
    //   # Probabilistic model;
    //   #########################################################################################################;

    Point mean(dim, 0.0);
    mean[0] = 0.0;
    mean[1] = 0.0;
    mean[2] = 0.0;
    mean[3] = 0.0;
    mean[4] = 0.0;
    mean[5] = 0.0;
    mean[6] = 0.0;
    mean[7] = 0.0;
    mean[8] = 0.0;
    mean[9] = 0.0;

    Point sigma(dim, 0.0);
    sigma[0] = 1.0;
    sigma[1] = 1.0;
    sigma[2] = 1.0;
    sigma[3] = 1.0;
    sigma[4] = 1.0;
    sigma[5] = 1.0;
    sigma[6] = 1.0;
    sigma[7] = 1.0;
    sigma[8] = 1.0;
    sigma[9] = 1.0;

    CorrelationMatrix CORR(dim);
    Normal myDistribution(mean, sigma, CORR);

    Point start(myDistribution.getSigma());
    CovarianceMatrix Covariance = myDistribution.getCovariance();

    //   #########################################################################################################;
    //   # Limit state;
    //   #########################################################################################################;

    RandomVector vect(myDistribution);

    CompositeRandomVector output(EtatLimite, vect);

    ThresholdEvent myEvent(output, Less(), 0.0);

    //   #########################################################################################################;
    //   # Calculs;
    //   #########################################################################################################;
    //   ;
    //   #########################################################################################################;
    //   # FORM/SORM Cobyla;
    Cobyla myCobyla;
    myCobyla.setMaximumEvaluationNumber(100 * dim);
    myCobyla.setMaximumAbsoluteError(1.0e-4);
    myCobyla.setMaximumRelativeError(1.0e-4);
    myCobyla.setMaximumResidualError(1.0e-4);
    myCobyla.setMaximumConstraintError(1.0e-4);

    FORM myAlgoC(myCobyla, myEvent, start);
    //SORM myAlgoC2(myCobyla, myEvent, start);

    myAlgoC.run();
    //myAlgoC2.run();

    FORMResult resultC(myAlgoC.getResult());
    //SORMResult resultC2(myAlgoC2.getResult());

    //   #########################################################################################################;
    //   # FORM/SORM Abdo Rackwitz;
    AbdoRackwitz myAbdoRackwitz;
    myAbdoRackwitz.setMaximumIterationNumber(100 * dim);
    myAbdoRackwitz.setMaximumAbsoluteError(1.0e-4);
    myAbdoRackwitz.setMaximumRelativeError(1.0e-4);
    myAbdoRackwitz.setMaximumResidualError(1.0e-4);
    myAbdoRackwitz.setMaximumConstraintError(1.0e-4);

    FORM myAlgoAR(myAbdoRackwitz, myEvent, start);
    //   SORM myAlgoAR2(myAbdoRackwitz, myEvent, start);

    myAlgoAR.run();
    //   myAlgoAR2.run();

    FORMResult resultAR(myAlgoAR.getResult());
    //   SORMResult resultAR2(myAlgoAR2.getResult());

    //   #########################################################################################################;
    //   # Monte Carlo;
    Scalar CoV_MC = 0.5;
    MonteCarlo myMC(myEvent);
    myMC.setMaximumOuterSampling(1000000);
    myMC.setBlockSize(1);
    myMC.setMaximumCoefficientOfVariation(CoV_MC);
    myMC.run();

    //   #########################################################################################################;
    //   # LHS;
    Scalar CoV_LHS = 0.1;
    LHS myLHS(myEvent);
    myLHS.setMaximumOuterSampling(1000000);
    myLHS.setBlockSize(1);
    myLHS.setMaximumCoefficientOfVariation(CoV_LHS);
    myLHS.run();
    /*  ;

        #########################################################################################################;

        #########################################################################################################;
        # Results;
        #########################################################################################################;

        #########################################################################################################;
        # FORM/SORM Cobyla*/;
    Scalar PfC = resultC.getEventProbability();
    Scalar Beta_generalizedC = resultC.getGeneralisedReliabilityIndex();
    Point u_starC = resultC.getStandardSpaceDesignPoint();
    Point x_starC = resultC.getPhysicalSpaceDesignPoint();
    Bool PtC = resultC.getIsStandardPointOriginInFailureSpace();
    Point gammaC = resultC.getImportanceFactors();
    Point gammaCC = resultC.getImportanceFactors(true);
    Scalar beta_hasoferC = resultC.getHasoferReliabilityIndex();
    Analytical::Sensitivity SensitivityC = resultC.getEventProbabilitySensitivity();

    //   Scalar PFBreitC2 = resultC2.getEventProbabilityBreitung();
    //   Scalar BetaBreitC2 = resultC2.getGeneralisedReliabilityIndexBreitung();
    //   Scalar PFHBC2=resultC2.getEventProbabilityHohenbichler();
    //   Scalar BetaHBC2=resultC2.getGeneralisedReliabilityIndexHohenbichler();
    //   Scalar PFTvedtC2 = resultC2.getEventProbabilityTvedt();
    //   Scalar BetaTvedtC2 = resultC2.getGeneralisedReliabilityIndexTvedt();
    //   Point CurvC2 = resultC2.getSortedCurvatures();
    //   Point u_starC2 = resultC2.getStandardSpaceDesignPoint();
    //   Point x_starC2 = resultC2.getPhysicalSpaceDesignPoint();
    //   Bool PtC2 = resultC2.getIsStandardPointOriginInFailureSpace();
    //   Point gammaC2 = resultC2.getImportanceFactors();
    //   Scalar beta_hasoferC2 = resultC2.getHasoferReliabilityIndex();

    //   #########################################################################################################;
    //   # FORM/SORM Abdo Rackwitz;
    Scalar PfAR = resultAR.getEventProbability();
    Scalar Beta_generalizedAR = resultAR.getGeneralisedReliabilityIndex();
    Point u_starAR = resultAR.getStandardSpaceDesignPoint();
    Point x_starAR = resultAR.getPhysicalSpaceDesignPoint();
    Bool PtAR = resultAR.getIsStandardPointOriginInFailureSpace();
    Point gammaAR = resultAR.getImportanceFactors();
    Point gammaCAR = resultAR.getImportanceFactors(true);
    Scalar beta_hasoferAR = resultAR.getHasoferReliabilityIndex();
    Analytical::Sensitivity SensitivityAR = resultAR.getEventProbabilitySensitivity();

    //   Scalar PFBreitAR2 = resultAR2.getEventProbabilityBreitung();
    //   Scalar BetaBreitAR2 = resultAR2.getGeneralisedReliabilityIndexBreitung();
    //   Scalar PFHBAR2=resultAR2.getEventProbabilityHohenbichler();
    //   Scalar BetaHBAR2=resultAR2.getGeneralisedReliabilityIndexHohenbichler();
    //   Scalar PFTvedtAR2 = resultAR2.getEventProbabilityTvedt();
    //   Scalar BetaTvedtAR2 = resultAR2.getGeneralisedReliabilityIndexTvedt();
    //   Point CurvAR2 = resultAR2.getSortedCurvatures();
    //   Point u_starAR2 = resultAR2.getStandardSpaceDesignPoint();
    //   Point x_starAR2 = resultAR2.getPhysicalSpaceDesignPoint();
    //   Bool PtAR2 = resultAR2.getIsStandardPointOriginInFailureSpace() ;
    //   Point gammaAR2 = resultAR2.getImportanceFactors();
    //   Scalar beta_hasoferAR2 = resultAR2.getHasoferReliabilityIndex();

    //   ######################################/*###################################################################;
    //   # Monte Carlo*/;
    SimulationResult ResultMC = myMC.getResult();
    Scalar PFMC = ResultMC.getProbabilityEstimate();
    Scalar CVMC = ResultMC.getCoefficientOfVariation();
    Scalar Variance_PF_MC = ResultMC.getVarianceEstimate();
    Scalar length90MC = ResultMC.getConfidenceLength(0.90);

    //   #########################################################################################################;
    //   # LHS;
    SimulationResult ResultLHS = myLHS.getResult();
    Scalar PFLHS = ResultLHS.getProbabilityEstimate();
    Scalar CVLHS = ResultLHS.getCoefficientOfVariation();
    Scalar Variance_PF_LHS = ResultLHS.getVarianceEstimate();
    Scalar length90LHS = ResultLHS.getConfidenceLength(0.90);

    //   #########################################################################################################;
    //   # Printting;
    //   #########################################################################################################;
    fullprint <<  "" << std::endl;
    fullprint <<  "" << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    fullprint <<  "***************************************** FORM  COBYLA *****************************************" << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    fullprint <<  "event probability =" << PfC << std::endl;
    fullprint <<  "generalized reliability index =" << Beta_generalizedC << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    for (UnsignedInteger i = 0; i < u_starC.getDimension(); i++)
      fullprint << "standard space design point =" << u_starC[i] << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    for (UnsignedInteger i = 0; i < x_starC.getDimension(); i++)
      fullprint << "physical space design point =" << x_starC[i] << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    fullprint << "is standard point origin in failure space? " << PtC << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    for (UnsignedInteger i = 0; i < gammaC.getDimension(); i++)
      fullprint << "importance factors =" << gammaC[i] << std::endl;
    for (UnsignedInteger i = 0; i < gammaCC.getDimension(); i++)
      fullprint << "importance factors (classical)=" << gammaCC[i] << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    fullprint <<  "Hasofer reliability index =" << beta_hasoferC << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    for (UnsignedInteger i = 0; i < SensitivityAR.getSize(); ++i)
      for (UnsignedInteger j = 0; j < SensitivityAR[i].getDimension(); ++j)
        fullprint <<  "Pf sensitivity =" << i << j << SensitivityC[i][j] << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    fullprint <<  "" << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    fullprint <<  "************************************** FORM ABDO RACKWITZ **************************************" << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    fullprint <<  "event probability =" << PfAR << std::endl;
    fullprint <<  "generalized reliability index =" << Beta_generalizedAR << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    for (UnsignedInteger i = 0; i < u_starAR.getDimension(); i++)
      fullprint << "standard space design point =" << u_starAR[i] << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    for (UnsignedInteger i = 0; i < x_starAR.getDimension(); i++)
      fullprint << "physical space design point =" << x_starAR[i] << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    fullprint << "is standard point origin in failure space? " << PtAR << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    for (UnsignedInteger i = 0; i < gammaAR.getDimension(); i++)
      fullprint << "importance factors =" << gammaAR[i] << std::endl;
    for (UnsignedInteger i = 0; i < gammaCAR.getDimension(); i++)
      fullprint << "importance factors (classical)=" << gammaCAR[i] << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    fullprint <<  "Hasofer reliability index =" << beta_hasoferAR << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    for (UnsignedInteger i = 0; i < SensitivityAR.getSize(); ++i)
      for (UnsignedInteger j = 0; j < SensitivityAR[i].getDimension(); ++j)
        fullprint <<  "Pf sensitivity =" << i << j << SensitivityAR[i][j] << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    fullprint <<  "" << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    fullprint <<  "***************************************** SORM  COBYLA *****************************************" << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;

    fullprint <<  "Convergence error" << std::endl;
    fullprint <<  "" << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    fullprint <<  "************************************** SORM ABDO RACKWITZ **************************************" << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    fullprint <<  "Convergence error" << std::endl;

    fullprint <<  "" << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    fullprint <<  "**************************************** MONTE CARLO *******************************************" << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    fullprint <<  "Pf estimation =" << PFMC << std::endl;
    fullprint <<  "Pf Variance estimation =" << Variance_PF_MC << std::endl;
    fullprint <<  "CoV =" << CVMC << std::endl;
    fullprint <<  "90% Confidence Interval =" << length90MC << std::endl;
    fullprint <<  "CI at 90% =[" << PFMC - 0.5 * length90MC << ";" << PFMC + 0.5 * length90MC << "]" << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    fullprint <<  "" << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    fullprint <<  "******************************************* L H S **********************************************" << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
    fullprint <<  "Pf estimation =" << PFLHS << std::endl;
    fullprint <<  "Pf Variance estimation =" << Variance_PF_LHS << std::endl;
    fullprint <<  "CoV =" << CVLHS << std::endl;
    fullprint <<  "90% Confidence Interval =" << length90LHS << std::endl;
    fullprint <<  "CI at 90% =[" << PFLHS - 0.5 * length90LHS << ";" << PFLHS + 0.5 * length90LHS << "]" << std::endl;
    fullprint <<  "************************************************************************************************" << std::endl;
  }
  catch (TestFailed & ex)
  {
    std::cerr << ex << std::endl;
    return ExitCode::Error;
  }

  return ExitCode::Success;

}
