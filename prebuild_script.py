import os
import subprocess
from platformio import util

Import("env")

def escape_string(s):
    return s.replace('\\', '\\\\').replace('"', '\\"').replace('\n', '\\n')

def build_vite_and_generate_header():
    # Get project directories
    project_dir = env.get('PROJECT_DIR', os.getcwd())
    webgui_dir = os.path.join(project_dir, 'webgui')
    dist_dir = os.path.join(webgui_dir, 'dist')
    include_dir = os.path.join(project_dir, 'lib', 'Automathaus', 'src')
    
    # Ensure the include directory exists
    os.makedirs(include_dir, exist_ok=True)
    
    print("Building Vite project...")
    # Run npm build in the webgui directory
    subprocess.run(['npm', 'run', 'build'], cwd=webgui_dir, check=True)
    
    # Read the generated index.html
    index_html_path = os.path.join(dist_dir, 'index.html')
    with open(index_html_path, 'r') as f:
        html_content = f.read()
    
    # Generate the header file content
    header_content = f"""
#ifndef WEBGUI_H
#define WEBGUI_H

#include <pgmspace.h>

// The HTML content from the Vite build
const char INDEX_HTML[] PROGMEM = R"=====(
{html_content}
)=====";

#endif // WEBGUI_H
"""
    
    # Write the header file
    header_path = os.path.join(include_dir, 'webgui.h')
    with open(header_path, 'w') as f:
        f.write(header_content)
    
    print(f"Generated header file at {header_path}")

# Register the pre-build script
# env.AddPreAction("buildprog", build_vite_and_generate_header)
build_vite_and_generate_header()