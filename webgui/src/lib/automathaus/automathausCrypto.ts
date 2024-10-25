import { JSEncrypt } from 'jsencrypt';


export async function encryptData(data: string, publicKey: string): Promise<string | false> {
    const encrypt = new JSEncrypt();
    encrypt.setPublicKey(publicKey);
    const encryptedData = encrypt.encrypt(data);
    return encryptedData;
}


export async function decryptData(data: string, privateKey: string): Promise<string | false> {
    const decrypt = new JSEncrypt();
    decrypt.setPrivateKey(privateKey);
    const decryptedData = decrypt.decrypt(data);
    return decryptedData;
}




//DEBUG
// export async function sendEncryptedData(encryptedData: string): Promise<string> {
//     const response = await fetch('/sendEncryptedDataInJSON', {
//         method: 'POST',
//         headers: {
//             'Content-Type': 'application/json',
//         },
//         body: JSON.stringify({ data: encryptedData }),
//     });
//     const responseData = await response.json();
//     console.log(responseData);
//     return responseData.value;
// }

// export async function sendEncryptedDataRAW(encryptedData: string): Promise<string> {
//     const response = await fetch('/sendEncryptedBody', {
//         method: 'POST',
//         headers: {
//             'Content-Type': 'application/json',
//         },
//         body: encryptedData,
//     });
//     const responseData = await response.text();
//     return responseData;
// }