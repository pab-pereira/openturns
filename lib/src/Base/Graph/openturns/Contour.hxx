//                                               -*- C++ -*-
/**
 *  @brief Contour class for piechart plots
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
#ifndef OPENTURNS_CONTOUR_HXX
#define OPENTURNS_CONTOUR_HXX

#include "openturns/DrawableImplementation.hxx"
#include "openturns/ResourceMap.hxx"

BEGIN_NAMESPACE_OPENTURNS



/**
 * @class Contour
 *
 * The class describing a contour chart
 * Instance of Drawable
 */


class OT_API Contour : public DrawableImplementation
{
  CLASSNAME

public:
  /** Default constructor */
  Contour();

  /** Default constructor */
  Contour(const UnsignedInteger dimX,
          const UnsignedInteger dimY,
          const Sample & data,
          const String & legend = "");

  /** Constructor with parameters */
  Contour(const Sample & x,
          const Sample & y,
          const Sample & data,
          const Point & levels,
          const Description & labels,
          const Bool drawLabels = true,
          const String & legend = "");

  /** Constructor with parameters
      Contour(const Sample & xy,
      const Sample & data,
      const Point & levels,
      const Description & labels,
      const Bool drawLabels = true,
      const String & legend = ""); */

  /** String converter */
  String __repr__() const override;

  /** Accessor for first coordinate */
  Sample getX() const override;
  void setX(const Sample & x) override;

  /** Accessor for second coordinate */
  Sample getY() const override;
  void setY(const Sample & y) override;

  /** Accessor for levels */
  Point getLevels() const override;
  void setLevels(const Point & levels) override;

  /** Accessor for labels */
  Description getLabels() const override;
  void setLabels(const Description & labels) override;

  /** Accessor for drawLabels */
  Bool getDrawLabels() const override;
  void setDrawLabels(const Bool & drawLabels) override;

  /** Accessor for boundingbox */
  Interval getBoundingBox() const override;

  /** Draw method */
  String draw() const override;

  /** Clone method */
  Contour * clone() const override;

  /** Build default levels using quantiles associated with regularly spaced probability levels
   */
  void buildDefaultLevels(const UnsignedInteger number = ResourceMap::GetAsUnsignedInteger( "Contour-DefaultLevelsNumber" ));

  /** Build default labels by taking the level values */
  void buildDefaultLabels();

  /** Method save() stores the object through the StorageManager */
  void save(Advocate & adv) const override;

  /** Method load() stores the object through the StorageManager */
  void load(Advocate & adv) override;

  /** Clean all the temporary data created by draw() method */
  void clean() const override;

protected:
  /** Check fo data validity */
  void checkData(const Sample & data) const override;

private:

  /** Sample of first coordinate */
  Sample x_;

  /** Sample of second coordinate */
  Sample y_;

  /** Values of the level sets */
  Point levels_;

  /** Labels of the level sets. If none is given, it defaults to the level values. */
  Description labels_;

  /** Flag for drawing the labels */
  Bool drawLabels_;

  /** Temporary file name for the exchange with R */
  mutable String xFileName_;

  /** Temporary file name for the exchange with R */
  mutable String yFileName_;

}; /* class Contour */



END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_CONTOUR_HXX */
