# Bar

A basic module should be a bash script that outputs the desired text when ran.

## Color

There are 2 colorschemes available for the bar act and ina.
act is the default but can also be signified with the escape char '\xf1'.
and ina can be signified with '\xf2'.

## Icon

when the bar wants just an icon for the script the script will be ran with the argument `icon`.
by default if you shift click a module it toggles icon mode.

## Clicking

Just like icons the script will be run with the argument `1`, `2`, or `3`. based off of witch button you use.

## Adding modules to the bar

You can add text to the bar by adding it to the const Blocks in config.h.
The format for this is
```c
  {icon, command},
```
- icon: To be reimplemeted, prepends the module with this text.
- command: The path or name of the module script.

## Left bar vs Right bar

The bar text starts at the right side of the bar going left to right.
The first module ont the left side should contain `";"` as its icon.

## window title

By default if you click the window title in the bar it toggles advanced title mode.
For now advanced title mode only shows the position and size of the window.
