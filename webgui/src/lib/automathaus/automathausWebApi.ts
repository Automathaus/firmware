import type { WifiNetwork, NodeConfig } from "$lib/types";
import { getPublicKey, encryptData } from "$lib/automathaus/automathausCrypto";
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