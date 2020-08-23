/* See LICENSE file for copyright and license details. */

/* ipc file */
#define FileName "/tmp/budwm.ipc"

/* appearance */
static const char *fonts[]          = { "CaskaydiaCove Nerd Font Mono:size=10"};
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int enableipc          = 1;        /* 0 means ipc */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int gappsi             = 15;       /* inner gaps */
static const int gappso             = 20;       /* outer gaps */
static const int frameicons         = 1;        /* show container icons in frame */
static const int frametabs          = 1;        /* show container icons in frame */
static const int baricon            = 1;        /* show the window icon on the bar */
static const int onebar             = 1;        /* show only the bar on the main monitor*/
static int absplit                  = -450;     /* the default position of the split betwen containers a and b*/
static int acsplit                  = 170;      /* the default position of the split betwen containers a and c*/
static int bdsplit                  = 300;      /* the default position of the split betwen containers b and d*/
static int amode                    = 1;        /* default mode for contsainer a 0: stack, 1: horiz, 2: vertical*/
static int bmode                    = 1;        /* default mode for contsainer b 0: stack, 1: horiz, 2: vertical*/
static int cmode                    = 1;        /* default mode for contsainer c 0: stack, 1: horiz, 2: vertical*/
static int dmode                    = 1;        /* default mode for contsainer d 0: stack, 1: horiz, 2: vertical*/
static const int swallowfloating    = 0;
static const int defbaricons        = 0b0;
static const char *desktoptext      = "Desktop";
static const char *desktopicon      = "";
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
static const char *tags[] = { "F1", "F2", "F3", "F4"};

/* scratchpad */
static const unsigned scratchpad_mask = 1u << sizeof tags / sizeof * tags;

static const Rule rules[] = {
  /* xprop(1):
   *  WM_CLASS(STRING) = instance, class
   *  WM_NAME(STRING) = title
   */
  /* class         instance    title   Force name    icon    tags mask     iscentered   isfloating   isterm noswallow monitor container*/
  { NULL,          NULL,       NULL,   NULL,         0,      0,            1,           1,           0,     0,        -1,     3},
  { "stA",         NULL,       NULL,   "Term",       "",    0,            0,           0,           1,     0,        -1,     1},
  { "stB",         NULL,       NULL,   "Term",       "",    0,            0,           0,           1,     0,        -1,     2},
  { "stC",         NULL,       NULL,   "Term",       "",    0,            0,           0,           1,     0,        -1,     3},
  { "neomutt",     NULL,       NULL,   "Mail",       "✉",    0,            0,           0,           0,     0,        -1,     3},
  { "Dragon",      NULL,       NULL,   "Drag",       "^",    0,            1,           0,           1,     1,        -1,     1},
  { "htop",        NULL,       NULL,   "Tasks",      "",    0,            0,           0,           0,     0,        -1,     1},
  { "Sxiv",        NULL,       NULL,   "Pix",        "P",    0,            0,           0,           0,     0,        -1,     2},
  { "mpv",         NULL,       NULL,   "Vid",        "",    0,            0,           0,           0,     0,        -1,     2},
  { "cava",        NULL,       NULL,   "Vis",        "C",    0,            0,           0,           0,     0,        -1,     4},
  { "Spotify",     NULL,       NULL,   "Mus",        "M",    0,            0,           0,           0,     0,        -1,     3},
  { "ncmpcpp",     NULL,       NULL,   "Mus",        "M",    0,            0,           0,           0,     0,        -1,     2},
  { "Subl",        NULL,       NULL,   "Code",       "",    0,            0,           0,           0,     0,        -1,     3},
  { "qutebrowser", NULL,       NULL,   "Web",        "",    0,            0,           0,           0,     0,        -1,     3},
  { "Surf",        NULL,       NULL,   "Web",        "",    0,            0,           0,           0,     0,        -1,     3},
  { "FilesB",      NULL,       NULL,   "Files",      "",    0,            0,           0,           1,     0,        -1,     2},
  { "FilesD",      NULL,       NULL,   "Files",      "",    0,            0,           0,           1,     0,        -1,     4},
  { "Lutris",      NULL,       NULL,   "Gam",        "",    0,            0,           0,           0,     0,        -1,     2},
  { "Zathura",     NULL,       NULL,   "PDF",        "",    0,            0,           0,           0,     0,        -1,     3},
  { "Zathura",     NULL,       NULL,   "PDF",        "",    0,            0,           0,           0,     0,        -1,     3},
  { "Pavucontrol", NULL,       NULL,   "Vol",        "",    0,            0,           0,           0,     0,        -1,     2},
  { "XEyes",       NULL,       NULL,   "EYES",       "I",    0,            0,           0,           0,     0,        -1,     2},
  { NULL,  "libreoffice",      NULL,   "Wrd",        "",    0,            0,           0,           0,     0,        -1,     3},
  { "Vivaldi-stable",NULL,     NULL,   "Web",        "",    0,            0,           0,           0,     0,        -1,     3},
  { "Vivaldi-stable",NULL,     NULL,   "Web",        "",    0,            0,           0,           0,     0,        -1,     3},
  { "minecraft-launcher",NULL, NULL,   "Gam",        "",    0,            0,           0,           0,     0,        -1,     3},
  { "Minecraft 1.14.4",NULL,   NULL,   "Gam",        "",    0,            0,           0,           0,     0,        -1,     0},
  { "Steam",       NULL,       NULL,   "Gam",        "",    0,            0,           0,           0,     0,        -1,     2},
  { NULL,          "winword.exe",NULL, "Wrd",        "",    0,            0,           0,           0,     0,        -1,     3},
  { NULL,          "mspub.exe",NULL,   "Pub",        "",    0,            0,           0,           0,     0,        -1,     3},
  { NULL, NULL, "Picture in picture",  "PIP",        "",    0,            0,           0,           0,     0,        -1,     2},
};

