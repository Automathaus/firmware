<script lang="ts">
    import { RefreshCw } from 'lucide-svelte';

    import Check from "svelte-radix/Check.svelte";
    import CaretSort from "svelte-radix/CaretSort.svelte";
    import { tick } from "svelte";
    import * as Command from "$lib/components/ui/command/index.js";
    import * as Popover from "$lib/components/ui/popover/index.js";
    import { Button } from "$lib/components/ui/button/index.js";
    import { cn } from "$lib/utils.js";
    import { ScrollArea } from "$lib/components/ui/scroll-area/index.js";


    import { onMount } from "svelte";

    import { WifiZero } from 'lucide-svelte';
    import { WifiLow } from 'lucide-svelte';
    import { WifiHigh } from 'lucide-svelte';
    import { Wifi } from 'lucide-svelte';

    import type { WifiNetwork } from "$lib/types";
    import { getWifiNetworks } from "$lib/automathaus/automathausWebApi";

    let items: WifiNetwork[] = [];
    let loading = true;

    let open = false;
    export let value = "";

    function closeAndFocusTrigger(triggerId: string) {
        open = false;
        tick().then(() => {
            document.getElementById(triggerId)?.focus();
        });
    }

    onMount(async () => {
        await refreshWifiNetworks();
    });

    let cooldown = 5;
    function refreshWifiNetworksCooldown() {
        cooldown = 5;
        const interval = setInterval(() => {
            cooldown--;
            if (cooldown <= 0) {
                clearInterval(interval);
            }
        }, 1000);
    }

    async function refreshWifiNetworks() {
        refreshWifiNetworksCooldown();
        loading = true;
        try {
            items = await getWifiNetworks();
        } catch (e) {
            console.error(e);
        } finally {
            loading = false;
        }
    }
</script>
<div class="flex items-center space-x-2">
    <Popover.Root bind:open let:ids disableFocusTrap={true}>
        <Popover.Trigger asChild let:builder>
            <Button
                builders={[builder]}
                variant="outline"
                role="combobox"
                aria-expanded={open}
                class="justify-between w-full"
                id="{$$props.id}"
            >
                {#if value !== ""}
                    {value}
                {:else}
                    Select a wifi network...
                {/if}
                <CaretSort class="ml-2 h-4 w-4 shrink-0 opacity-50" />
            </Button>
        </Popover.Trigger>
        <Popover.Content
            class="p-0"
            sameWidth={true}
            sideOffset={5}
        >
            <Command.Root>
                <Command.Input placeholder="Search wifi accesspoint.." class="h-9" />
                <Command.Empty>
                    {#if loading}
                        Loading wifi networks...
                    {:else}
                        No wifi network found
                    {/if}
                </Command.Empty>
                <Command.Group>
                    <ScrollArea class="max-h-32">
                        {#each items as item}
                            <Command.Item
                                value={item.ssid}
                                onSelect={(currentValue) => {
                                    value = currentValue;
                                    closeAndFocusTrigger(ids.trigger);
                                }}
                            >
                            
                            {#if item.signalStrength === 0}
                                <WifiZero class="mr-2 h-4 w-4"/>
                            {:else if item.signalStrength === 1}
                                <WifiLow class="mr-2 h-4 w-4"/>
                            {:else if item.signalStrength === 2}
                                <WifiHigh class="mr-2 h-4 w-4"/>
                            {:else}
                                <Wifi class="mr-2 h-4 w-4"/>
                            {/if}
                            {item.ssid}

                            <Check
                                class={cn(
                                    "ml-auto h-4 w-4",
                                    value !== item.ssid && "text-transparent",
                                )}
                            />
                            </Command.Item>
                        {/each}
                    </ScrollArea>
                </Command.Group>
            </Command.Root>
        </Popover.Content>
    </Popover.Root>

    <Button variant="outline" on:click={refreshWifiNetworks} class="aspect-square h-10 p-0 group" disabled={cooldown > 0}>
        {#if cooldown == 0}
            <RefreshCw class="h-4 w-4 transition-transform duration-300 group-hover:rotate-180"/>
        {:else}
            <span class="text-lg">{cooldown}</span>
        {/if}
    </Button>
</div>