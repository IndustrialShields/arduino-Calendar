#ifndef __Calendar_H__
#define __Calendar_H__

#include <Arduino.h>

class CalendarClass {
	public:
		explicit CalendarClass();

	public:
		void update();

		// UNIX timestamp (spent seconds since Jan 1 1970 00:00:00)
		void setTime(uint32_t time);
		inline uint32_t getTime() const { return _timestamp; };

		// Calendar
		void setDate(uint16_t year, uint8_t month, uint8_t monthDay, uint8_t hour, uint8_t minute, uint8_t second);

		inline uint8_t getSecond() const { return _second; }
		inline uint8_t getMinute() const { return _minute; }
		inline uint8_t getHour() const { return _hour; }
		inline uint8_t getWeekDay() const { return _weekDay; }
		inline uint8_t getMonthDay() const { return _monthDay; }
		inline uint8_t getMonth() const { return _month; }
		inline uint16_t getYear() const { return _year; }

	private:
		void updateCalendar();

	private:
		uint8_t _second;
		uint8_t _minute;
		uint8_t _hour;
		uint8_t _weekDay;
		uint8_t _monthDay;
		uint8_t _month;
		uint16_t _year;

		uint32_t _timestamp;
		uint32_t _millis;

		uint32_t _lastUpdateTime;
};

extern CalendarClass Calendar;

#endif // __Calendar_H__
