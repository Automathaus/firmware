<script lang="ts">
    import Check from "svelte-radix/Check.svelte";
    import CaretSort from "svelte-radix/CaretSort.svelte";
    import { tick } from "svelte";
    import * as Command from "$lib/components/ui/command/index.js";
    import * as Popover from "$lib/components/ui/popover/index.js";
    import { Button } from "$lib/components/ui/button/index.js";
    import { cn } from "$lib/utils.js";

    import { WifiZero } from 'lucide-svelte';
    import { WifiLow } from 'lucide-svelte';
    import { WifiHigh } from 'lucide-svelte';
    import { Wifi } from 'lucide-svelte';


    // const frameworks = [
    //     {
    //         value: "sveltekit",
    //         label: "SvelteKit",
    //     },
    //     {
    //         value: "next.js",
    //         label: "Next.js",
    //     },
    //     {
    //         value: "nuxt.js",
    //         label: "Nuxt.js",
    //     },
    //     {
    //         value: "remix",
    //         label: "Remix",
    //     },
    //     {
    //         value: "astro",
    //         label: "Astro",
    //     },
    // ];

    export let items = [];

    let open = false;
    let value = "";

    $: selectedValue =
        items.find((f) => f.value === value)?.label ??
        "Select a wifi network...";

    // We want to refocus the trigger button when the user selects
    // an item from the list so users can continue navigating the
    // rest of the form with the keyboard.
    function closeAndFocusTrigger(triggerId: string) {
        open = false;
        tick().then(() => {
            document.getElementById(triggerId)?.focus();
        });
    }
</script>

<Popover.Root bind:open let:ids id="{$$props.id}">
    <Popover.Trigger asChild let:builder>
        <Button
            builders={[builder]}
            variant="outline"
            role="combobox"
            aria-expanded={open}
            class="justify-between"
        >
            {selectedValue}
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
            <Command.Empty>No wifi network found</Command.Empty>
            <Command.Group>
                {#each items as item}
                    <Command.Item
                        value={item.value}
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
                    {item.label}

                    <Check
                        class={cn(
                            "ml-auto h-4 w-4",
                            value !== item.value && "text-transparent",
                        )}
                    />
                    </Command.Item>
                {/each}
            </Command.Group>
        </Command.Root>
    </Popover.Content>
</Popover.Root>
