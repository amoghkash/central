# Setting up VSCode to build with the base application

## Configuring Intellisense

Intellisense is what helps the system know what the different files in your application are, as well as allowing it to know where they are located on your computer. This makes things like function, symbol, and module parsing possible (where you can click on a function or file and get taken to it's implementation). There is a very specific setup for this, and it will vary from person to person. However, there is a template provided below that you can copy and paste into your .vscode/c_cpp_properties.json file.

1. Find the path to your nrf/zephyr library. This will look something like `/home/amogh/ncs/vX.X.X` or `C:\Users\amogh\ncs\vX.X.X`. This is what will go into the places where it says INSERT PATH HERE. Remember to take out the curly brackets.


```json
{
    "configurations": [
        {
            "name": "Default",
            "compileCommands": [
                "${workspaceFolder}/build/compile_commands.json"
            ],
            "includePath": [
                "${workspaceFolder}/**",
                "{INSERT PATH HERE}/nrf/include/**",
                "{INSERT PATH HERE}/zephyr/include/zephyr/**",
                "{INSERT PATH HERE}/modules/**"
            ],
            "defines": [],
            "configurationProvider": "nordic-semiconductor.nrf-connect"
        }
    ],
    "version": 4
}
```
