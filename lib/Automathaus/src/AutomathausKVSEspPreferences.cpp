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
    if (_preferences.isKey("nodeName")) {
        return _preferences.getString("nodeName", "");
    }
    return "";
}

String AutomathausKVSEspPreferences::getNodeID() {
    if (_preferences.isKey("nodeID")) {
        return _preferences.getString("nodeID", "");
    }
    return "";
}

String AutomathausKVSEspPreferences::getNodeType() {
    if (_preferences.isKey("nodeType")) {
        return _preferences.getString("nodeType", "");
    }
    return "";
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
