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

            SensorInfo sensorInfo;
            sensorInfo.observeRoom = room;
            sensorInfo.avgTemp = 0.0f;
            sensorInfo.recentTemps = std::queue<int>();

            sensorIdToSensorInfo[sensorId] = sensorInfo;
        }
    }

    file.close();
}

void DataManager::processSensorData()
{
    while (true)
    {
        pthread_mutex_lock(&sharedDataMutex);
        // Wait until there is data in the queue
        if (!sensorDataQueue.empty())
        {
            printf("sensorDataQueue size: %d\n", sensorDataQueue.size());
            // Fetch and process the data
            SensorData data = sensorDataQueue.front();
            if (isSensorIDValid(data.sensorId))
            {
                calculateAvgTemp(data.sensorId, data.sensorTemp);

                // Signal the condition variable to notify StorageManager
                pthread_cond_signal(&sharedDataCond);
                sleep(3);
            }
        }
        pthread_mutex_unlock(&sharedDataMutex);
    }
}

bool DataManager::isSensorIDValid(int sensorId)
{
    return sensorIdToSensorInfo.find(sensorId) != sensorIdToSensorInfo.end();
}

void DataManager::calculateAvgTemp(int sensorId, int sensorTemp)
{

    float avgTempOld = sensorIdToSensorInfo[sensorId].avgTemp;
    if (sensorIdToSensorInfo[sensorId].recentTemps.size() == 5)
    {
        sensorIdToSensorInfo[sensorId].avgTemp = avgTempOld + (sensorTemp - sensorIdToSensorInfo[sensorId].recentTemps.back()) / 5;
        sensorIdToSensorInfo[sensorId].recentTemps.pop();
    }
    else
    {
        sensorIdToSensorInfo[sensorId].avgTemp = (avgTempOld * sensorIdToSensorInfo[sensorId].recentTemps.size() + sensorTemp) / (sensorIdToSensorInfo[sensorId].recentTemps.size() + 1);
    }
    sensorIdToSensorInfo[sensorId].recentTemps.push(sensorTemp);

    printf("Sensor ID: %d, Temperature: %d, Average Temperature: %.2f\n", sensorId, sensorTemp, sensorIdToSensorInfo[sensorId].avgTemp);

    std::string logMessage;
    if (sensorIdToSensorInfo[sensorId].avgTemp > 30)
    {
        logMessage = "The sensor node with " + std::to_string(sensorId) + " reports it's too hot (running avg temperature = " + std::to_string(sensorIdToSensorInfo[sensorId].avgTemp) + ")";
        eventLogger.logEvent(logMessage, EventLogger::DATA_MANAGER);
        logMessage.clear();
    }
    else if (sensorIdToSensorInfo[sensorId].avgTemp < 10)
    {
        logMessage = "The sensor node with " + std::to_string(sensorId) + " reports it's too cold (running avg temperature = " + std::to_string(sensorIdToSensorInfo[sensorId].avgTemp) + ")";
        eventLogger.logEvent(logMessage, EventLogger::DATA_MANAGER);
        logMessage.clear();
    }
}
DataManager dataMgr;
