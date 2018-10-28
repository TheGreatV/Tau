# Tau
τ ([lowercase Greek letter tau](https://en.wikipedia.org/wiki/Tau)) - notation system for representing commonly used data types, such as numbers, strings, collections or structures. The main Tau goals is:
* Improve readability by allowing more flexible syntax rules than other formats
* Simplify the process of editing the file by humans
* Provide data structures that can be used to simplify serialization process

# Quick examples

## Rectangle
```
map (
    "Left"      :      0,
    "Top"       :    256,
    "Right"     :  4 096,
    "Bottom"    : 32 768,
)
```

## List of characters
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
## Hierarchical windows
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

# Syntax

## Comments
_TODO_

## Entities
Tau supports the following types of objects:
- Empty objects
    - None
    - Unique
- Primitives
    - Booleans
    - Numbers
    - Strings
- Containers
    - Set
    - Array
    - Map
    - Dictionary
- Binaries
    - Hex
    - Base64
    - Raw

### Empty Objects

#### None
```
none
```
Similarly to ```null``` in JSON or some programming languages, _none_ represents _nothing_ and may be used to denote undefined, unspecified or default values.

#### Unique
```
unique
```
_Unique_ object represents the entity which is defferent from any other entity including other _unique_ objects. _Unique_ is quite similar to ```Symbol()``` in JavaScript. It represents something that has the only one purpose: guarantee to have unique value. Because of this property, _unique_ may be used in containers without any possibility to be overlapped (unlike numbers).

### Primitives

### Booleans
```
true
false
```
_Booleans_ represents logical _true_ and _false_ statements and may be used for representing values which may have only two possible states.

### Numbers
_Numbers_ is represented by integers and real numbers, [dot (".")](https://en.wikipedia.org/wiki/Decimal_separator) is used to separate fractional part:
```
1
5.0
123.456
```
_Numbers_ may have optional preceding plus or minus sign:
```
+100
-500
```
Spaces (including tabs and line breaks) inside _numbers_ are ignored:
```
   10 000
  150 000
1 000 000
```
[Binary](https://en.wikipedia.org/wiki/Binary_number) and [hex](https://en.wikipedia.org/wiki/Hexadecimal) _numbers_ are also suported:
```
101b    `/ 5
101B    `/ 5
16h     `/ 22
1 234 h `/ 4660
```

### Strings
_Strings_ in Tau are placed inside double quotes, [backslash](https://en.wikipedia.org/wiki/Backslash) is used for [escaping](https://en.wikipedia.org/wiki/Escape_character):
```
"text"
"text with \" double quotes"
```
_Strings_ placed next to each other will [concatenate](https://en.wikipedia.org/wiki/Concatenation):
```
"snow" "ball" `/ result into: "snowball"
```

### Containers
Containers is used to store other entities regardless of their type.
Containers may be ordered or unordered, and some of them may require an element to be unique.
Container may be declared by placing [round brackets](https://en.wikipedia.org/wiki/Bracket) after its name and separating the elements inside of this braces with [commas](https://en.wikipedia.org/wiki/Comma):
```
container (element_1, element_2, element_3)
```
Any spaces between a container name (which is case sensitive), brackets and commas are ignored, additional comma after the last element is allowed:
```
container()         `/ OK
container ()        `/ OK
container           `/ OK
(                   `/ OK
)                   `/ OK
container(1, 2, 3,) `/ OK
```
Declaring an empty container with one (```set (,)```) or several commas (```set (,,,)```) is not specified yet and is under discussion.
The situation when the container which require unique elements contains two objects with same value is treated as an error with [undefined behavior](https://en.wikipedia.org/wiki/Undefined_behavior).

#### Set
_Set_ is an unordered container, which stores unique elements:
```
set (1, 2, 3)
```
_Sets_ may be used to describe a relation between two objects, when one of them either not include the other one or include it only once. For example, membership of persons in some organization may be described as an _set_ of this persons with guarantee to include each of them not more than once:
```
set ("John", "Bob", "Andrew") `/ set of participants
```

#### Arrays
_Array_ is an ordered container. The elements may appear inside the container more than once:
```
array (1, 2, 3, 1, 2)
```

#### Maps
_Map_ is an unordered container, which stores pairs of unique keys and not unique values. This pairs are declaring using colon ([":"](https://en.wikipedia.org/wiki/Colon_(punctuation))) operator:
```
map ("first" : 1, "second" : 2, "third" : 3)
```
Having different pairs sharing the same key is treated as an error with undefined behavior:
```
map (
    "first" : 1,
    "first" : 2,    `/ error, key "first" is already used 
)
```
Unlike JSON, any object may be used as an key:
```
map (
    "first"         : 1,    `/ string key
    none            : 2,    `/ none key
    true            : 3,    `/ boolean key
    4               : 4,    `/ number key
    set ()          : 5,    `/ set key
    array ()        : 6,    `/ array key
    map ()          : 7,    `/ map key
)
```
_Maps_ may be useful to describe wide range of relations between objects. For instance, they may index numerical values of hexadecimal characters:
```
map (
    "0" : 0,
    "1" : 1,
    "2" : 2,
    "3" : 3,
    "4" : 4,
    "5" : 5,
    "6" : 6,
    "7" : 7,
    "8" : 8,
    "9" : 9,
    "A" : 10,
    "B" : 11,
    "C" : 12,
    "D" : 13,
    "E" : 14,
    "F" : 15,
)
```

#### Dictionary
Unlike _maps_, _dictionary_ contains pairs of unique keys **and** unique values:
```
dictionary (
    1   : 3,
    2   : 2,
    3   : 1,
)
```
This makes dictionary to be [bidirectional](https://en.wikipedia.org/wiki/Bidirectional_map) versions of _map_.

### Binaries
Binaries is designed to compactly represent sequences of bytes. There are a few notations to denote this kind of objects in Tau.

#### Hex
_Hex_ is used to denote binary data in [hexadecimal notation](https://en.wikipedia.org/wiki/Hexadecimal). Each byte should be written inside container as a pair of two hexadecimal digits: regular digits 0-9 or letters A-F (not case sensitive):
```
hex (010203)
```
The spaces (including tabs and line breaks) inside are ignored:
```
hex (
    00  01  02  03
    04  05  06  07
    08  09  0A  0B
    0C  0D  0E  0F
)
```

#### Base64
_Base64_ is used to denote binary data in [Base64 encoding](https://en.wikipedia.org/wiki/Base64):
```
base64 (
    TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlz
    IHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2Yg
    dGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGlu
    dWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRo
    ZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=
)
```
Like with _hex_, spaces are also ignored.

### Raw
_TODO_

## Referencing
Tau also uses additional mechanisms to denote objects which is mostly not supported by other data formats, but may be represented in some programming languages.

### Naming
Naming is a way to define a unique name for specific object. This name can be used as a reference for object in order to reduce its size, creating circular dependencies or even fractals.
Name is denoted inside single quotes[("'")](https://en.wikipedia.org/wiki/Quotation_mark):
```
array (
    'zero' 0,   1,
    'zero',     2,
    'zero',     3,
)
```
Names don't require [forward declaration](https://en.wikipedia.org/wiki/Forward_declaration), which means that they can be used to create circular dependencies or fractals:
```
'my self-containing array' array ( 'my self-containing array' )
```
