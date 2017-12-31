#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

struct scoreRule{
    const int winwin = 2;
    const int beBetrayed = -1;
    const int betray = 3;
    const int doubleBetray = 0;
};
struct gameSetting{
    const int generation = 20;
    const int rounds = 5;
    const int contact = 25;
    const int Replace = 10;
    const int relative_const = 3;
    const float missRate = 0.05;
};

#endif // CONFIG_H_INCLUDED
