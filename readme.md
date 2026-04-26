# GraphicEditor

A desktop GUI application for defining, editing, and persisting attributes and their values using the Dear ImGui.

## Key features

- Add and manage attribute descriptions
- Edit attribute values with dynamic UI controls (text entries, sliders)
- Load and save attribute schemas and values via JSON
- Template entities support (bundle + reuse attribute sets)
- Extensible type and control architecture

## Requirements

- C++20 compiler (g++-13, clang, MSVC)
- CMake >= 3.5
- OpenGL (system provided)
- GLFW (bundled in `src/glfw`)
- nativefiledialog-extended (bundled in `src/nativefiledialog-extended`)


## Attribute descriptions and attributes

### Attribute description
Attribute descriptions holds values such as name of attribute, type of attribute, range of value.

### Attribute
Attribute holds the value

## Creating an Attribute descriptions

### Creating single attribute description
An attribute description can be added via clicking `Add description` button to open window for filling neccessary information for an attribute:
1. Category
2. Attribute name
3. Attribute level (if it belongs to main entity, or to cluster attribute)
4. Attribute type

By clicking `Add description` next window will appear to fill minimum and maximum a value can be, if it is supported by the attribute type.


### Loading JSON file
Multiple attribute descriptions can be loaded via json file by following simple structure:
``` json
[
    {
        "STRING": [
                {
                    "Attribute name": "First name",
                    "Minimum": 3,
                    "Maximum": 20
                },
                {
                    "Attribute name": "Last name",
                    "Minimum": 3,
                    "Maximum": 20
                }
            ]
    },
    {
        "UINT": [
            {
                "Attribute name": "Average time to response to question(ms)",
                "Minimum": 800000,
                "Maximum": 200000000
            }
        ]
    }
]
```

Thanks to the objects of attribute type being in array, multiple definitions of the same type can be no problem.

``` json
[
    {
        "STRING": [
                {
                    "Attribute name": "First name",
                    "Minimum": 3,
                    "Maximum": 20
                }
            ]
    },
    {
        "STRING": [
                {
                    "Attribute name": "Last name",
                    "Minimum": 3,
                    "Maximum": 20
                }
            ]
    },
    {
        "UINT": [
            {
                "Attribute name": "Average time to response to question(ms)",
                "Minimum": 800000,
                "Maximum": 200000000
            }
        ]
    }
]
```

### Creating through template

Like loading multiple attribute descriptions with json file, same can be achieved with loading template entity. An entity can have single or more attribute descriptions, which can be loaded very simple. Firstly you need to create an entity, which can be done by clicking `Create templates`. The proccess is similiar to creating single attribute descriptions.

## Controls for attributes setup
To be able to change values for attributes, an control must be assigned to each attribute. This can be done by 2 options:
1. Load from json file
2. Assign control to each attribute one by one in window `Modify control types window`

### JSON file
JSON file for controls straightforward. All you need to provide is `Attribute name` and `control` (e.g. "SLIDER", "VSLIDER", "DRAG").
``` json
{
  "First name" : "TEXT",
  "Last name" : "TEXT",
  "Average time to response to question(ms)" : "SLIDER"
}
```
### GUI assign
To assign a control through GUI, choose type from dropdown menu and it will automatically create control.


## Workflow
1. Create attribute descriptions.
2. Generate attributes with button `Generate attributes`.
3. Use either load controls from json file or manually assign to each attribute control to your own liking.
4. Set values.
5. Save to json.
6. Recreate instance of `Formular` or use `Delete all` button.

## Usage in another project

1. Create instance of class `Formular`.
2. Put `showControls` and `showAttributes` methods into your main loop.

## Project structure
p
- `src/imgui`: Dear ImGui core + backend
- `src/glfw`: GLFW dependency sources
- `src/nativefiledialog-extended`: file dialog support
- - `src/nlohmannJson`: json file support
- `CMakeLists.txt`: build config

## How to extend

### Attribute descriptions and attribute types
To Add new types go to `src/libs/Headers/ImplementedDescriptions` and `src/libs/Headers/ImplementedAttributes`.
In `ImplementedDescriptions.h` you can use predefiend base class for numbers, or you don't have to use it (just remember to override all methods).
Similiar it is in `ImplementedAttributes.h`.

In `ControlComponent.h` are base classes for the final control classes (e.g. ControlComponentInt is for IntSlider, VSlider,...).
To add control for new type, you need to create base class in this header file and then you can create the spefic control class.

If you need to modify main UI behavior, you can do in in `src/libs/Sources/ControlComponents/Formular.cpp`.

> [!WARNING]
> After adding new attribute descriptions, attribute types or controls don't forget to add it to their each factories, so you can use them.