/* layout(s) */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "bud.c"
static const Layout layouts[] = {
  /* symbol     arrange function */
  {" --- ",     budnogaps },
  {" -+- ",      budnoogaps},
  {" [+] ",      bud       },
  {" [-] ",     budnoigaps},
  {NULL, NULL}
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

/* commands */
static const char *runcmd[] = { "dmenu_run", NULL };
static const char *druncmd[] = { "j4-dmenu-desktop", NULL };

static Key keys[] = {
  /* modifier                     key        function         argument */
  { MODKEY,                       XK_h,      cyclelayout,     {.i = +1 } },
  { MODKEY,                       XK_grave,  spawn,           SHCMD("iconpick") },
  { MODKEY,                       XK_d,      spawn,           {.v = runcmd } },
  { MODKEY|ShiftMask,             XK_d,      spawn,           {.v = druncmd } },
  { MODKEY,                       XK_v,      spawn,           TERMCMD("cava", "cava") },
  { MODKEY,                       XK_Return, spawn,           TERMCMD("stA", "/usr/bin/zsh") },
  { MODKEY|ShiftMask,             XK_Return, spawn,           TERMCMD("stB", "/usr/bin/zsh") },
  { MODKEY|ShiftMask,             XK_c,      spawn,           TERMCMD("stC", "/usr/bin/zsh") },
  { MODKEY,                       XK_i,      spawn,           TERMCMD("htop", "/usr/bin/htop") },
  { MODKEY,                       XK_e,      spawn,           TERMCMD("neomutt", "/usr/bin/neomutt") },
  { MODKEY,                       XK_t,      spawn,           SHCMD("mondocontrol menu") },
  { MODKEY,                       XK_m,      spawn,           TERMCMD("ncmpcpp", "/usr/bin/ncmpcpp") },
  { MODKEY|ShiftMask,             XK_n,      setmode,         {.i = 3} }, // vertical mode
  { MODKEY,                       XK_n,      setmode,         {.i = 2} }, // horizontal mode
  { MODKEY|ShiftMask,             XK_m,      setmode,         {.i = 1} }, // normal mode
  { MODKEY|ShiftMask,             XK_b,      spawn,           SHCMD("sxiv -b -s h ~/pix/wallpapers/currentwall") },
  { MODKEY|ShiftMask,             XK_w,      spawn,           SHCMD("bwpcontrol menu") },
  { MODKEY,                       XK_w,      spawn,           SHCMD("qutebrowser") },
  { MODKEY|ShiftMask,             XK_t,      spawn,           SHCMD("sublaunch -p todo") },
  { MODKEY,                       XK_c,      spawn,           SHCMD("sublaunch -p dox") },
  { MODKEY,                       XK_a,      spawn,           SHCMD("pavucontrol") },
  { MODKEY,                       XK_l,      spawn,           SHCMD("linklord -x 'gurl \"%u\"'") },
  { MODKEY|ShiftMask,             XK_r,      spawn,           TERMCMD("FilesB", "/usr/bin/ranger") },
  { MODKEY,                       XK_r,      spawn,           TERMCMD("FilesD", "/usr/bin/ranger") },
  { MODKEY,                       XK_f,      fullscreen,      {0} },
  { MODKEY,                       XK_o,      setacsplit,      {.i = -170} },
  { MODKEY|ShiftMask,             XK_o,      setacsplit,      {.i = +170} },
  { MODKEY,                       XK_p,      bigB,            {0} },
  { MODKEY|ShiftMask,             XK_p,      smallB,          {0} },
  { MODKEY,                       XK_b,      togglebar,       {0} },
  { MODKEY,                       XK_g,      spawn,           SHCMD("lutris")},
  { MODKEY,                       XK_Tab,    focusstack,      {.i = +1 } },
  { MODKEY|ShiftMask,             XK_Tab,    focusstack,      {.i = -1 } },
  { MODKEY,                       XK_q,      killclient,      {0} },
  { MODKEY|ShiftMask,             XK_q,      killclient,      {0} },
  { MODKEY,                       XK_space,  togglefloating,  {0} },
  { MODKEY|ShiftMask,             XK_1,      setcontainer,    {.f = 1 } },
  { MODKEY|ShiftMask,             XK_2,      setcontainer,    {.f = 2 } },
  { MODKEY|ShiftMask,             XK_3,      setcontainer,    {.f = 3 } },
  { MODKEY|ShiftMask,             XK_4,      setcontainer,    {.f = 4 } },
  { MODKEY,                       XK_F5,     xrdb,            {1} }, 
  { MODKEY,                       0x5b,      spawn,           SHCMD("mediacontrol seek -10") },
  { MODKEY,                       0x5d,      spawn,           SHCMD("mediacontrol seek +10") },
  { 0,                            0x1008FF12,spawn,           SHCMD("pamixer -t") },
  { 0,                            0x1008ffb2,spawn,           SHCMD("pamixer -default-source -t") },
  { 0,                            0x1008FF11,spawn,           SHCMD("pamixer -d 5") },
  { ShiftMask,                    0x1008FF11,spawn,           SHCMD("pamixer -d 10") },
  { 0,                            0x1008FF13,spawn,           SHCMD("pamixer -i 5") },
  { ShiftMask,                    0x1008FF13,spawn,           SHCMD("pamixer -i 10") },
  { 0,                            0x1008FF31,spawn,           SHCMD("mediacontrol playpause") },
  { 0,                            0x1008ff14,spawn,           SHCMD("mediacontrol playpause") },
  { 0,                            0x1008ff17,spawn,           SHCMD("mediacontrol next") },
  { 0,                            0x1008ff16,spawn,           SHCMD("mediacontrol prev") },
  TAGKEYS(                        XK_F1,                      0)
  TAGKEYS(                        XK_F2,                      1)
  TAGKEYS(                        XK_F3,                      2)
  TAGKEYS(                        XK_F4,                      3)
  { MODKEY|ShiftMask,             XK_Escape, quit,            {0} },
  { MODKEY,                       XK_Up,     inchsplit,       {.i = -5} },
  { MODKEY,                       XK_Down,   inchsplit,       {.i = +5} },
  { MODKEY,                       XK_Left,   incvsplit,       {.i = -5} },
  { MODKEY,                       XK_Right,  incvsplit,       {.i = +5} },
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
  { 9,            setacsplit,     {.i = -170}},
  { 10,           setacsplit,     {.i = +170}},
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
  { 99,           quit,           {0} },
  TAGSIG(0)
  TAGSIG(1)
  TAGSIG(2)
  TAGSIG(3)
  TAGSIG(4)
};

static const Block blocks[] = {
  /*Icon*//*Command*/ 
//  {"",    "nameinfo"                   },
//  {"",    "music"                      },
  {";",   "date +%-I:%M | sed 's/ //'" },
//  {"",    "wswpswitcher"               },
//  {"",    "volume"                     },
//  {"",    "volume-mic"                 },
//  {"",    "disk /home "               },
//  {"",    "battery"                    },
//  {"",    "cpu"                        },
//  {"",    "mailbox"                    },
//  {"",    "bwp-status"                 },
//  {"",    "mondo-status"               }
};

void
bigB(const Arg *arg) {
  Arg a = {.i = +716};
  setabsplit(&a);
  Arg b = {.i = +450};
  setbdsplit(&b);
}

void
smallB(const Arg *arg) {
  Arg a = {.i = +916};
  setabsplit(&a);
  Arg b = {.i = +300};
  setbdsplit(&b);
}

void
titlemodetoggle(const Arg *arg) {
  titlemode = (titlemode == 0) ? 1: 0;
  drawbar(selmon);
}
