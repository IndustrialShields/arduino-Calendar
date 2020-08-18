/*
   Copyright (c) 2020 Boot&Work Corp., S.L. All rights reserved

   This library is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Calendar.h"

#define LEAP_YEAR(y) (!(((y) % 4) && (((y) % 100) || (!((y) % 400)))))
#define SECONDS_PER_MINUTE 60L
#define MINUTES_PER_HOUR 60L
#define SECONDS_PER_HOUR (SECONDS_PER_MINUTE * MINUTES_PER_HOUR)
#define HOURS_PER_DAY 24L
#define MINUTES_PER_DAY (MINUTES_PER_HOUR * HOURS_PER_DAY)
#define SECONDS_PER_DAY (SECONDS_PER_HOUR * HOURS_PER_DAY)

const uint8_t _monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

////////////////////////////////////////////////////////////////////////////////////////////////////
CalendarClass::CalendarClass() {
	setTime(0UL);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CalendarClass::update() {
	uint32_t now = millis();

	_millis += now - _lastUpdateTime;
	if (_millis >= 1000UL) {
		_timestamp += _millis / 1000UL;
		_millis = _millis % 1000UL;

		updateCalendar();
	}

	_lastUpdateTime = now;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CalendarClass::setTime(uint32_t timestamp) {
	_lastUpdateTime = millis();
	_timestamp = timestamp;
	_millis = 0UL;

	updateCalendar();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CalendarClass::updateCalendar() {
	uint32_t time = _timestamp;

	_second = time % SECONDS_PER_MINUTE;
	time /= SECONDS_PER_MINUTE;
	_minute = time % MINUTES_PER_HOUR;
	time /= MINUTES_PER_HOUR;
	_hour = time % HOURS_PER_DAY;
	time /= HOURS_PER_DAY;

	_weekDay = ((time + 4) % 7) + 1;

	_year = 1970;
	uint32_t spentDays = 0;
	while (spentDays <= time) {
		spentDays += 365;
		if (LEAP_YEAR(_year)) {
			++spentDays;
		}
		++_year;
	}
	--_year;

	spentDays -= 365;
	if (LEAP_YEAR(_year)) {
		--spentDays;
	}
	time -= spentDays;

	for (_month = 1; _month <= 12; ++_month) {
		uint8_t monthLen = _monthDays[_month - 1];
		if ((_month == 2) && LEAP_YEAR(_year)) {
			++monthLen;
		}

		if (time >= monthLen) {
			time -= monthLen;
		} else {
			break;
		}
	}
	_monthDay = time + 1;
}

void CalendarClass::setDate(uint16_t year, uint8_t month, uint8_t monthDay, uint8_t hour, uint8_t minute, uint8_t second) {
	_year = year;
	_month = month;
	_monthDay = monthDay;
	_hour = hour;
	_minute = minute;
	_second = second;

	// Spent years
    uint32_t seconds = (uint32_t(_year) - 1970L) * SECONDS_PER_DAY * 365L;
    for (uint16_t i = 1970L; i < _year; ++i) {
        if (LEAP_YEAR(i)) {
            seconds +=  SECONDS_PER_DAY;
        }
    }

    // Spent months
    for (int i = 1; i < _month; i++) {
        seconds += SECONDS_PER_DAY * uint32_t(_monthDays[i - 1]);
        if ((i == 2) && LEAP_YEAR(_year)) {
            seconds += SECONDS_PER_DAY;
        }
    }

    // Spent days
    seconds += (uint32_t(_monthDay) - 1) * SECONDS_PER_DAY;

    seconds += _hour * SECONDS_PER_HOUR;
    seconds += _minute * SECONDS_PER_MINUTE;
    seconds += _second;

	_lastUpdateTime = millis();
	_timestamp = seconds;
	_millis = 0UL;
}

CalendarClass Calendar;
