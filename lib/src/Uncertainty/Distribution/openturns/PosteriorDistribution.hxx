//                                               -*- C++ -*-
/**
 *  @brief The PosteriorDistribution distribution
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
#ifndef OPENTURNS_POSTERIORDISTRIBUTION_HXX
#define OPENTURNS_POSTERIORDISTRIBUTION_HXX

#include "openturns/OTprivate.hxx"
#include "openturns/ContinuousDistribution.hxx"
#include "openturns/ConditionalDistribution.hxx"
#include "openturns/ResourceMap.hxx"

BEGIN_NAMESPACE_OPENTURNS

/**
 * @class PosteriorDistribution
 *
 * The PosteriorDistribution distribution.
 */
class OT_API PosteriorDistribution
  : public ContinuousDistribution
{
  CLASSNAME
public:

  /** Default constructor */
  PosteriorDistribution();

  /** Parameters constructor */
  PosteriorDistribution(const ConditionalDistribution & conditionalDistribution,
                        const Sample & observations);

  /** Comparison operator */
  Bool operator ==(const PosteriorDistribution & other) const;
protected:
  Bool equals(const DistributionImplementation & other) const override;
public:

  /** String converter */
  String __repr__() const override;
  String __str__(const String & offset = "") const override;

  /* Interface inherited from Distribution */

  /** Virtual constructor */
  PosteriorDistribution * clone() const override;

  /** Get the PDF of the distribution */
  using ContinuousDistribution::computePDF;
  Scalar computePDF(const Point & point) const override;

  /** Get the CDF of the distribution */
  using ContinuousDistribution::computeCDF;
  Scalar computeCDF(const Point & point) const override;

  /** Parameters value and description accessor */
  PointWithDescriptionCollection getParametersCollection() const override;
  using ContinuousDistribution::setParametersCollection;
  void setParametersCollection(const PointCollection & parametersCollection) override;


  /* Interface specific to PosteriorDistribution */

  /** Conditional distribution accessor */
  void setConditionalDistribution(const ConditionalDistribution & conditionalDistribution);
  ConditionalDistribution getConditionalDistribution() const;

  /** Observations accessor */
  void setObservations(const Sample & observations);
  Sample getObservations() const;

  /** Log normalization factor accessor */
  Scalar getLogNormalizationFactor() const;

  /** Get the standard deviation of the distribution */
  Point getStandardDeviation() const override;

  /** Get the skewness of the distribution */
  Point getSkewness() const override;

  /** Get the kurtosis of the distribution */
  Point getKurtosis() const override;

  /** Method save() stores the object through the StorageManager */
  void save(Advocate & adv) const override;

  /** Method load() reloads the object from the StorageManager */
  void load(Advocate & adv) override;


  /** Compute the likelihood of the observations */
  Point computeLikelihood(const Point & theta) const;

  /** Compute the log-likelihood of the observations */
  Point computeLogLikelihood(const Point & theta) const;

protected:


private:

  /** Compute the numerical range of the distribution given the parameters values */
  void computeRange() override;

  /** Compute the mean of the distribution */
  void computeMean() const override;

  /** Compute the covariance of the distribution */
  void computeCovariance() const override;

  /** The underlying conditional distribution */
  ConditionalDistribution conditionalDistribution_;

  /** The observations */
  Sample observations_;

  /** The Bayes normalization constant */
  Scalar logNormalizationFactor_;

}; /* class PosteriorDistribution */


END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_POSTERIORDISTRIBUTION_HXX */
