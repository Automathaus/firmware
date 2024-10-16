import os
import subprocess
import re
from platformio import util

Import("env")

# Get project directories
project_dir = env.get('PROJECT_DIR', os.getcwd())
webgui_dir = os.path.join(project_dir, 'webgui')
dist_dir = os.path.join(webgui_dir, 'dist')
automathaus_src_dir = os.path.join(project_dir, 'lib', 'Automathaus', 'src')

def find_header_files(src_directory):
    header_files = []
    for root, dirs, files in os.walk(src_directory):
        for file in files:
            if file.endswith('.h') or file.endswith('.hpp'):
                header_files.append(os.path.join(root, file))
    return header_files

def extract_classes(header_content):
    # Regex to find classes that extend AutomathausWebBindings
    class_pattern = re.compile(r'class\s+(\w+)\s*:\s*public\s+AutomathausWebBindings\s*{')
    classes = class_pattern.findall(header_content)
    return classes

def generate_cpp_handler(return_type, method_name, params, class_name):
    handler_code = ""

    if return_type == 'void':
        # Handle void functions
        handler_code += f"""    // Void function case for {class_name}::{method_name}
    _server.on("/bindings/{class_name}/{method_name}", HTTP_POST, [](AsyncWebServerRequest *request) {{
        {class_name}::{method_name}();
        request->send(200, "text/plain", "{{\\"returnValue\\": null}}");
    }},
    NULL,
    AutomathausWebBindings::handleBody);\n\n"""
    else:
        # Handle functions with return values
        handler_code += f"""    // Function with return value case for {class_name}::{method_name}
    _server.on("/bindings/{class_name}/{method_name}", HTTP_POST, [](AsyncWebServerRequest *request) {{ 
        JsonDocument doc;

        DeserializationError error = deserializeJson(doc, request->_tempObject);
        if (error) {{
            Serial.println(error.c_str());
            request->send(400, "application/json", "{{\\"returnValue\\": \\"Invalid JSON\\"}}");
            return;
        }}

"""

        # Extract parameters
        param_pairs = [p.strip().rsplit(' ', 1) for p in params.split(',') if p.strip()]
        types, names = zip(*param_pairs) if param_pairs else ([], [])

        for i, (ptype, pname) in enumerate(zip(types, names), start=1):
            handler_code += f"""        {ptype} v{i} = 0;
        if (doc["{pname}"].is<{ptype}>()) {{
            v{i} = doc["{pname}"].as<{ptype}>();
        }} else {{
            request->send(400, "application/json", "{{\\"error\\": \\"Invalid or missing '{pname}' parameter\\"}}");
            return;
        }}

"""
        if return_type == 'std::string':
            # Generate the call and response
            handler_code += f"""        auto returnValue = {class_name}::{method_name}({', '.join([f'v{i}' for i in range(1, len(names)+1)])});

        std::string response = "{{\\"returnValue\\": \\"" + returnValue + "\\"}}";
        request->send(200, "application/json", response.c_str());
    }},
    NULL,
    AutomathausWebBindings::handleBody);\n\n"""
        else:
            # Generate the call and response
            handler_code += f"""        auto returnValue = {class_name}::{method_name}({', '.join([f'v{i}' for i in range(1, len(names)+1)])});

        std::string response = "{{\\"returnValue\\": " + std::to_string(returnValue) + "}}";
        request->send(200, "application/json", response.c_str());
    }},
    NULL,
    AutomathausWebBindings::handleBody);\n\n"""

    return handler_code

def generate_cpp_bindings(header_content, class_name):
    methods = re.findall(r'static\s+([\w<>]+(?:\s*::\s*\w+)?)\s+(\w+)\s*\((.*?)\)', header_content)

    cpp_bindings = ""

    for return_type, method_name, params in methods:
        cpp_bindings += generate_cpp_handler(return_type, method_name, params, class_name)

    return cpp_bindings

