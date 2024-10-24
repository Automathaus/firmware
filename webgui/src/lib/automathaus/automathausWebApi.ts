import type { WifiNetwork, NodeConfig, NodeState } from "$lib/types";
import { encryptData } from "$lib/automathaus/automathausCrypto";


export async function getPublicKey(): Promise<string> {
    const response = await fetch("/getPublicKey"); 
    const publicKey = await response.text();
    return publicKey;
}

export async function restartNode(): Promise<boolean> {
    const response = await fetch("/restartNode", {
        method: 'POST'
    });
    return response.ok;
}


export async function getRoute(): Promise<string>{
    try {
        let response = await fetch('/getRoute'); 
        if(response.ok){
            let data = await response.json();
            return data.route;
        }
    } catch(e) {
        console.error(e);
    }

    return "/";
}


export async function getWifiNetworks(): Promise<WifiNetwork[]>{
    try {
        let response = await fetch('/wifiScan'); 
        if(response.ok){
            let data = await response.json();
            return data;
        }
    } catch(e) {
        console.error(e);
    }

    return [];
}


export async function setNodeConfig(config: NodeConfig): Promise<boolean>{
    let publicKey = await getPublicKey();
    let encryptedData = await encryptData(JSON.stringify(config), publicKey);
    if(encryptedData === false) return false;
    
    try {
        let response = await fetch('/setNodeConfig', {
            method: 'POST',
            body: encryptedData
        });
        if(response.ok) return true;
    } catch(e) {
        console.error(e);
    }

    return false;
}


export async function getNodeState(): Promise<NodeState>{
    try {
        const response = await fetch('/getNodeState');
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        const data = await response.json();
        return data as NodeState;
    } catch (error) {
        console.error('Error fetching node state:', error);
        return {
            nodeName: 'Unknown',
            nodeType: 'Unknown',
            ipAddress: '0.0.0.0',
            macAddress: '00:00:00:00:00:00',
            automathausServerConnected: false
        };
    }
}

export async function setNodeName(nodeName: string): Promise<boolean>{
    try {
        const response = await fetch('/setNodeName', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ nodeName: nodeName })
        });

        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }

        const result = await response.json();
        return result.returnValue === "Success";
    } catch (error) {
        console.error('Error setting node name:', error);
        return false;
    }
}

export async function controlLedBuiltin(state: boolean): Promise<boolean>{
    try {
        const response = await fetch('/controlLedBuiltin', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ state: state })
        });
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        return true;
    } catch (error) {
        console.error('Error controlling LED:', error);
        return false;
    }
}