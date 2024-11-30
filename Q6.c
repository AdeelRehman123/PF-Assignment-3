#include <stdio.h>
#include <stdlib.h>
#include <string.h> 


typedef struct {
    char cropType[50];
    char growthStage[50];
    float expectedYield;

    struct Weather *weather;
} Crop;

typedef struct Weather {
    float temperature;
    float rainfall;
    float windSpeed;
} Weather;

typedef struct {
    float soilNutrients;
    float pHLevel;
    float pestActivity;
} Sensor;

typedef struct {
    char equipmentName[50];
    int operationalStatus;
    float fuelLevel;
    char activitySchedule[100];
} Equipment;


typedef struct Field {
    float latitude;
    float longitude;
    float soilHealth;
    float moistureLevel;
    Crop *crops;
    Equipment *equipment;
    Sensor *sensors;
} Field;

typedef struct RegionHub {
    char hubName[50];
    Field *fields;
    int numFields;
    float yieldPrediction;
    float resourceDistribution;
} RegionHub;

typedef struct {
    RegionHub *regionalHubs;
    int numHubs;
} AnalyticsServer;

void initializeField(Field *field, float lat, float lon, float soilHealth, float moistureLevel);
void initializeCrop(Crop *crop, char *type, char *stage, float yield, Weather *weather);
void initializeEquipment(Equipment *equip, char *name, int status, float fuel, char *schedule);
void initializeSensor(Sensor *sensor, float nutrients, float pH, float pest);
void initializeWeather(Weather *weather, float temp, float rain, float wind);
void initializeRegionHub(RegionHub *hub, char *name, int numFields);
void initializeAnalyticsServer(AnalyticsServer *server, int numHubs);
void freeMemory(Field *field, RegionHub *hub, AnalyticsServer *server);

int main() {
    Weather weather1, weather2;
    initializeWeather(&weather1, 25.0, 100.0, 10.0);
    initializeWeather(&weather2, 22.0, 150.0, 12.0);

    Crop *crops = (Crop *)malloc(2 * sizeof(Crop));
    initializeCrop(&crops[0], "Wheat", "Vegetative", 1200.0, &weather1);
    initializeCrop(&crops[1], "Corn", "Flowering", 1500.0, &weather2);

    Sensor *sensors = (Sensor *)malloc(3 * sizeof(Sensor));
    initializeSensor(&sensors[0], 50.0, 7.0, 5.0);
    initializeSensor(&sensors[1], 48.5, 6.8, 4.0);
    initializeSensor(&sensors[2], 52.0, 7.2, 3.0);

    Equipment *equipment = (Equipment *)malloc(2 * sizeof(Equipment));
    initializeEquipment(&equipment[0], "Autonomous Tractor", 1, 80.0, "8:00 AM - 2:00 PM");
    initializeEquipment(&equipment[1], "Irrigation System", 1, 90.0, "2:00 PM - 6:00 PM");

    Field field;
    initializeField(&field, 34.0522, -118.2437, 80.5, 35.0);
    field.crops = crops;
    field.sensors = sensors;
    field.equipment = equipment;

    RegionHub hub;
    initializeRegionHub(&hub, "Central Valley", 1);
    hub.fields = &field;

    AnalyticsServer server;
    initializeAnalyticsServer(&server, 1);
    server.regionalHubs = &hub;

    printf("Field at Latitude: %.4f, Longitude: %.4f\n", field.latitude, field.longitude);
    printf("Weather for %s crop: Temp: %.2f, Rain: %.2f, Wind: %.2f\n", field.crops[0].cropType, field.crops[0].weather->temperature, field.crops[0].weather->rainfall, field.crops[0].weather->windSpeed);
    
    freeMemory(&field, &hub, &server);

    return 0;
}


void initializeField(Field *field, float lat, float lon, float soilHealth, float moistureLevel) {
    field->latitude = lat;
    field->longitude = lon;
    field->soilHealth = soilHealth;
    field->moistureLevel = moistureLevel;
}

void initializeCrop(Crop *crop, char *type, char *stage, float yield, Weather *weather) {
    strcpy(crop->cropType, type);
    strcpy(crop->growthStage, stage); 
    crop->expectedYield = yield;
    crop->weather = weather;
}

void initializeEquipment(Equipment *equip, char *name, int status, float fuel, char *schedule) {
    strcpy(equip->equipmentName, name);
    equip->operationalStatus = status;
    equip->fuelLevel = fuel;
    strcpy(equip->activitySchedule, schedule);
}

void initializeSensor(Sensor *sensor, float nutrients, float pH, float pest) {
    sensor->soilNutrients = nutrients;
    sensor->pHLevel = pH;
    sensor->pestActivity = pest;
}

void initializeWeather(Weather *weather, float temp, float rain, float wind) {
    weather->temperature = temp;
    weather->rainfall = rain;
    weather->windSpeed = wind;
}

void initializeRegionHub(RegionHub *hub, char *name, int numFields) {
    strcpy(hub->hubName, name);
    hub->numFields = numFields;
    hub->yieldPrediction = 0.0;
    hub->resourceDistribution = 0.0;
}

void initializeAnalyticsServer(AnalyticsServer *server, int numHubs) {
    server->numHubs = numHubs;
}

void freeMemory(Field *field, RegionHub *hub, AnalyticsServer *server) {
    free(field->crops);
    free(field->sensors);
    free(field->equipment);
}
