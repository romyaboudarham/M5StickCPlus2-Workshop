#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <M5StickCPlus2.h>

class Clock {
public:
    void initializeRTC() {
        StickCP2.Rtc.begin();
    }

    void setManualTime(int year, int month, int day, int hour, int minute, int second) {
        m5::rtc_date_t date = { year, (uint8_t)month, (uint8_t)day };
        m5::rtc_time_t time = { (uint8_t)hour, (uint8_t)minute, (uint8_t)second };
        StickCP2.Rtc.setDateTime(m5::rtc_datetime_t{ date, time });
    }

    void updateDisplay() {
        m5::rtc_datetime_t dt = StickCP2.Rtc.getDateTime();
        StickCP2.Display.setCursor(0, 0);
        StickCP2.Display.setTextSize(2);
        StickCP2.Display.printf("%04d-%02d-%02d\n%02d:%02d:%02d",
                                dt.date.year, dt.date.month, dt.date.date,
                                dt.time.hours, dt.time.minutes, dt.time.seconds);
    }
};

#endif // CLOCK_HPP
