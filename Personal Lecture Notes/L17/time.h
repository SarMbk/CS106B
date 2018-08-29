// Place all your headers in the header file. In the .cpp file you only need to include time.h
#include <string>

class time{

public:
    /* This is called the constructor */
    time(int hr, int min);
    void setHour(int newValue);
    void setMinute(int newValue);
    void shiftBy(int dh, int dm);
    std::string toString();
    bool isLessThan(time other);

private:
    int hour;
    int minute;
};

