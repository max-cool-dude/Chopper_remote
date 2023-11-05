#include <Arduino.h>
#include <WIFI.h>
#include <painlessMesh.h>

////////////////////////////////////////////////////////////////////////////////
// WIFI
////////////////////////////////////////////////////////////////////////////////
#define   MESH_PREFIX     "Chopper"
#define   MESH_PASSWORD   "HelloWorld"
#define   MESH_PORT       6143

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;

uint32_t newConnection = 0;
void newConnectionCallback(uint32_t nodeId);
void receivedCallback(uint32_t from, String &msg);
bool connected = false;

void setup() {
  // WIFI SETUP
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages
  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onReceive(&receivedCallback);

}

void loop() {

  mesh.update();

  if (mesh.getNodeList().size() == 0) {
    connected = false;
  } else {
    connected = true;
  }

  Serial.print("connected: ");
  Serial.println(connected);
}

////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
////////////////////////////////////////////////////////////////////////////////
void newConnectionCallback(uint32_t nodeId) {
  newConnection = nodeId;
}

void receivedCallback(uint32_t from, String &msg) {
   Serial.printf("Received from %u msg=%s\n", from, msg.c_str());
}