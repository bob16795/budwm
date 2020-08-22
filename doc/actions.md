# Actions

an action is a name of a function

## Arguments

- i: an integer
- ui: a positive integer
- f: a decimal
- v: misc, normally used as an array of strings or a single string.

## By name

- clickbar: For mouse use only triggers a module in the bar to be activated.
- cyclelayout: changes the budmode i times.
- drawbars: updates the bar(s).
- focusstack: cycles focus between tabs if i is less than zero goes backwards.
- fullscreen: toggles fullscreen for the current window.
- inchsplit: increases ACsplit or BDsplit depending on current container by i pixels.
- incvsplit: increases ABsplit by i pixels.
- killclient: closes the current window.
- movemouse: for mouses only moves the current window with the mouse, forces floating.
- quit: quits budwm.
- resizemouse: for mouses only resizes the current window with the mouse, forces floating.
- setlayout: sets the budmode to i.
- setmode: sets the container mode to i, 1 is normal mode, 2 is vertical mode, 3 horozontal mode.
- setabsplit: sets the absplit to i.
- setacsplit: sets the acsplit to i.
- setbdsplit: sets the bdsplit to i.
