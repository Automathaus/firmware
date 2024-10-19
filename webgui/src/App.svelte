<script lang="ts">
    //svelte
    import { onMount } from 'svelte';
    import { tweened } from 'svelte/motion';
	import { cubicOut } from 'svelte/easing';
    import { blur } from 'svelte/transition';

    //style
    import "@fontsource/poppins";
    import { ModeWatcher } from "mode-watcher";

    //routes
    import NodeResetForm from '$lib/pages/NodeResetForm.svelte';

    //components
    import Navbar from "$lib/components/ui/navbar.svelte";
    import CurveThing from "$lib/components/svg/CurveThing.svelte";
    import Button from "$lib/components/ui/button/button.svelte";
    import { Progress } from "$lib/components/ui/progress";
    import CurveThingsScreen from "$lib/components/svg/CurveThingsScreen.svelte";

    //automathaus
    import { AutomathausWebBindTest } from "$lib/automathaus/automathaus";
    import AnimAutomatLogo from '$lib/components/svg/animAutomatLogo.svelte';
    import { getPublicKey, encryptData } from '$lib/automathaus/automathausCrypto';

    async function getRoute(): Promise<string>{
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

    let route = "/";

    const progress = tweened(0, { duration: 800, easing: cubicOut });

    onMount(async () => {
        progress.set(30);
        route = await getRoute();
        progress.set(100);
    });

    // async function testEncrypt(){
    //     let publicKey = await getPublicKey();
    //     let encryptedData = await encryptData(JSON.stringify({ value: "Hello World" }), publicKey);
    //     console.log(encryptedData);
    //     if(encryptedData){
    //         console.log(await sendEncryptedData(encryptedData));
    //     }
    // }

    // async function testRawEncrypt(){
    //     let publicKey = await getPublicKey();
    //     let encryptedData = await encryptData(JSON.stringify({ value: "Hello World" }), publicKey);
    //     console.log(encryptedData);
    //     if(encryptedData){
    //         console.log("data from server: " + await sendEncryptedDataRAW(encryptedData));
    //     }
    // }
</script>

<ModeWatcher />


{#if $progress < 100}
    <div class="w-full min-h-svh flex flex-col items-center justify-center bg-white dark:bg-zinc-950 z-20 fixed top-0 left-0" transition:blur={{ amount: 10 }}>
        <div class="scale-75">
            <AnimAutomatLogo />
        </div>
        <Progress class="w-24" value={$progress} max={100}/>
    </div>
{/if}


<!-- TEST BUTTONS -->
<div class="flex flex-col absolute top-4 left-4 space-y-4 z-50">
    <Button
        on:click={async() => console.log(await AutomathausWebBindTest.addInt(2,3))}
    > Add </Button>
    <Button
        on:click={async() => console.log(await AutomathausWebBindTest.multiplyInt(2,3))}
    > Multiply </Button>

    <Button
        on:click={async() => console.log(await AutomathausWebBindTest.getString())}
    > Get String </Button>

    
    <Button
    on:click={async() => console.log(await getRoute())}
    > Get Route </Button>
    
    <!-- <Button
        on:click={async() => testEncrypt()}
    > Test Encrypt </Button>

    <Button
        on:click={async() => testRawEncrypt()}
    > Test Raw Encrypt </Button> -->

    <Button
        on:click={async() => console.log(await getPublicKey())}
    > Get Public Key </Button>
</div>


<div class="w-full min-h-svh flex items-center justify-center overflow-hidden relative">

    <!-- NORMAL MODE -->
    {#if route === "/"}
        <div>
            <h1>Automathaus</h1>
        </div>
    {:else if route === "/setup"}
        <NodeResetForm />
    {/if}

    <CurveThingsScreen />
</div>
