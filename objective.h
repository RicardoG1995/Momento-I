#ifndef OBJECTIVE_H
#define OBJECTIVE_H

#include <string>

class Objective {
public:
    std::string description;
    bool completed;

    void check();
};

#endif // OBJECTIVE_H 