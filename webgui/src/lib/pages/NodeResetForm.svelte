<script lang="ts">
    //svelte
    import { onMount } from "svelte";

    //lucide icons
    import { ArrowRight } from "lucide-svelte";
    import { Info } from 'lucide-svelte';
    import { ChartNetwork } from 'lucide-svelte';
    import { Server } from 'lucide-svelte';
    import { CircuitBoard } from 'lucide-svelte';
    import { Eye } from 'lucide-svelte';
    import { EyeOff } from 'lucide-svelte';
    import "@fontsource/poppins";
    
    //components
    import { ModeWatcher } from "mode-watcher";
    import Navbar from "$lib/components/ui/navbar.svelte";
    import Button from "$lib/components/ui/button/button.svelte";
    import CurveThing from "$lib/components/svg/CurveThing.svelte";
    import AnimAutomatLogo from "$lib/components/svg/animAutomatLogo.svelte";
    import * as Card from "$lib/components/ui/card/index.js";
    import { Input } from "$lib/components/ui/input/index.js";
    import { Label } from "$lib/components/ui/label/index.js";
    import Combobox from "$lib/components/ui/combobox.svelte";
    import LogoAutomat from "$lib/components/svg/logoAutomat.svelte";
    import { Switch } from "$lib/components/ui/switch";
    import * as Popover from "$lib/components/ui/popover";
    import ModeSelector from "$lib/components/ui/modeSelector.svelte";
    import * as Accordion from "$lib/components/ui/accordion";

    import { Toggle } from "$lib/components/ui/toggle/index.js";
    import type { WifiNetwork } from "$lib/types";

    let showPassword = false;
</script>

<div class="flex flex-col space-y-4 z-10">
    <div class="flex flex-col align-middle items-center gap-4 rounded-lg border p-6 w-[23rem] backdrop-blur-md bg-white/80 dark:bg-zinc-950/50">
        <LogoAutomat class="size-12"/>
        <div class="flex flex-col items-center space-y-1">
            <h2 class="text-lg leading-none tracking-tight">Automathaus node setup</h2>
            <p class="text-muted-foreground text-sm">Node configuration</p>
        </div>
    </div>
        

    <Card.Root class="w-[23rem] backdrop-blur-md bg-white/80 dark:bg-zinc-950/50">
        <Card.Header>
            <Card.Title>Network configuration</Card.Title>
            <Card.Description>Please connect the node to your network</Card.Description>
            </Card.Header>
        <Card.Content>
            <form>
                <div class="grid w-full items-center gap-6">
                    <div class="flex flex-col space-y-1.5">
                        <Label for="combo">Wifi network</Label>
                        <Combobox id="combo"/>
                    </div>
                    <div class="flex flex-col space-y-1.5">
                        <Label for="password">Password</Label>
                        <div class="flex items-center space-x-2">
                            <Input
                                id="password"
                                placeholder="Wifi password"
                                type="{!showPassword ? "password" : "text"}"
                                required
                            />
                            <Toggle bind:pressed={showPassword} variant="outline" class="aspect-square h-10 p-0">
                                {#if !showPassword}
                                    <Eye class="h-5 w-5"/>
                                {:else}
                                    <EyeOff class="h-5 w-5"/>
                                {/if}
                            </Toggle>
                        </div>
                    </div>

                    <div class="grid w-full items-center gap-3">
                        <Label for="mode" class="flex align-middle">
                            Select operational mode: 
                            <Popover.Root disableFocusTrap={true}>
                                <Popover.Trigger>
                                    <Info class="ml-1 h-4 w-4"/>
                                </Popover.Trigger>
                                <Popover.Content class="pt-2" sideOffset={5}>
                                    <Accordion.Root>
                                        <Accordion.Item value="item-1">
                                            <Accordion.Trigger>
                                                <Server/>
                                                Server mode
                                            </Accordion.Trigger>

                                            <Accordion.Content>
                                            The node once connected to the network will search for an automathaus server instance to connect to.
                                            </Accordion.Content>
                                        </Accordion.Item>

                                        <Accordion.Item value="item-2">
                                            <Accordion.Trigger><ChartNetwork/>Mesh mode</Accordion.Trigger>
                                            <Accordion.Content>
                                            The node will connect to other nearby nodes to form a mesh network.(WIP)
                                            </Accordion.Content>
                                        </Accordion.Item>

                                        <Accordion.Item value="item-3">
                                            <Accordion.Trigger><CircuitBoard/>Standalone mode</Accordion.Trigger>
                                            <Accordion.Content>
                                            The node will operate as a standalone device.
                                            </Accordion.Content>
                                        </Accordion.Item>
                                        
                                    </Accordion.Root>
                                </Popover.Content>
                            </Popover.Root>
                        </Label>
                        <ModeSelector />
                    </div>

                    <div class="flex items-center justify-between">
                        <span class="flex align-middle space-x-2">
                            <Label for="otherDev">Configure other nearby nodes</Label>
                            <Popover.Root>
                                <Popover.Trigger>
                                    <Info class="h-4 w-4"/>
                                </Popover.Trigger>
                                <Popover.Content sideOffset={5} class="w-[15rem]">
                                    <span class="text-sm">Try to connect to other nearby nodes to configure the wifi credentials for them.</span>
                                </Popover.Content>
                            </Popover.Root>
                        </span>
                        <Switch id="otherDev"/>
                    </div>
                </div>
            </form>
        </Card.Content>
        <Card.Footer class="flex justify-between">
            <Button class="w-full">Submit</Button>
        </Card.Footer>
    </Card.Root>
</div>