import { defineConfig } from 'vite'
import path from "path"
import { svelte } from '@sveltejs/vite-plugin-svelte'
import { viteSingleFile } from "vite-plugin-singlefile"

// https://vitejs.dev/config/
export default defineConfig({
    plugins: [svelte(),viteSingleFile()],
    resolve: {
        alias: {
            $lib: path.resolve("./src/lib"),
        },
    },
})
