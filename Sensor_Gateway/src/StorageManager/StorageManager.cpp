#include "StorageManager.hpp"

void StorageManager::init()
{
    connectDB();
    // Create the database if it doesn't exist
    createTable();
}

void StorageManager::connectDB()
{
    int rc = sqlite3_open("sensor_data.db", &(this->db));
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    std::string logMessage = "Connection to SQL server established";
    eventLogger.logEvent(logMessage, EventLogger::STORAGE_MANAGER);
    logMessage.clear();
}

void StorageManager::createTable()
{
    const char *sql;

    sql = "CREATE TABLE IF NOT EXISTS SensorData (SensorID INT NOT NULL, SensorTemp INT NOT NULL, Timestamp INT NOT NULL);";

    int rc = sqlite3_exec(db, sql, nullptr, 0, nullptr);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }
    else
    {
        std::string logMessage = "New table SensorData created.";
        eventLogger.logEvent(logMessage, EventLogger::STORAGE_MANAGER);
        logMessage.clear();
    }
}

void StorageManager::storeSensorData()
{
    while (true)
    {
        // Lock the mutex before accessing the shared data
        pthread_mutex_lock(&sharedDataMutex);

        // Wait for the condition variable to be signaled
        printf("Waiting for sensor data...\n");
        pthread_cond_wait(&sharedDataCond, &sharedDataMutex);
        // printf("Sensor data received...\n");
        if (!sensorDataQueue.empty())
        {

            // Store the data in the database
            SensorData data = sensorDataQueue.front();
            storeProcess(data);

            printf("sensorDataQueue size1: %d\n", sensorDataQueue.size());
            sensorDataQueue.pop();
            printf("sensorDataQueue size2: %d\n", sensorDataQueue.size());

            printf("Data stored in the database...\n");
        }
        pthread_mutex_unlock(&sharedDataMutex);
        printf("Unlock mutex1...\n");
    }
}

void StorageManager::storeProcess(SensorData data)
{
    const char *sql;
    sqlite3_stmt *stmt;

    sql = "INSERT INTO SensorData (SensorID, SensorTemp, Timestamp) VALUES (?, ?, ?);";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_int(stmt, 1, data.sensorId);
    sqlite3_bind_int(stmt, 2, data.sensorTemp);
    sqlite3_bind_int(stmt, 3, data.timestamp);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
    }
    else
    {
        std::string logMessage = "Sensor data stored in the database: SensorID = " + std::to_string(data.sensorId) +
                                 ", SensorTemp = " + std::to_string(data.sensorTemp) +
                                 ", Timestamp = " + std::to_string(data.timestamp);
        eventLogger.logEvent(logMessage, EventLogger::STORAGE_MANAGER);
        logMessage.clear();
    }

    sqlite3_finalize(stmt);
}

StorageManager storageMgr;
