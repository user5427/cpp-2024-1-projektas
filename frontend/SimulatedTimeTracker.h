//
// Created by topto on 2024-05-04.
//

#ifndef CPP_2024_1_PROJEKTAS_SIMULATEDTIMETRACKER_H
#define CPP_2024_1_PROJEKTAS_SIMULATEDTIMETRACKER_H

#include <string>
#include <vector>

class SimulatedTimeTracker {
public:
    std::vector<std::string> getActionList(){
        return {"action1", "action2", "action3", "action4", "action5", "action6", "action7", "action8", "action9", "action10"};
    }

    bool isThereEventStarted(){
        return false;
    }

    bool isTherePausedEvent(){
        return false;
    }

    std::string activeEventName(){
        return "activeEvent";
    }

    long getSimulatedTime() {
        return 485181;
    }
};
#endif //CPP_2024_1_PROJEKTAS_SIMULATEDTIMETRACKER_H
