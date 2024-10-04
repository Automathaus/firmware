<script lang="ts">
    import { ArrowRight } from "lucide-svelte";
    import { ModeWatcher } from "mode-watcher";
    import "@fontsource/poppins";

    import Navbar from "$lib/components/ui/navbar.svelte";
    import Button from "$lib/components/ui/button/button.svelte";
    import CurveThing from "$lib/components/svg/CurveThing.svelte";
    import AnimAutomatLogo from "$lib/components/svg/animAutomatLogo.svelte";
    import * as Card from "$lib/components/ui/card/index.js";
    import { Input } from "$lib/components/ui/input/index.js";
    import { Label } from "$lib/components/ui/label/index.js";
    import Combobox from "$lib/components/ui/combobox.svelte";
    import LogoAutomat from "$lib/components/svg/logoAutomat.svelte";

    const wifiNetworks = [
        {
            value: "network1",
            label: "Network 1",
            signalStrength: 3,
        },
        {
            value: "network2",
            label: "Network 2",
            signalStrength: 2,
        },
        {
            value: "network3",
            label: "Network 3",
            signalStrength: 1,
        },
    ];
</script>

<ModeWatcher />
<!-- <Navbar/> -->
<div class="w-full h-svh flex justify-center content-center overflow-hidden relative">
    <div class="flex flex-col items-center justify-center space-y-4">
        
        <div class="flex flex-col align-middle items-center gap-4 rounded-lg border p-6 w-[23rem]">
            <LogoAutomat class="size-12"/>
            <div class="flex flex-col items-center">
                <Card.Title>Automathaus node setup</Card.Title>
                <Card.Description>Node configuration</Card.Description>
            </div>
        </div>
           

        <Card.Root class="w-[23rem]">
            <Card.Content>
                <form>
                    <div class="grid w-full items-center gap-6">
                        <div class="flex flex-col space-y-1.5">
                            <Label for="name">Node name</Label>
                            <Input
                                id="name"
                                placeholder="Name of the node"
                            />
                        </div>
                        <div class="flex flex-col space-y-1.5">
                            <Label for="combo">Wifi network</Label>
                            <Combobox items={wifiNetworks} id="combo"/>
                        </div>
                        <div class="flex flex-col space-y-1.5">
                            <Label for="password">Password</Label>
                            <Input
                                id="password"
                                placeholder="Wifi password"
                                type="password"
                            />
                        </div>
                    </div>
                </form>
            </Card.Content>
            <Card.Footer class="flex justify-between">
                <Button class="w-full">Submit</Button>
            </Card.Footer>
        </Card.Root>
    </div>

    <CurveThing
        class="absolute -bottom-60 -left-60 -rotate-45 fill-zinc-900 size-[20rem] md:size-[25rem] lg:size-[27rem] xl:size-[30rem] scale-[2] dark:stroke-white dark:stroke-2"
    />
    <CurveThing
        class="absolute -bottom-80 -left-80 -rotate-45 fill-zinc-950 size-[20rem] md:size-[25rem] lg:size-[27rem] xl:size-[30rem] scale-[2.2] dark:stroke-white dark:stroke-2"
    />

    <CurveThing
        class="absolute -top-60 -right-60 rotate-[135deg] fill-zinc-900 size-[20rem] md:size-[25rem] lg:size-[27rem] xl:size-[30rem] scale-[2] dark:stroke-white dark:stroke-2"
    />
    <CurveThing
        class="absolute -top-80 -right-80 rotate-[135deg] fill-zinc-950 size-[20rem] md:size-[25rem] lg:size-[27rem] xl:size-[30rem] scale-[2.2] dark:stroke-white dark:stroke-2"
    />
</div>
