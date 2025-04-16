#include "SharedData.hpp"

pthread_mutex_t sharedDataMutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t sharedDataCond = PTHREAD_COND_INITIALIZER;

std::queue<SensorData> sensorDataQueue = std::queue<SensorData>();
