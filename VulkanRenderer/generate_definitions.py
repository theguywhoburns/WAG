import re

bindings_file = 'src/renderer_interface_bindings.rs'
output_file = 'src/generated.rs'

# Regular expression to find function declarations in the bindings
function_regex = re.compile(r'pub fn (\w+)\((.*?)\)(?: -> (.+?))?;', re.DOTALL)

argument_regex = re.compile(r'(\w*): [^,]*,?', re.MULTILINE)

generated_definitions = []
with open(bindings_file, 'r') as f:
    contents = f.read()

    # Find all function declarations
    functions = function_regex.findall(contents)
    generated_definitions.append('#![allow(non_snake_case)]')
    generated_definitions.append('#![allow(non_camel_case_types)]')
    generated_definitions.append('#![allow(non_upper_case_globals)]')
    generated_definitions.append('use crate::renderer_interface_bindings::*;')
    generated_definitions.append('use crate::vulkan::{self};')

    for func_name, args, ret_type in functions:
        func_name = func_name if not func_name.startswith('_PFN') else func_name[4:]
        ret_type = ret_type if ret_type else '()'  # Use () for void functions
        args = args if args else ''  # If no args, leave it empty

        # Generate Rust function definitions with placeholders
        generated_definitions.append(f'#[no_mangle]')
        generated_definitions.append(f'pub unsafe extern "C" fn {func_name}({args}) -> {ret_type} ' + '{')
        arguments = argument_regex.findall(args)
        call_str = f'\tvulkan::{func_name}('
        for arg in arguments:
            call_str += f'{arg}, '
        if call_str.endswith(', '): generated_definitions.append(call_str[:-2] + ')')
        else: generated_definitions.append(call_str + ')')
        generated_definitions.append('}')

# Write the generated function definitions to a file
with open(output_file, 'w') as f:
    f.write('\n'.join(generated_definitions))

print(f"Generated Rust function definitions in {output_file}")