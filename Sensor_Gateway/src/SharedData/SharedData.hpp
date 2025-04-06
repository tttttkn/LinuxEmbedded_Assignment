#ifndef SHARED_DATA_HPP
#define SHARED_DATA_HPP
#include <queue>

typedef struct
{
    int sensorId;
    int sensorTemp;
    int timestamp;

} SensorData;

extern std::queue<SensorData> sensorDataQueue;

#endif // SHARED_DATA_HPP