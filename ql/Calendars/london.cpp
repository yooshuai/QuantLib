
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
/*! \file london.cpp
    \brief London calendar

    \fullpath
    Calendars/%london.cpp
*/

// $Id$

#include <ql/Calendars/london.hpp>

namespace QuantLib {

    namespace Calendars {

        bool London::LonCalendarImpl::isBusinessDay(const Date& date) const {
            Weekday w = date.weekday();
            Day d = date.dayOfMonth(), dd = date.dayOfYear();
            Month m = date.month();
            Year y = date.year();
            Day em = easterMonday(y);
            if ((w == Saturday || w == Sunday)
                // New Year's Day (possibly moved to Monday)
                || ((d == 1 || ((d == 2 || d == 3) && w == Monday)) &&
                    m == January)
                // Good Friday
                || (dd == em-3)
                // Easter Monday
                || (dd == em)
                // first Monday of May (Bank Holiday)
                || (d <= 7 && w == Monday && m == May)
                // last Monday of May or August (Bank Holidays)
                || (d >= 25 && w == Monday && (m == May || m == August))
                // Christmas (possibly moved to Monday or Tuesday)
                || ((d == 25 || (d == 27 && (w == Monday || w == Tuesday)))
                    && m == December)
                // Boxing Day (possibly moved to Monday or Tuesday)
                || ((d == 26 || (d == 28 && (w == Monday || w == Tuesday)))
                    && m == December)
                // December 31st, 1999 only
                || (d == 31 && m == December && y == 1999))
                    return false;
            return true;
        }

    }

}

