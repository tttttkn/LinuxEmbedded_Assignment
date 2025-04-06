#ifndef DATA_MANAGER_HPP
#define DATA_MANAGER_HPP

#include <map>
#include <vector>
#include <queue>
#include "../SharedData/SharedData.hpp"

#define SENSOR_CONFIG_FILE "/home/tantaikieu/Work/LinuxEmbedded_Assignment/Sensor_Gateway/SensorConfig.csv"
typedef struct
{
    std::queue<int> recentTemps;
    float avgTemp;
    bool status;
} SensorInfo;

class DataManager
{
public:
    // Constructor and Destructor
    DataManager() = default;
    ~DataManager() = default;

    static bool isSensorIDValid(int sensorId);
    void init();
    void collectSensorID();
    void processSensorData();

private:
    std::map<int, int> sensorMap;          // Map to store sensor IDs and their corresponding room numbers
    std::map<int, SensorInfo> sensorIDMap; // Map to store sensor information
};

extern DataManager dataMgr;

#endif // DATA_MANAGER_HPP