//                                               -*- C++ -*-
/**
 *  @brief PostAnalyticalControlledImportanceSampling is an implementation of the importance sampling Montex Carlo simulation method
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
#ifndef OPENTURNS_POSTANALYTICALCONTROLLEDIMPORTANCESAMPLING_HXX
#define OPENTURNS_POSTANALYTICALCONTROLLEDIMPORTANCESAMPLING_HXX

#include "openturns/PostAnalyticalSimulation.hxx"

BEGIN_NAMESPACE_OPENTURNS



/**
 * @class PostAnalyticalControlledImportanceSampling
 */

class OT_API PostAnalyticalControlledImportanceSampling :
  public PostAnalyticalSimulation
{

  CLASSNAME
public:
  /** for save/load mechanism */
  PostAnalyticalControlledImportanceSampling();

  /** Constructor with parameters */
  explicit PostAnalyticalControlledImportanceSampling(const AnalyticalResult & AnalyticalResult);

  /** Virtual constructor */
  PostAnalyticalControlledImportanceSampling * clone() const override;

  /** String converter */
  String __repr__() const override;

  /** Compute the block sample */
  Sample computeBlockSample() override;

} ; /* class PostAnalyticalControlledImportanceSampling */

END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_POSTANALYTICALCONTROLLEDIMPORTANCESAMPLING_HXX */
