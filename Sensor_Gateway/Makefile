CC = g++
CFLAGS = -Wall
LDFLAGS = -lsqlite3
SRC_DIR = src
BIN_DIR = bin

GATEWAY_SRCS = $(filter-out $(SRC_DIR)/SensorSimulate/%, $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp))
SENSOR_SRCS = $(wildcard $(SRC_DIR)/SensorSimulate/*.cpp)
GATEWAY_TARGET = $(BIN_DIR)/SensorGateway
SENSOR_TARGET = $(BIN_DIR)/SensorSimulate

all: $(GATEWAY_TARGET) $(SENSOR_TARGET)

$(GATEWAY_TARGET): $(GATEWAY_SRCS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(SENSOR_TARGET): $(SENSOR_SRCS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(BIN_DIR) valgrind-out.txt

memcheck: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(TARGET) 5000

.PHONY: all clean memcheck