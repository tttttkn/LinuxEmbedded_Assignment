#ifndef DATA_MANAGER_HPP
#define DATA_MANAGER_HPP

#include <map>
#include <vector>
#include <queue>
#include <signal.h>

#include "../SharedData/SharedData.hpp"
#include "../ConnectionManager/ConnectionManager.hpp"

#define SENSOR_CONFIG_FILE "/home/tantaikieu/Work/LinuxEmbedded_Assignment/Sensor_Gateway/SensorConfig.csv"
typedef struct
{
    std::queue<int> recentTemps;
    float avgTemp;
    int observeRoom;
} SensorInfo;

class DataManager
{
public:
    // Constructor and Destructor
    DataManager() = default;
    ~DataManager() = default;

    bool isSensorIDValid(int sensorId);
    void init();
    void collectSensorID();
    void processSensorData();
    void calculateAvgTemp(int sensorId, int sensorTemp);

private:
    std::map<int, SensorInfo> sensorIdToSensorInfo; // Map to store sensor information
};

extern DataManager dataMgr;

#endif // DATA_MANAGER_HPP