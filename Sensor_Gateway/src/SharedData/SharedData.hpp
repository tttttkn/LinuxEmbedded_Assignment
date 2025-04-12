#ifndef SHARED_DATA_HPP
#define SHARED_DATA_HPP
#include <queue>
#include <mutex>

typedef struct
{
    int sensorId;
    int sensorTemp;
    int timestamp;

} SensorData;

extern std::queue<SensorData> sensorDataQueue;

extern pthread_cond_t sharedDataCond;

extern pthread_mutex_t sharedDataMutex;

#endif // SHARED_DATA_HPP