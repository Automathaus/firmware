<script lang="ts">
    import "@fontsource/poppins";
    import NodeResetForm from '$lib/pages/NodeResetForm.svelte';
    import { ModeWatcher } from "mode-watcher";
    import Navbar from "$lib/components/ui/navbar.svelte";
    import CurveThing from "$lib/components/svg/CurveThing.svelte";

    import { automathauswebbindtest } from "$lib/automathaus/automathaus";
    import Button from "$lib/components/ui/button/button.svelte";

</script>

<ModeWatcher />
<div class="w-full min-h-svh flex items-center justify-center overflow-hidden relative">
    <NodeResetForm />
    <Button
        class="absolute top-4 left-4"
        on:click={async() => console.log(await automathauswebbindtest.addInt(2,3))}
    > Reset </Button>
    <Button
        class="absolute top-12 left-4"
        on:click={async() => console.log(await automathauswebbindtest.multiplyInt(2,3))}
    > Multiply </Button>

    <Button
        class="absolute top-20 left-4"
        on:click={async() => console.log(await automathauswebbindtest.getString())}
    > Get String </Button>

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
