#include "AutomathausKVSEspPreferences.h"

AutomathausKVSEspPreferences::AutomathausKVSEspPreferences() {
}

AutomathausKVSEspPreferences::~AutomathausKVSEspPreferences() {
    _preferences.end();
}

void AutomathausKVSEspPreferences::begin() {
    _preferences.begin("automathaus", false);
}

void AutomathausKVSEspPreferences::clearAll() {
    _preferences.clear();
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

const char* AutomathausKVSEspPreferences::getNodeName() {
    return _preferences.getString("nodeName", "").c_str();
}

const char* AutomathausKVSEspPreferences::getNodeID() {
    return _preferences.getString("nodeID", "").c_str();
}

const char* AutomathausKVSEspPreferences::getNodeType() {
    return _preferences.getString("nodeType", "").c_str();
}

const char* AutomathausKVSEspPreferences::getWifiSSID() {
    return _preferences.getString("ssid", "").c_str();
}

const char* AutomathausKVSEspPreferences::getWifiPassword() {
    return _preferences.getString("password", "").c_str();
}

const char* AutomathausKVSEspPreferences::getOperationalMode() {
    return _preferences.getString("operationalMode", "").c_str();
}
