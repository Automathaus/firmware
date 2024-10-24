export type WifiNetwork = {
    signalStrength: number;
    ssid: string;
    bssid: string;
    channel: number;
    secure: string;
}

export type NodeConfig = {
    selectedNetwork: string;
    password: string;
    mode: string;
    configureOtherNodes: boolean;
}

export type NodeState = {
    nodeName: string;
    nodeType: string;
    ipAddress: string;
    macAddress: string;
    automathausServerConnected: boolean;
}