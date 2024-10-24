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
    strncpy(_nodeID, nodeID, 15);
}

void AutomathausKVSEspPreferences::setWifiCredentials(const char* ssid, const char* password) {
    _preferences.putString("ssid", ssid);
    _preferences.putString("password", password);
}

void AutomathausKVSEspPreferences::setOperationalMode(const char* operationalMode) {
    _preferences.putString("operationalMode", operationalMode);
}

void AutomathausKVSEspPreferences::setNodeType(const char* nodeType) {
    _nodeType = nodeType;
}

String AutomathausKVSEspPreferences::getNodeName() {
    if (_preferences.isKey("nodeName")) {
        return _preferences.getString("nodeName", "");
    }
    return "";
}

String AutomathausKVSEspPreferences::getNodeID() {
    return _nodeID;
}

String AutomathausKVSEspPreferences::getNodeType() {
    return _nodeType;
}

String AutomathausKVSEspPreferences::getWifiSSID() {
    if (_preferences.isKey("ssid")) {
        return _preferences.getString("ssid", "");
    }
    return "";
}

String AutomathausKVSEspPreferences::getWifiPassword() {
    if (_preferences.isKey("password")) {
        return _preferences.getString("password", "");
    }
    return "";
}

String AutomathausKVSEspPreferences::getOperationalMode() {
    if (_preferences.isKey("operationalMode")) {
        return _preferences.getString("operationalMode", "");
    }
    return "";
}
