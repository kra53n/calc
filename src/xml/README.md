# Calculation from XML file

## Example

```xml
<calc>

<vars type="Matrix">
<var name="a">mx((1 0) (0 1))</var>
<var name="b">mx((0 1) (1 0))</var>
</vars>

<vars type="Num">
<var name="c">101</var>
<var name="d"> 1 </var>
</vars>

<eval>
a*2 + b*(c-3)
</eval>

</calc>
```
