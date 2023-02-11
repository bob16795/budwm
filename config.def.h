/* See LICENSE file for copyright and license details. */

/* ipc file */
#define FileName "/tmp/budwm.ipc"

/* appearance */
static const char *fonts[]          = { "CaskaydiaCovePL Nerd Font:size=10"};
static const unsigned int borderpx  = 2;         /* border pixel of windows */
static const unsigned int snap      = 32;        /* snap pixel */
static const unsigned int systraypinning = 1;    /* pin systray to monitor X */
static const unsigned int systrayspacing = 0;    /* systray spacing */
static const int systraypinningfailfirst = 1;    /* if pinning fails, display systray on the first monitor*/
static const int showsystray        = 1;         /* 0 means no systray */
static const int enableipc          = 1;         /* 0 means ipc */
static const int showbar            = 1;         /* 0 means no bar */
static const int topbar             = 1;         /* 0 means bottom bar */
static const int gappsi             = 15;        /* inner gaps */
static const int gappso             = 40;        /* outer gaps */
static const int frameicons         = 1;         /* show container icons in frame */
static const int frametabs          = 1;         /* show container icons in frame */
static const int baricon            = 1;         /* show icons in the bar*/
static const int onebar             = 1;         /* show only the bar on the main monitor*/
static int absplit                  = -450;      /* the default position of the split betwen containers a and b */
static int acsplit                  = 200;       /* the default position of the split betwen containers a and c */
static int bdsplit                  = 300;       /* the default position of the split betwen containers b and d */
static int amode                    = 1;         /* default mode for contsainer a 0: stack, 1: horiz, 2: vertical */
static int bmode                    = 1;         /* default mode for contsainer b 0: stack, 1: horiz, 2: vertical */
static int cmode                    = 1;         /* default mode for contsainer c 0: stack, 1: horiz, 2: vertical */
static int dmode                    = 1;         /* default mode for contsainer d 0: stack, 1: horiz, 2: vertical */
static const int swallowfloating    = 0;         /* swallow when the terminal is floating */
static const int resizehints        = 0;         /* 1 means respect size hints in tiled resizals */

/* theme */
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#333333";
static char normfgcolor[]           = "#888888";
static char selfgcolor[]            = "#FFFFFF";
static char selbordercolor[]        = "#4C7899";
static char selbgcolor[]            = "#285577";
static const char *desktoptext      = "Desktop";
static const char *desktopicon      = "";

