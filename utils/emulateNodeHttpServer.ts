import express, { Request, Response } from "npm:express";
import { Buffer } from "node:buffer";
import cors from "npm:cors";

const app = express();
const port: number = 8080;

app.use(cors());
app.use(express.json()); // Add this line to parse JSON bodies

type NodeState = {
    nodeName: string;
    nodeType: string;
    ipAddress: string;
    macAddress: string;
    automathausServerConnected: boolean;
}

const nodeState: NodeState = {
    nodeName: "Automathaus node",
    nodeType: "controller",
    ipAddress: "192.168.1.100",
    macAddress: "00:00:00:00:00:00",
    automathausServerConnected: true
};

app.get("/getNodeState", (req: Request, res: Response): void => {
    res.json(nodeState);
});

app.post("/setNodeName", (req: Request, res: Response): void => {
    nodeState.nodeName = req.body.nodeName;
    res.json({ success: true });
});

app.post("/controlLedBuiltin", (req: Request, res: Response): void => {
    console.log(req.body.state);
    res.json({ success: true });
});




// Routes
app.get("/getRoute", (req: Request, res: Response): void => {
    res.json({ route: "/" });
});

app.get("/wifiScan", (req: Request, res: Response): void => {
    const wifiNetworks = [
        {
            signalStrength: 4,
            ssid: "HomeNetwork",
            bssid: "00:11:22:33:44:55",
            channel: 6,
            secure: "WPA2-PSK"
        },
        {
            signalStrength: 3,
            ssid: "OfficeWiFi",
            bssid: "AA:BB:CC:DD:EE:FF",
            channel: 11,
            secure: "WPA/WPA2-PSK"
        },
        {
            signalStrength: 2,
            ssid: "GuestNetwork",
            bssid: "11:22:33:44:55:66",
            channel: 1,
            secure: "Open"
        },
        {
            signalStrength: 1,
            ssid: "SecureNet",
            bssid: "BB:CC:DD:EE:FF:00",
            channel: 3,
            secure: "WPA2-Enterprise"
        }
    ];

    res.json([...wifiNetworks, ...wifiNetworks, ...wifiNetworks]);
});


app.get("/getPublicKey", (req: Request, res: Response): void => {
    const publicKey = "-----BEGIN PUBLIC KEY-----\n" +
        "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAotQFOqrrcmk+nVoo3dh0\n" +
        "faR85uLVcDHiN6hM7G9wcl90qOkoap9iRq24rTnp2dgj0BGCYUSFMA/7qBpY1aB7\n" +
        "tjsJ5d9JC1U0raFjTfKf7u7bdhEzptR6Vm7Jo04hUgCHbEQ9NqdAhQjfjGv0s8l0\n" +
        "SbY/ah1s2OaQPvNi30YqLSCcy0LGUF5xaFJ0eRZMlxXIUGV1EmNJLsTUSa79iXL/\n" +
        "MVU0WgujGmTdkSMQI/99KD/DhoLNnUdD7N8U+qTnDj2gd5LxEWlvbt7XTx+GPoaQ\n" +
        "xa68UoPbkujPc+vtIDWDG8iR8LVLjJtQtO+HXWrIGCeRaWy47CSih/h05AFTa8DR\n" +
        "FQIDAQAB\n" +
        "-----END PUBLIC KEY-----";

    res.send(publicKey);
});

app.post("/setNodeConfig", (req: Request, res: Response): void => {
    let rawBody = '';
    req.on('data', (chunk: Buffer) => {
        rawBody += chunk.toString();
    });
    req.on('end', () => {
        console.log('Raw body:', rawBody);
    });

    res.json({ success: true });
});



// Start the server
app.listen(port, () => {
    console.log(`Server running on http://localhost:${port}`);
});