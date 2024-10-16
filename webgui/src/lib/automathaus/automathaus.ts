export const AutomathausWebBindTest = {
    
    testBinding: async(): Promise<void> => {
        try {
            let response = await fetch('/bindings/AutomathausWebBindTest/testBinding', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({}),
            });

            // Optionally handle the response
        } catch(e) {
            console.error(e);
        }
    },

    addInt: async(a: number, b: number): Promise<number | null> => {
        try {
            let response = await fetch('/bindings/AutomathausWebBindTest/addInt', {
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
        } catch(e) {
            console.error(e);
        }

        return null;
    },

    multiplyInt: async(a: number, b: number): Promise<number | null> => {
        try {
            let response = await fetch('/bindings/AutomathausWebBindTest/multiplyInt', {
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
        } catch(e) {
            console.error(e);
        }

        return null;
    },

    getString: async(): Promise<string | null> => {
        try {
            let response = await fetch('/bindings/AutomathausWebBindTest/getString', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({}),
            });

            if(response.ok){
                let data = await response.json();
                return data.returnValue;
            }
        } catch(e) {
            console.error(e);
        }

        return null;
    },
};


export const bindings = {
    ...AutomathausWebBindTest,
};
