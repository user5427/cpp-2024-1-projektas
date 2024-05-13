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
        return {"PSP veikla", "Kodavimas", "Skaitymas", "Planavimas", "Projektavimas", "Aptarimas", "Testavimas", "Kompiliavimas", "Atsiskaitymas", "Kitas veiksmas"};
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

    // Returns the duration of the current event in seconds
    long long getCurrentEventDuration(long long Time) {
        return 485181;
    }
};
#endif //CPP_2024_1_PROJEKTAS_SIMULATEDTIMETRACKER_H
