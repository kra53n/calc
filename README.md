# calc - simple calculator

<img src="https://i.pinimg.com/originals/bf/d3/af/bfd3af850ecc21ad95495e994a73e80c.jpg" align="right" width="40%">

calc - calculator with supproting math types like matrix, complex
numbers, etc. Can be run from the terminal in a REPL
(Read-Eval-Print-Loop) manner or by executing lines by lines from an
Xml file.

## Types

Type            | Declaration
--:             | :--
Matrix          | `matrix((1 1) (1 1))` or `mx((1 1) (1 1))`
Complex         | `complex(1 1)` or `cx(1 1)`
Big int         | `2354672543213341212323`
Fraction        | `[1/2]` or `1[1/2`
Just a number   | `777`

## Usage

### Repl

```
$ calc
> a = 101
> b = 737
> a + b
838
>
```

### Xml

```
$ calc --xml path/to/file.xml
838
```

Content of `file.xml`:

```xml
<calc>

<vars type="Num">
    <var name="a">101</var>
    <var name="b">737</var>
</vars>

<eval>
    a + b
</eval>

</calc>
```
