<script lang="ts">
    import LogoAutomat from "$lib/components/svg/logoAutomat.svelte";
    import * as Card from "$lib/components/ui/card/index.js";
    import DarkmodeButton from "$lib/components/ui/darkmodeButton.svelte";
    import { Button } from "$lib/components/ui/button/index.js";
    import * as Popover from "$lib/components/ui/popover";
    import { Label } from "$lib/components/ui/label/index.js";
    import { Switch } from "$lib/components/ui/switch/index.js";
    import { toast } from "svelte-sonner";
    import * as AlertDialog from "$lib/components/ui/alert-dialog";
    import { getNodeState, setNodeName, controlLedBuiltin, restartNode } from "$lib/automathaus/automathausWebApi";
    import type { NodeState } from "$lib/types";

    import { onMount } from "svelte";

    import { Cpu } from 'lucide-svelte';
    import { Bot } from 'lucide-svelte';
    import { Router } from 'lucide-svelte';
    import { Hexagon } from 'lucide-svelte';
    import { Pencil } from 'lucide-svelte';
    import { Check } from 'lucide-svelte';
    import { Info } from 'lucide-svelte';

    import Input from "$lib/components/ui/input/input.svelte";

    let nodeState: NodeState = {
        nodeName: "Automathaus node",
        nodeType: "controller",
        ipAddress: "192.168.1.100",
        macAddress: "00:00:00:00:00:00",
        automathausServerConnected: false
    };

    let nodeNameInput = "";
    let ledBuiltinState = false;

    async function saveNodeName() {
        if(await setNodeName(nodeNameInput)){
            nodeState.nodeName = nodeNameInput;
            toast.success("Node name saved");
        }else{
            toast.error("Failed to set node name");
        }
    }

    onMount(async () => {
        nodeState = await getNodeState();
    });
</script>

<div class="flex flex-col space-y-4 z-10">
    <div class="flex flex-col align-middle items-center gap-4 rounded-lg border p-6 w-[23rem] backdrop-blur-md bg-white/80 dark:bg-zinc-950/50">
        <div class="absolute top-2 right-2">
            <DarkmodeButton/>
        </div>
        
        <LogoAutomat class="size-12"/>
        <div class="flex flex-col items-center space-y-1">
            <h2 class="text-lg leading-none tracking-tight">Automathaus node</h2>
            <p class="text-muted-foreground text-sm">Node control pannel</p>
        </div>
    </div>

    <Card.Root class="w-[23rem] backdrop-blur-md bg-white/80 dark:bg-zinc-950/50 overflow-hidden relative">
        <Card.Header>
            <Card.Title>Node information</Card.Title>
            <Card.Description>Information about this automathaus node</Card.Description>
        </Card.Header>
        <Card.Content class="space-y-3">
            <div class="flex flex-row items-center gap-5 border rounded-lg p-2 px-4">
                <span class="flex flex-row items-center gap-3">
                    {#if nodeState.automathausServerConnected}
                        <span class="relative flex h-3 w-3">
                            <span class="animate-ping absolute inline-flex h-full w-full rounded-full bg-green-400 opacity-75"></span>
                            <span class="relative inline-flex rounded-full h-3 w-3 bg-green-500"></span>
                        </span>
                        <p class="text-muted-foreground text-sm">Connected to Automathaus server</p>
                    {:else}
                        <span class="relative flex h-3 w-3">
                            <span class="animate-ping absolute inline-flex h-full w-full rounded-full bg-red-400 opacity-75"></span>
                            <span class="relative inline-flex rounded-full h-3 w-3 bg-red-500"></span>
                        </span>
                        <p class="text-muted-foreground text-[0.82rem]">Not connected to Automathaus server</p>
                    {/if}
                </span>
            </div>


            <div class="flex flex-row items-center gap-5 border rounded-lg p-2 pl-4 pr-3">
                <Bot class="size-5"/>
                <div class="flex flex-col gap-1">
                    <p class="text-muted-foreground text-sm">Node name</p>
                    <h2>{nodeState.nodeName}</h2>
                </div>

                <Popover.Root>
                    <Popover.Trigger class="ml-auto">
                        <Button variant="outline" size="icon" >
                            <Pencil class="size-4"/>
                        </Button>
                    </Popover.Trigger>
                    <Popover.Content sideOffset={8}>
                        <div class="flex flex-row gap-4">
                            <Input type="text" placeholder="Node name" bind:value={nodeNameInput}/>
                            <Popover.Close>
                                <Button size="icon" class="aspect-square" on:click={saveNodeName}>
                                    <Check class="size-4"/>
                                </Button>
                            </Popover.Close>
                        </div>
                    </Popover.Content>
                </Popover.Root>
            </div>


            <div class="flex flex-row items-center gap-5 border rounded-lg p-2 px-4">
                <Hexagon class="size-5"/>
                <div class="flex flex-col gap-1">
                    <p class="text-muted-foreground text-sm">Node type</p>
                    <h2>{nodeState.nodeType}</h2>
                </div>
            </div>
            <div class="flex flex-row items-center gap-5 border rounded-lg p-2 px-4">
                <Router class="size-5"/>
                <div class="flex flex-col gap-1">
                    <p class="text-muted-foreground text-sm">IP address</p>
                    <h2>{nodeState.ipAddress}</h2>
                </div>
            </div>
            <div class="flex flex-row items-center gap-5 border rounded-lg p-2 px-4">
                <Cpu class="size-5"/>
                <div class="flex flex-col gap-1">
                    <p class="text-muted-foreground text-sm">MAC address</p>
                    <h2>{nodeState.macAddress}</h2>
                </div>
            </div>
        </Card.Content>
        <Card.Footer class="flex-col gap-5">
            <div class="flex items-center justify-between w-full">
                <span class="flex align-middle space-x-2">
                    <Label for="otherDev">Onboard LED</Label>
                    <Popover.Root>
                        <Popover.Trigger>
                            <Info class="h-4 w-4"/>
                        </Popover.Trigger>
                        <Popover.Content sideOffset={5} class="w-[15rem]">
                            <span class="text-sm">If your board has an onboard LED, you can turn it on or off here.</span>
                        </Popover.Content>
                    </Popover.Root>
                </span>
                <Switch class="ml-auto" id="otherDev" bind:checked={ledBuiltinState} on:click={async () => await controlLedBuiltin(!ledBuiltinState)}/>
            </div>

            <AlertDialog.Root>
                <AlertDialog.Trigger asChild let:builder>
                    <Button builders={[builder]} class="w-full">Restart node</Button>
                </AlertDialog.Trigger>
                <AlertDialog.Content>
                    <AlertDialog.Header>
                        <AlertDialog.Title>Are you absolutely sure?</AlertDialog.Title>
                        <AlertDialog.Description>
                            This will reboot the automathaus node.
                        </AlertDialog.Description>
                    </AlertDialog.Header>
                    <AlertDialog.Footer>
                        <AlertDialog.Cancel>Cancel</AlertDialog.Cancel>
                        <AlertDialog.Action on:click={async () => await restartNode()}>Continue</AlertDialog.Action>
                    </AlertDialog.Footer>
                </AlertDialog.Content>
            </AlertDialog.Root>
        </Card.Footer>
    </Card.Root>
</div>