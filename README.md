# Tau
τ ([lowercase Greek letter tau](https://en.wikipedia.org/wiki/Tau)) - file format for data interchange. Tau is structurized, text-represented and human-readable. The main goals of the format is:
* Improve readability by allowing more flexible syntax rules than other formats
* Simplify the process of editing the file by humans
* Provide data structures that can be used to simplify serialization process

## Quick examples

### Rectangle
```
map (
    "Left"      :      0,
    "Top"       :    256,
    "Right"     :  4 096,
    "Bottom"    : 32 768,
)
```

### List of characters
```
array (
    map (
        "Name"          : "John",
        "Surname"       : "Connor",
        "Description"   :
            "Born on 28 February 1985, lead the Resistance to defeat an "
            "empire of robotic Terminators amassed by Skynet."
    ),
    map (
        "Name"          : "Terminator",
        "Surname"       : "T-800",
        "Description"   :
            "A Cyberdyne Systems series T-800 Model 101 Terminator with "
            "living tissue over a metal endoskeleton. The Terminator CPU "
            "is an artificial neural network with the ability to learn "
            "and adapt."
    ),
    map (
        "Name"          : "Evil Terminator",
        "Surname"       : "T-1000",
        "Description"   :
            "More advanced Terminator, composed entirely of a \"mimetic "
            "polyalloy\", rendering it capable of rapid shape shifting, "
            "near-perfect mimicry and rapid recovery from damage."
    ),
)
```
### Hierarchical windows
```
'main window' map (
    "Title"         : "window",
    "Visibility"    : true,
    "Parent"        : none,
    "Childs"        : array (
        map (
            "Title"         : "Nested window",
            "Visibility"    : true,
            "Parent"        : 'main window',
            "Childs"        : array (),
        )
        map (
            "Title"         : "Hidden window",
            "Visibility"    : false,
            "Parent"        : 'main window',
            "Childs"        : array (),
        )
    ),
)
```

## Syntax

### Comments
_TODO_

### Entities
Here is a complete list of the classes supported in Tau:
- Empty object
- Primitives
  - Booleans
  - Numbers
  - Strings
- Containers
  - Set
  - Array
  - Map
- Binary data types
  - Hex
  - Base64
  - Raw

#### None
Empty object or _none_ represents nothing and may be used as ```null``` in JSON. _None_ should be written like this:
```
none
```

#### Booleans
Booleans represents logical true and false statements and should be written like this:
```
true
false
```

#### Numbers
Numbers is represented by integers and real numbers, dot (.) is used to separate fractional part:
```
1
5.0
123.456
```
Numbers may have optional preceding plus or minus sign:
```
+100
-500
```
Spaces inside numbers are ignored:
```
   10 000
  150 000
1 000 000
```
Binary and hex numbers are also suported:
```
101b    `/ 5
101B    `/ 5
16h     `/ 22
1 234 h `/ 4660
```

#### Strings






