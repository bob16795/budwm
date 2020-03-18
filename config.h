/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int gappsi             = 0;        /* inner gaps */
static const int gappso             = 0;        /* outer gaps */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
  /*               fg           bg           border   */
  [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
  [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4"};

static const Rule rules[] = {
  /* xprop(1):
   *  WM_CLASS(STRING) = instance, class
   *  WM_NAME(STRING) = title
   */
  /* class         instance    title       tags mask     iscentered   isfloating   monitor container*/
  { NULL,          NULL,       NULL,       0,            1,           1,           -1,     -1},
  { "urxvtA",      NULL,       NULL,       0,            0,           0,           -1,     1},
  { "urxvtB",      NULL,       NULL,       0,            0,           0,           -1,     2},
  { "urxvtC",      NULL,       NULL,       0,            0,           0,           -1,     3},
  { "Sxiv",        NULL,       NULL,       0,            0,           0,           -1,     2},
  { "cmus",        NULL,       NULL,       0,            0,           0,           -1,     2},
  { "Subl",        NULL,       NULL,       0,            0,           0,           -1,     3},
  { "minecraft-launcher",NULL, NULL,       0,            0,           0,           -1,     3},
  { "Minecraft 1.14.4",NULL,   NULL,       0,            0,           1,           -1,     0},
  { "qutebrowser", NULL,       NULL,       0,            0,           0,           -1,     3},
  { "Files",       NULL,       NULL,       0,            0,           0,           -1,     4},
  { "Lutris",      NULL,       NULL,       0,            0,           0,           -1,     3},
  { "Zathura",     NULL,       NULL,       0,            0,           0,           -1,     3},
  { NULL,          "winword.exe",NULL,     0,            0,           0,           -1,     3},
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "bud.c"
static const Layout layouts[] = {
  /* symbol     arrange function */
  { "[+]",      bud  },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
  { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
  { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define SHONECMD(name, cmd) { .v = (const char*[]){ "/home/john/scr/launchprog", name, "/bin/sh", "-c", cmd, NULL } }
#define TERMONECMD(name, cmd) { .v = (const char*[]){ "/home/john/scr/launchprog", name, "/usr/bin/xst", "-T", name, "-c", name, "-e", cmd, NULL } }
#define TERMCMD(name, cmd) { .v = (const char*[]){ "/usr/bin/xst", "-T", name, "-c", name, "-e", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *runcmd[] = { "rofi", "-show", "run", "-padding", "200", "-fullscreen", NULL };
static const char *druncmd[] = { "rofi", "-show", "drun", "-show-icons", "-padding", "200", "-fullscreen", NULL };
static const char *termcmd[]  = { "xst", NULL };

static Key keys[] = {
  /* modifier                     key        function        argument */
  { MODKEY,                       XK_d,      spawn,          {.v = runcmd } },
  { MODKEY|ShiftMask,             XK_d,      spawn,          {.v = druncmd } },
  { MODKEY,                       XK_Return, spawn,          TERMCMD("urxvtA", "/bin/bash") },
  { MODKEY|ShiftMask,             XK_Return, spawn,          TERMONECMD("urxvtB", "/bin/bash") },
  { MODKEY|ShiftMask,             XK_c,      spawn,          TERMONECMD("urxvtC", "/bin/bash") },
  { MODKEY,                       XK_m,      spawn,          TERMONECMD("cmus", "/usr/bin/cmus") },
  { MODKEY,                       XK_w,      spawn,          SHONECMD("qutebrowser", "qutebrowser") },
  { MODKEY,                       XK_c,      spawn,          SHONECMD("doc", "subl") },
  { MODKEY,                       XK_l,      spawn,          SHCMD("linklord -x 'qutebrowser \"%u\"'") },
  { MODKEY|ShiftMask,             XK_l,      spawn,          SHCMD("linklord -d ~/.config/pdflord/pdfs -s ~/.config/pdflord -x 'zathura \"%u\"'") },
  { MODKEY,                       XK_r,      spawn,          TERMONECMD("Files", "/usr/bin/ranger") },
  { MODKEY,                       XK_f,      fullscreen,     {0} },
  { MODKEY,                       XK_g,      spawn,          SHONECMD("Lutris", "lutris")},
  { MODKEY,                       XK_Tab,    focusstack,     {.i = +1 } },
  { MODKEY,                       XK_q,      killclient,     {0} },
  { MODKEY,                       XK_space,  togglefloating, {0} },
  { MODKEY|ShiftMask,             XK_1,      setcontainer,   {.f = 1 } },
  { MODKEY|ShiftMask,             XK_2,      setcontainer,   {.f = 2 } },
  { MODKEY|ShiftMask,             XK_3,      setcontainer,   {.f = 3 } },
  { MODKEY|ShiftMask,             XK_4,      setcontainer,   {.f = 4 } },
  { MODKEY|ShiftMask,             XK_r,      quit,           {1} }, 
  { MODKEY,                       0x5b,      spawn,          SHCMD("mediacontrol seek -10") },
  { MODKEY,                       0x5d,      spawn,          SHCMD("mediacontrol seek +10") },
  { 0,                            0x1008FF12,spawn,          SHCMD("pactl set-sink-mute 0 'toggle'") },
  { 0,                            0x1008ffb2,spawn,          SHCMD("pactl set-source-mute 1 'toggle'") },
  { 0,                            0x1008FF11,spawn,          SHCMD("pactl set-sink-volume 0 -5%") },
  { ShiftMask,                    0x1008FF11,spawn,          SHCMD("pactl set-sink-volume 0 -10%") },
  { 0,                            0x1008FF13,spawn,          SHCMD("pactl set-sink-volume 0 +5%") },
  { ShiftMask,                    0x1008FF13,spawn,          SHCMD("pactl set-sink-volume 0 +10%") },
  { 0,                            0x1008FF31,spawn,          SHCMD("mediacontrol toggle") },
  { 0,                            0x1008ff14,spawn,          SHCMD("mediacontrol toggle") },
  { 0,                            0x1008ff17,spawn,          SHCMD("mediacontrol next") },
  { 0,                            0x1008ff16,spawn,          SHCMD("mediacontrol prev") },
  TAGKEYS(                        XK_F1,                      0)
  TAGKEYS(                        XK_F2,                      1)
  TAGKEYS(                        XK_F3,                      2)
  TAGKEYS(                        XK_F4,                      3)
  { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

