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

## Creating an Attribute descriptions through GUI

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

## Creating an Attribute descriptions through API

### Creating single attribute description
An attribute description can be added programmatically using the `addDescription` method of the `Formular` class. You need to provide the path (category), attribute name, and attribute type:

```cpp
Formular formular;
AttributeDescription* desc = formular.addDescription("TEXT", "First name", AttributeType::STRING);
```

### Assigning control types manually
After creating attribute descriptions and generating attributes, you can assign control types manually using the `Formular` methods:

```cpp
// Generate attributes from descriptions
formular.createAttributes();

// Assign specific control types by attribute path
//If no "." delimiter is used, only main container will be searched
formular.addControlTypeByNames("Person.First name", "TEXT");
formular.addControlTypeByNames("Person.Son.Last name", "TEXT");
formular.addControlTypeByNames("Average time to response to question(ms)", "SLIDER");

// Or assign default control types
formular.addDefaultControlType("First name");

// Replace control type for existing attributes
formular.replaceControlType("First name", "DRAG");
```

### Loading JSON file
Multiple attribute descriptions can be loaded from a JSON string or object using the `loadDescriptions` method:

```cpp
nlohmann::ordered_json json = nlohmann::ordered_json::parse(jsonString);
bool success = formular.loadDescriptions(json);
```

The JSON structure should follow the same format as described in the GUI section.

### Creating through template
Templates can be created and used programmatically to bundle attribute descriptions:

```cpp
bool created = formular.createTemplateEntity("Person Template");

formular.addDescriptionToEntity("Person Template", "TEXT", "First name", AttributeType::STRING);
formular.addDescriptionToEntity("Person Template", "TEXT", "Last name", AttributeType::STRING);
formular.addDescriptionToEntity("Person Template", "UINT", "Age", AttributeType::UINT);

bool generated = formular.generateAttributesFromEntity("Person Template");
```

## Getting values
Framework supports two ways of getting values, either by extracting to JSON file or getting container of pointers to attributes with values.

### Extracting to JSON file
To save the current attributes and their values to a JSON object, use the `saveOutput` method:

```cpp
nlohmann::ordered_json output = formular.saveOutput();
// Now you can write it to a file or use it as needed
std::ofstream file("attributes_output.json");
file << output;
file.close();
```

### Getting vector of attributes
To access the attributes directly, use the `getAttributes` method which returns a vector of pointers to `Attribute` objects:

```cpp
const std::vector<Attribute*> attributes = formular.getAttributes();
for (Attribute* attr : attributes) {
    // Access attribute properties and values
    std::string name = attr->getName();
    // Get the value depending on the attribute type
    // For example, for a string attribute:
    if (attr->getType() == AttributeType::STRING) {
        std::string value = dynamic_cast<AttributeString*>(attr)->getValue();
        // Use the value...
    }
}
```

You can also retrieve a specific attribute by its path:

```cpp
Attribute* specificAttr = formular.getAttribute("First name");
if (specificAttr) {
    // Work with the specific attribute
}
```




## Workflow
1. Create attribute descriptions.
2. Generate attributes with button `Generate attributes` or via `createAttributes` method.
3. Use either load controls from json file or manually assign to each attribute control to your own liking.
4. Set values.
5. Save to json, get attribute or container of attributes.
6. Recreate instance of `Formular` or use `Delete all` button.

## Usage in another project

1. Create instance of class `Formular`.
2. Put `showControls` and `showAttributes` methods into your main loop.

## Project structure
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


