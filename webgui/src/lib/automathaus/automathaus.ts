export const automathausWebReset = {
    testBinding: async(): Promise<void> => {
        try {
            let response = await fetch('/bindings/AutomathausWebReset/testBinding', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({}),
            });

            if(response.ok){
                let data = await response.json();
                console.log(data);
            }
        }catch(e){
            console.error(e);
        }
    },

    add: async(a: number, b: number): Promise<number | undefined> => {
        try {
            let response = await fetch('/bindings/AutomathausWebReset/addInt', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({a, b}),
            });

            if(response.ok){
                let data = await response.json();
                return data.returnValue;
            }
        }catch(e){
            console.error(e);
        }

        return undefined;
    }
};