def generate_ts_bindings(header_content, class_name):
    # Mapping from C++ types to TypeScript types
    type_mapping = {
        'int': 'number',
        'float': 'number',
        'double': 'number',
        'bool': 'boolean',
        'std::string': 'string',
        'string': 'string',
        # Add more mappings as needed
    }

    methods = re.findall(r'static\s+([\w<>]+(?:\s*::\s*\w+)?)\s+(\w+)\s*\((.*?)\)', header_content)

    ts_bindings = f"""export const {class_name} = {{
    """

    for return_type, method_name, params in methods:
        param_pairs = [p.strip().rsplit(' ', 1) for p in params.split(',') if p.strip()]
        types, names = zip(*param_pairs) if param_pairs else ([], [])

        # Map C++ types to TypeScript types
        ts_types = [type_mapping.get(ptype, 'any') for ptype in types]
        ts_params = ', '.join([f"{name}: {ttype}" for name, ttype in zip(names, ts_types)])
        if return_type == 'void':
            ts_return_type = 'void'
        else:
            ts_return_type = f'{type_mapping.get(return_type, "any")} | null'

        ts_bindings += f"""
    {method_name}: async({ts_params}): Promise<{ts_return_type}> => {{
        try {{
            let response = await fetch('/bindings/{class_name}/{method_name}', {{
                method: 'POST',
                headers: {{
                    'Content-Type': 'application/json',
                }},
                body: JSON.stringify({{{', '.join(names)}}}),
            }});
"""

        if return_type != 'void':
            ts_bindings += f"""
            if(response.ok){{
                let data = await response.json();
                return data.returnValue;
            }}
"""
        else:
            # For void functions, no need to check response.ok
            ts_bindings += """
            // Optionally handle the response
"""

        ts_bindings += f"""        }} catch(e) {{
            console.error(e);
        }}
"""
        if return_type != 'void':
            ts_bindings += """
        return null;
"""
        ts_bindings += "    },\n"

    ts_bindings += "};\n"
    return ts_bindings






def generate_bindings():
    src_directory = automathaus_src_dir
    cpp_binding_dir = os.path.join(automathaus_src_dir, 'generated')
    ts_binding_dir = os.path.join(webgui_dir, 'src', 'lib', 'automathaus')

    header_files = find_header_files(src_directory)
    all_cpp_bindings = """#include <ArduinoJson.h>
#include "AutomathausAsyncWebServer.h"
"""

    # Collect unique class headers to include
    included_headers = set()

    all_cpp_bindings += "\nvoid AutomathausAsyncWebServer::setGeneratedBindings() {\n\n"

    all_ts_bindings = ""
    ts_included_classes = set()

    for header_file in header_files:
        with open(header_file, 'r') as file:
            header_content = file.read()

        classes = extract_classes(header_content)
        for class_name in classes:
            cpp_binding = generate_cpp_bindings(header_content, class_name)
            ts_binding = generate_ts_bindings(header_content, class_name)

            all_cpp_bindings += cpp_binding
            all_ts_bindings += ts_binding + "\n"

            # Add the header file to the include list
            header_filename = os.path.basename(header_file)
            included_headers.add(header_filename)

    # Add class-specific includes
    for header in sorted(included_headers):
        all_cpp_bindings = f'#include "{header}"\n' + all_cpp_bindings

    all_cpp_bindings += "}\n"

    with open(os.path.join(cpp_binding_dir, 'generatedBindings.cpp'), 'w') as file:
        file.write(all_cpp_bindings)

    # Combine all TypeScript bindings into a single file with separate objects
    all_ts_bindings += "\nexport const bindings = {\n"
    for header_file in header_files:
        with open(header_file, 'r') as file:
            header_content = file.read()
        classes = extract_classes(header_content)
        for class_name in classes:
            all_ts_bindings += f"    ...{class_name},\n"
    all_ts_bindings += "};\n"

    with open(os.path.join(ts_binding_dir, 'automathaus.ts'), 'w') as file:
        file.write(all_ts_bindings)






def escape_string(s):
    return s.replace('\\', '\\\\').replace('"', '\\"').replace('\n', '\\n')

def build_vite_and_generate_header():
    # Ensure the include directory exists
    os.makedirs(automathaus_src_dir, exist_ok=True)
    
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
    header_path = os.path.join(automathaus_src_dir, 'generated', 'webgui.h')
    with open(header_path, 'w') as f:
        f.write(header_content)
    
    print(f"Generated header file at {header_path}")

# Register the pre-build script
# env.AddPreAction("buildprog", build_vite_and_generate_header)
generate_bindings()
build_vite_and_generate_header()