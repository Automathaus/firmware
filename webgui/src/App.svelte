<script>
    import { ArrowRight } from 'lucide-svelte';
    import { ModeWatcher } from "mode-watcher";
    import '@fontsource/poppins';

    import Navbar from "$lib/components/ui/navbar.svelte";
    import Button from "$lib/components/ui/button/button.svelte";
    import CurveThing from '$lib/components/svg/CurveThing.svelte';
    import AnimAutomatLogo from '$lib/components/svg/animAutomatLogo.svelte';
</script>


<ModeWatcher/>
<!-- <Navbar/> -->
<div class="w-full h-svh flex justify-center content-center overflow-hidden relative">
    <div class="flex flex-col items-center justify-center space-y-6">
        <AnimAutomatLogo />
        <div class="text-center space-y-2">
            <h1 class="text-5xl lg:text-6xl">Automathaus</h1>
            <p class="text-lg">Open source domotic system</p>
        </div>
        
        <Button class="hover:scale-110 ease-in-out transition-transform	duration-300">
            Get Started
            <ArrowRight class="ml-2 h-5 w-5"/>
        </Button>
    </div>


    <CurveThing class="absolute -bottom-60 -left-60 -rotate-45 fill-zinc-900 size-[20rem] md:size-[25rem] lg:size-[27rem] xl:size-[30rem] scale-[2] dark:stroke-white dark:stroke-2" />
    <CurveThing class="absolute -bottom-80 -left-80 -rotate-45 fill-zinc-950 size-[20rem] md:size-[25rem] lg:size-[27rem] xl:size-[30rem] scale-[2.2] dark:stroke-white dark:stroke-2" />

    <CurveThing class="absolute -top-60 -right-60 rotate-[135deg] fill-zinc-900 size-[20rem] md:size-[25rem] lg:size-[27rem] xl:size-[30rem] scale-[2] dark:stroke-white dark:stroke-2" />
    <CurveThing class="absolute -top-80 -right-80 rotate-[135deg] fill-zinc-950 size-[20rem] md:size-[25rem] lg:size-[27rem] xl:size-[30rem] scale-[2.2] dark:stroke-white dark:stroke-2" />
</div>

