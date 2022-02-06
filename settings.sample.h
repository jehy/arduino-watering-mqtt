// MQQT settings
#define MQTT_SERVER "192.168.0.5"
#define MQTT_PORT 1883
#define MQTT_USER ""
#define MQTT_PASSWORD ""

// WIFI settings
#define WIFI_SSID  "Me"             //  your network SSID (name)
#define WIFI_PASS "secure_password" // your network password
#define USE_GOOGLE_DNS false

#define WATER_STATE_TOPIC "esp/water/1/state"
#define WATER_STATUS_TOPIC "esp/water/1/status"

#define RELAY_PIN D2
#define SENSOR_PIN A0
#define PUMP_WORK_TIME 2000
#define LOOP_ITERATION 1000 * 60 * 10 // 10 minutes
#define MIN_WATERING_INTERVAL 1000 * 60 * 30 // 30 minutes
#define DRYNESS_NEED_WATER 700

#define RELAY_ON LOW // My board signals were somehow inverted o_O
#define RELAY_OFF HIGH
