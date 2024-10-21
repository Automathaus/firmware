<script lang="ts">
    import { Label } from "$lib/components/ui/label";
    import * as RadioGroup from "$lib/components/ui/radio-group";

    import { ChartNetwork } from 'lucide-svelte';
    import { Server } from 'lucide-svelte';
    import { CircuitBoard } from 'lucide-svelte';

    export let value = "";
</script>

<RadioGroup.Root bind:value={value} class="grid grid-cols-3 gap-4">
    <Label
        for="server"
        class="border-muted bg-popover hover:bg-accent hover:text-accent-foreground [&:has([data-state=checked])]:border-primary flex flex-col items-center justify-between rounded-md border-2 p-4 cursor-pointer"
    >
        <RadioGroup.Item value="server" id="server" class="sr-only" aria-label="Server" />
        <Server class="mb-3 h-6 w-6" />
        Server
    </Label>
    <Label
        for="mesh"
        class="border-muted bg-popover hover:bg-accent hover:text-accent-foreground [&:has([data-state=checked])]:border-primary flex flex-col items-center justify-between rounded-md border-2 p-4 cursor-not-allowed opacity-50"
    >
        <RadioGroup.Item value="mesh" id="mesh" class="sr-only" aria-label="Mesh" disabled/>
        <ChartNetwork class="mb-3 h-6 w-6" />
        Mesh
    </Label>
    <Label
        for="standalone"
        class="border-muted bg-popover hover:bg-accent hover:text-accent-foreground [&:has([data-state=checked])]:border-primary flex flex-col items-center justify-between rounded-md border-2 p-4 cursor-pointer"
    >
        <RadioGroup.Item value="standalone" id="standalone" class="sr-only" aria-label="Standalone" />
        <CircuitBoard class="mb-3 h-6 w-6" />
        Standalone
    </Label>
</RadioGroup.Root>

