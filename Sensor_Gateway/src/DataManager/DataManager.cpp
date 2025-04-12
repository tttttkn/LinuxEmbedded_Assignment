#include "DataManager.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

void DataManager::init()
{
    collectSensorID();
}

void DataManager::collectSensorID()
{
    std::ifstream file(SENSOR_CONFIG_FILE);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << SENSOR_CONFIG_FILE << std::endl;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        int sensorId, room;
        std::vector<std::string> tokens;
        std::string token;
        while (std::getline(iss, token, ';'))
        {
            tokens.push_back(token);
        }
        if (tokens.size() == 2)
        {
            sensorId = std::stoi(tokens[0]);
            room = std::stoi(tokens[1]);
            // printf("Sensor ID: %d, Room: %d\n", sensorId, room);
            sensorMap[sensorId] = room;
        }
    }
    // printf("Total number of sensors: %zu\n", sensorMap.size());
    file.close();
}

void DataManager::processSensorData()
{
    while (true)
    {
        // Lock the mutex before accessing the shared data
        pthread_mutex_lock(&sharedDataMutex);
        if (!sensorDataQueue.empty())
        {
            SensorData data = sensorDataQueue.front();
            for (const auto &sensor : sensorMap)
            {
                if (sensor.first == data.sensorId)
                {
                    float avgTempOld = sensorIDMap[data.sensorId].avgTemp;
                    if (sensorIDMap[data.sensorId].recentTemps.size() == 5)
                    {
                        sensorIDMap[data.sensorId].avgTemp = avgTempOld + (data.sensorTemp - sensorIDMap[data.sensorId].recentTemps.back()) / 5;
                        sensorIDMap[data.sensorId].recentTemps.pop();
                    }
                    else
                    {
                        sensorIDMap[data.sensorId].avgTemp = (avgTempOld * sensorIDMap[data.sensorId].recentTemps.size() + data.sensorTemp) / (sensorIDMap[data.sensorId].recentTemps.size() + 1);
                    }
                    sensorIDMap[data.sensorId].recentTemps.push(data.sensorTemp);

                    // printf("Sensor ID: %d, Room: %d, Temperature: %d, Average Temperature: %.2f\n", data.sensorId, sensor.second, data.sensorTemp, sensorIDMap[data.sensorId].avgTemp);
                }
            }
            // Signal the condition variable to notify the StorageManager thread
            pthread_cond_signal(&sharedDataCond);
        }
        pthread_mutex_unlock(&sharedDataMutex);
    }
}

DataManager dataMgr;