static char *colors[][3] = {
  /*               fg           bg           border   */
  [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
  [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "F1", "F2", "F3", "F4"};

static const Rule rules[] = {
  /* xprop(1):
   *  WM_CLASS(STRING) = instance, class
   *  WM_NAME(STRING) = title
   */
  /* class         instance    title   Force name    icon iscentered   isfloating   isterm noswallow container*/
  { NULL,          NULL,       NULL,   NULL,         "?", 1,           1,           0,     0,        3},
  { "stA",         NULL,       NULL,   NULL,       "", 0,           0,           0,     0,        1},
  { "stB",         NULL,       NULL,   NULL,       "", 0,           0,           0,     0,        2},
  { "stC",         NULL,       NULL,   NULL,       "", 0,           0,           0,     0,        3},
  { "stF",         NULL,       NULL,   NULL,       "", 1,           1,           0,     1,        3},
  { "neomutt",     NULL,       NULL,   "Mail",       "✉", 0,           0,           0,     0,        3},
  { "Dragon",      NULL,       NULL,   "Drag",       "^", 1,           1,           0,     1,        1},
  { "discord",     NULL,       NULL,   "Discord",    "C", 0,           0,           0,     1,        3},
  { "htop",        NULL,       NULL,   "Tasks",      "", 0,           0,           0,     0,        1},
  { "Sxiv",        NULL,       NULL,   "Pix",        "", 0,           0,           0,     0,        2},
  { "mpv",         NULL,       NULL,   "Vid",        "", 0,           0,           0,     0,        2},
  { "zoom",        NULL,       NULL,   "Zoom",       "", 0,           0,           0,     0,        4},
  { "chromium",    NULL,       NULL,   "Web",        "", 0,           0,           0,     0,        3},
  { "cava",        NULL,       NULL,   "Vis",        "", 0,           0,           0,     0,        2},
  { "Spotify",     NULL,       NULL,   "Mus",        "", 0,           0,           0,     0,        3},
  { "ncmpcpp",     NULL,       NULL,   "Mus",        "", 0,           0,           0,     0,        4},
  { "Code - Insiders", NULL,   NULL,   "Code",       "", 0,           0,           0,     0,        3},
  { "code-oss",    NULL,       NULL,   "Code",       "", 0,           0,           0,     0,        3},
  { "subl",        NULL,       NULL,   "Code",       "", 0,           0,           0,     0,        3},
  { "qutebrowser", NULL,       NULL,   "Web",        "", 0,           0,           0,     0,        3},
  { "firefox",     NULL,       NULL,   "Web",        "", 0,           0,           0,     0,        3},
  { "chromium",    NULL,       NULL,   "Web",        "", 0,           0,           0,     0,        3},
  { "Surf",        NULL,       NULL,   "Web",        "", 0,           0,           0,     0,        3},
  { "FilesB",      NULL,       NULL,   "Files",      "", 0,           0,           1,     0,        2},
  { "FilesD",      NULL,       NULL,   "Files",      "", 0,           0,           1,     0,        4},
  { "Lutris",      NULL,       NULL,   "Gam",        "", 0,           0,           0,     0,        2},
  { "Zathura",     NULL,       NULL,   "PDF",        "", 0,           0,           0,     0,        3},
  { "Zathura",     NULL,       NULL,   "PDF",        "", 0,           0,           0,     0,        3},
  { "Pavucontrol", NULL,       NULL,   "Vol",        "", 0,           0,           0,     0,        2},
  { "XEyes",       NULL,       NULL,   "EYES",       "I", 0,           0,           0,     0,        2},
  { NULL,  "libreoffice",      NULL,   "Wrd",        "", 0,           0,           0,     0,        3},
  { "Vivaldi-stable",NULL,     NULL,   "Web",        "", 0,           0,           0,     0,        3},
  { "Vivaldi-stable",NULL,     NULL,   "Web",        "", 0,           0,           0,     0,        3},
  { "minecraft-launcher",NULL, NULL,   "Gam",        "", 0,           0,           0,     0,        3},
  { "Minecraft 1.14.4",NULL,   NULL,   "Gam",        "", 0,           0,           0,     0,        0},
  { "Steam",       NULL,       NULL,   "Steam",      "", 0,           0,           0,     0,        4},
  { NULL,          "winword.exe",NULL, "Wrd",        "", 0,           0,           0,     0,        3},
  { NULL,          "mspub.exe",NULL,   "Pub",        "", 0,           0,           0,     0,        3},
  { NULL, NULL, "Picture in picture",  "PIP",        "", 0,           0,           0,     0,        2},
  { NULL, NULL, "the Will To Lose",    "Gam",        "G", 0,           1,           0,     1,        3},
  { "hangui", NULL,           NULL,    "Gam",        "G", 0,           1,           0,     1,        3},
};

/* layouts */

#include "bud.h"
static const Layout layouts[] = {
  /* symbol arrange function */
  {" --- ", budnogaps },
  {" -+- ", budnoogaps},
  {" [+] ", bud       },
  {" [-] ", budnoigaps},
  {NULL,  NULL}
};

static void bigB(const Arg *arg);
static void smallB(const Arg *arg);
static void titlemodetoggle(const Arg *arg);

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
  { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
  { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
        
/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define TERMCMD(name, cmd) { .v = (const char*[]){ "/usr/local/bin/st", "-T", name, "-c", name, "-e", cmd, NULL } }

static Key keys[] = {
  /* modifier                     key        function         argument */
  { MODKEY|ControlMask|Mod1Mask,  XK_Return, spawn,           TERMCMD("st", "/usr/bin/zsh") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkBarIcon,           0,              Button1,        clickbar,       {.v = "1"} },
  { ClkBarIcon,           0,              Button3,        clickbar,       {.v = "3"} },
  { ClkBarIcon,           0,              Button2,        clickbar,       {.v = "2"} },
  { ClkBarIcon,           ShiftMask,      Button1,        clickbar,       {.v = "icon"} },
  { ClkBarIcon,           ShiftMask,      Button2,        clickbar,       {.v = "icon"} },
  { ClkBarIcon,           ShiftMask,      Button3,        clickbar,       {.v = "icon"} },
  { ClkFrameWin,          0,              Button1,        movemouse,      {0} },
  { ClkFrameWin,          0,              Button2,        killclient,     {0} },
  { ClkFrameWin,          0,              Button3,        resizemouse,    {0} },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkLtSymbol,          0,              Button1,        cyclelayout,    {.i = +1 } },
  { ClkLtSymbol,          0,              Button3,        cyclelayout,    {.i = -1 } },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
};

#define TAGSIG(TAG) \
  { 101 + (TAG * 10),      view,           {.ui = 1 << TAG} }, \
  { 102 + (TAG * 10),      toggleview,     {.ui = 1 << TAG} }, \
  { 103 + (TAG * 10),      tag,            {.ui = 1 << TAG} }, \
  { 104 + (TAG * 10),      toggletag,      {.ui = 1 << TAG} }, \
  { 105 + (TAG * 10),      setcontainer,   {.f = TAG } },

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signum>"` */
static Signal signals[] = {
  /* signum       function        argument  */
  { 1,            xrdb,           {0} },
  { 2,            updatestatus,   {0} },
  { 3,            cyclelayout,    {.i = +1} },
  { 4,            cyclelayout,    {.i = -1} },
  { 5,            focusstack,     {.i = +1} },
  { 6,            focusstack,     {.i = -1} },
  { 7,            fullscreen,     {0} },
  { 8,            togglebar,      {0} },
  { 9,            setacsplit,     {.i = -200}},
  { 10,           setacsplit,     {.i = +200}},
  { 11,           setmode,        {1} },
  { 12,           setmode,        {2} },
  { 13,           setmode,        {3} },
  { 14,           bigB,           {0} },
  { 15,           smallB,         {0} },
  { 16,           killclient,     {0} },
  { 17,           togglefloating, {0} },
  { 18,           inchsplit,      {.i = -5} },
  { 19,           inchsplit,      {.i = +5} },
  { 20,           incvsplit,      {.i = -5} },
  { 21,           incvsplit,      {.i = +5} },
  { 22,           titlemodetoggle,{0} },
  { 23,           unswallow,      {0} },
  { 99,           quit,           {0} },
  TAGSIG(0)
  TAGSIG(1)
  TAGSIG(2)
  TAGSIG(3)
  TAGSIG(4)
};


static const Block blocks[] = {
  /*sep*//*Command*/ 
  {0,    "nameinfo"                   },//0
  //{0,    "music"                      },//0
  {1,    "date +%-I:%M | sed 's/ //'" },//0
  {0,    "wswpswitcher"               },//1
  {0,    "volume"                     },//1
  {0,    "volume-mic"                 },//1
  {0,    "disk /home "               },//1
  {0,    "battery"                    },//0
  //{0,    "cpu"                        },//0
  //{0,    "mailbox"                    },//0
  //{0,    "bwp-status"                 },//1
  //{0,    "mondo-status"               },//1
};
static int defbaricons = 0b0;

void
bigB(const Arg *arg) {
  Arg a = {.i = +716};
  setabsplit(&a);
  Arg b = {.i = +450};
  setbdsplit(&b);
}

void
smallB(const Arg *arg) {
  Arg a = {.i = -450};
  setabsplit(&a);
  Arg b = {.i = +300};
  setbdsplit(&b);
}

void
titlemodetoggle(const Arg *arg) {
  titlemode = (titlemode == 0) ? 1: 0;
  drawbar(selmon);
}
