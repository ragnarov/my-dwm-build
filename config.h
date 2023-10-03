/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                instance    title           tags mask     isfloating   monitor */
        // tag 1
        // browsers
	/* class                instance    title           tags mask     isfloating   monitor */
	{ "Firefox",            NULL,       NULL,           1,            0,           -1 },
	{ "firefox",            NULL,       NULL,           1,            0,           -1 },
	{  NULL,         "Navigator",       NULL,           1,            0,           -1 },
	{ "Firefox-esr",        NULL,       NULL,           1,            0,           -1 },
	{ "Tor Browser",        NULL,       NULL,           1,            0,           -1 },
	{  NULL,                NULL,       "Chromium",     1,            0,           -1 },
	{  NULL,                NULL,       "Tor Browser",  1,            0,           -1 },
        // tag 2
        // terminals
	{ "st-256color",        NULL,       NULL,           1 << 1,       0,           -1 },
	{ "URxvt",              NULL,       NULL,           1 << 1,       0,           -1 },
        // tag 3
        // documents
	{ "Zathura",            NULL,       NULL,           1 << 2,       0,           -1 },
	{ "org.pwmt.zathura",   NULL,       NULL,           1 << 2,       0,           -1 },
	{  NULL,    "tabbed-zathura",       NULL,           1 << 2,       0,           -1 },
	{ "okular",             NULL,       NULL,           1 << 2,       0,           -1 },
        // tag 4
        // library
	{ "Zeal",               NULL,       NULL,           1 << 3,       0,           -1 },
	{  NULL,              "zeal",       NULL,           1 << 3,       0,           -1 },
	{ "calibre",            NULL,       NULL,           1 << 3,       0,           -1 },
        // tag 5
        // multimedia
	{ "mpv",                NULL,       NULL,           1 << 4,       0,           -1 },
	{  NULL,                NULL,       "VLC media player",
                                                            1 << 4,       0,           -1 },
	{  NULL,                NULL,       "SMPlayer",     1 << 4,       0,           -1 },
        // tag 6
        // filemanager
	{ "Pcmanfm",            NULL,       NULL,           1 << 5,       0,           -1 },
	{ "Spacefm",            NULL,       NULL,           1 << 5,       0,           -1 },
	{ "Thunar",             NULL,       NULL,           1 << 5,       0,           -1 },
        // tag 7
        // miscellaneous
	{ "jupyterlab-desktop", NULL,       NULL,           1 << 6,       0,           -1 },
	{ "KeePassXC",          NULL,       NULL,           1 << 6,       0,           -1 },
        // tag 8
        // control
	{ "Pavucontrol",        NULL,       NULL,           1 << 7,       0,           -1 },
        // tag 9
        // im
	{ "discord",            NULL,       NULL,           1 << 8,       0,           -1 },
	{ "KotatogramDesktop",  NULL,       NULL,           1 << 8,       0,           -1 },
	{ "revolt-desktop",     NULL,       NULL,           1 << 8,       0,           -1 },
	{  NULL,    "revolt-desktop",       NULL,           1 << 8,       0,           -1 },
        // any tag
	{  NULL,              "cmst",       NULL,                0,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
// #define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
// static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
  /* modifier             key             function        argument */
//{ MODKEY,               XK_p,           spawn,          {.v = dmenucmd } },
  { MODKEY,               XK_Return,      spawn,          SHCMD("st -d ~/HWD") },
  { MODKEY,               XK_b,           togglebar,      {0} }, // Show or Hide bar
  { MODKEY|ShiftMask,     XK_n,           focusstack,     {.i = +1 } }, // Focus Window
  { MODKEY|ShiftMask,     XK_t,           focusstack,     {.i = -1 } }, // Focus Window
  { MODKEY|ControlMask,   XK_o,           incnmaster,     {.i = +1 } },
  { MODKEY|ControlMask,   XK_e,           incnmaster,     {.i = -1 } },
  { MODKEY|ControlMask,   XK_t,           setmfact,       {.f = -0.05} }, // Increase or Decrease Master Area Size
  { MODKEY|ControlMask,   XK_n,           setmfact,       {.f = +0.05} }, // Increase or Decrease Master Area Size
  { MODKEY,               XK_Return,      zoom,           {0} },
  { MODKEY,               XK_Tab,         view,           {0} },
  { MODKEY|ShiftMask,     XK_c,           killclient,     {0} }, // Kill a window
  { MODKEY,               XK_apostrophe,  setlayout,      {.v = &layouts[0]} }, // Sets layout to the first element
  { MODKEY,               XK_comma,       setlayout,      {.v = &layouts[1]} }, // Sets layout to the second element
  { MODKEY,               XK_period,      setlayout,      {.v = &layouts[2]} }, // Sets layout to the third element
  { MODKEY,               XK_space,       setlayout,      {0} }, // Sets layout to the first element
  { MODKEY|ShiftMask,     XK_space,       togglefloating, {0} }, // Toggles floating
  { MODKEY,               XK_0,           view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,     XK_0,           tag,            {.ui = ~0 } },
  { MODKEY|ControlMask,   XK_comma,       focusmon,       {.i = -1 } },
  { MODKEY|ControlMask,   XK_period,      focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask,     XK_comma,       tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,     XK_period,      tagmon,         {.i = +1 } },
  { MODKEY|ShiftMask,     XK_s,           viewnext,       {0} }, // Next tag
  { MODKEY|ShiftMask,     XK_h,           viewprev,       {0} }, // Prev tag
  { MODKEY|ControlMask,   XK_s,           tagtonext,      {0} }, // Move to Next tag
  { MODKEY|ControlMask,   XK_h,           tagtoprev,      {0} }, // Move to Prev tag
  { MODKEY|ShiftMask,
                          XK_Delete,      quit,           {0} }, // Quit DWM
  TAGKEYS(                XK_1,                   0)
  TAGKEYS(                XK_2,                   1)
  TAGKEYS(                XK_3,                   2)
  TAGKEYS(                XK_4,                   3)
  TAGKEYS(                XK_5,                   4)
  TAGKEYS(                XK_6,                   5)
  TAGKEYS(                XK_7,                   6)
  TAGKEYS(                XK_8,                   7)
  TAGKEYS(                XK_9,                   8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
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

