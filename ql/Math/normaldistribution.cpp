
/*
 Copyright (C) 2000, 2001, 2002 RiskMap srl

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software developed by the QuantLib Group; you can
 redistribute it and/or modify it under the terms of the QuantLib License;
 either version 1.0, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 QuantLib License for more details.

 You should have received a copy of the QuantLib License along with this
 program; if not, please email ferdinando@ametrano.net

 The QuantLib License is also available at http://quantlib.org/license.html
 The members of the QuantLib Group are listed in the QuantLib License
*/
/*! \file normaldistribution.cpp
    \brief normal, cumulative and inverse cumulative distributions

    \fullpath
    ql/Math/%normaldistribution.cpp
*/

// $Id$

#include <ql/Math/normaldistribution.hpp>

namespace QuantLib {

    namespace Math {

        const double NormalDistribution::pi_ = 3.14159265358979323846;

        // For the following formula see M. Abramowitz and I. Stegun,
        // Handbook of Mathematical Functions,
        // Dover Publications, New York (1972)

        const double CumulativeNormalDistribution::a1_ =  0.319381530;
        const double CumulativeNormalDistribution::a2_ = -0.356563782;
        const double CumulativeNormalDistribution::a3_ =  1.781477937;
        const double CumulativeNormalDistribution::a4_ = -1.821255978;
        const double CumulativeNormalDistribution::a5_ =  1.330274429;

        const double CumulativeNormalDistribution::gamma_     = 0.2316419;
        const double CumulativeNormalDistribution::precision_ = 1e-6;

        double CumulativeNormalDistribution::operator()(double x) const {
            if (x >= average_) {
                double xn = (x - average_) / sigma_;
                double k = 1.0/(1.0+gamma_*xn);
                double temp = gaussian_(xn) * k *
                                (a1_ + k*(a2_ + k*(a3_ + k*(a4_ + k*a5_))));
                if (temp<precision_) return 1.0;
                temp = 1.0-temp;
                if (temp<precision_) return 0.0;
                return temp;
            } else {
                return 1.0-(*this)(2.0*average_-x);
            }
        }




        const double InvCumulativeNormalDistribution::p0_ = 2.515517;
        const double InvCumulativeNormalDistribution::p1_ = 0.802853;
        const double InvCumulativeNormalDistribution::p2_ = 0.010328;
        const double InvCumulativeNormalDistribution::q1_ = 1.432788;
        const double InvCumulativeNormalDistribution::q2_ = 0.189269;
        const double InvCumulativeNormalDistribution::q3_ = 0.001308;

        double InvCumulativeNormalDistribution::operator()(double x) const {
            QL_REQUIRE(x>0.0 && x<1.0, "InvCumulativeNormalDistribution(" +
                DoubleFormatter::toString(x) + ") undefined: must be 0<x<1");

            if (x <= 0.5) {
                double kSquare = QL_LOG( 1 / (x*x) ) ;
                double k = QL_SQRT(kSquare);
                double rn = ((p0_ + p1_*k + p2_*kSquare) /
                            (  1  + q1_*k + q2_*kSquare + q3_*kSquare*k) - k );
                return average_ + rn*sigma_;
            } else {
                return 2.0*average_-(*this)(1.0-x);
            }
        }

    }

}
