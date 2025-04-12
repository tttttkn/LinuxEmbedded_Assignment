#ifndef STORAGE_MANAGER_HPP
#define STORAGE_MANAGER_HPP

#include <sqlite3.h>
#include <iostream>
#include "../SharedData/SharedData.hpp"

class StorageManager
{
public:
    // Constructor and Destructor
    StorageManager() = default;
    ~StorageManager() = default;

    void init();
    void connectDB();
    void createTable();

    void storeSensorData();
    void storeProcess(SensorData data);

private:
    sqlite3 *db;
};

extern StorageManager storageMgr;

#endif