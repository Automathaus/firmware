#include "AutomathausKVSEspPreferences.h"

AutomathausKVSEspPreferences::AutomathausKVSEspPreferences() {
}

AutomathausKVSEspPreferences::~AutomathausKVSEspPreferences() {
    _preferences.end();
}

bool AutomathausKVSEspPreferences::begin() {
    return _preferences.begin("automathaus", false);
}

bool AutomathausKVSEspPreferences::clearAll() {
    return _preferences.clear();
}

void AutomathausKVSEspPreferences::setNodeName(const char* nodeName) {
    _preferences.putString("nodeName", nodeName);
}

void AutomathausKVSEspPreferences::setNodeID(const char* nodeID) {
    _preferences.putString("nodeID", nodeID);
}

void AutomathausKVSEspPreferences::setWifiCredentials(const char* ssid, const char* password) {
    _preferences.putString("ssid", ssid);
    _preferences.putString("password", password);
}

void AutomathausKVSEspPreferences::setOperationalMode(const char* operationalMode) {
    _preferences.putString("operationalMode", operationalMode);
}

void AutomathausKVSEspPreferences::setNodeType(const char* nodeType) {
    _preferences.putString("nodeType", nodeType);
}

String AutomathausKVSEspPreferences::getNodeName() {
    return _preferences.getString("nodeName", "");
}

String AutomathausKVSEspPreferences::getNodeID() {
    return _preferences.getString("nodeID", "");
}

String AutomathausKVSEspPreferences::getNodeType() {
    return _preferences.getString("nodeType", "");
}

String AutomathausKVSEspPreferences::getWifiSSID() {
    return _preferences.getString("ssid", "");
}

String AutomathausKVSEspPreferences::getWifiPassword() {
    return _preferences.getString("password", "");
}

String AutomathausKVSEspPreferences::getOperationalMode() {
    return _preferences.getString("operationalMode", "");
}
