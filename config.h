/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-gohufont-medium-*-*-*-14-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#E5E5E5";
static const char normbgcolor[]     = "#2D2D2D";
static const char normfgcolor[]     = "#BBBBBB";
static const char selbordercolor[]  = "#427FED";
static const char selbgcolor[]      = "#2D2D2D";
static const char selfgcolor[]      = "#FFFFFF";
static const unsigned int borderpx  = 3;       /* border pixel of windows */
static const unsigned int snap      = 8;       /* snap pixel */
static const Bool showbar           = True;    /* False means no bar */
static const Bool topbar            = True;    /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       False,       -1 },
	{ "URxvt",    NULL,       "Download", 1 << 8,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvt", NULL };
static const char *webcmd[]  =  { "surf", "www.google.com", NULL };

static const char *mailcmd[]  = { "/home/bryan/script/menubar-popup.sh", "mail", NULL };
static const char *calcmd[]  = { "/home/bryan/script/menubar-popup.sh", "cal", NULL };

static const char *volup[] = { "/home/bryan/script/dwmstatus", "volume", "up", NULL };
static const char *voldown[] = { "/home/bryan/script/dwmstatus", "volume", "down", NULL };
static const char *volmute[] = { "/home/bryan/script/dwmstatus", "volume", "mute", NULL };

static const char *brup[] = { "xbacklight", "-inc", "10", NULL };
static const char *brdown[] = { "xbacklight", "-dec", "10", NULL };

static const char *mediaprev[] = { "mpc", "prev", NULL };
static const char *medianext[] = { "mpc", "next", NULL };
static const char *mediatoggle[] = { "mpc", "toggle", NULL };

static const char *showdate[] = { "/home/bryan/script/dwmstatus", "showdate", NULL };


static Key keys[] = {
	/* program launchers */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_i,      spawn,          {.v = webcmd } },
	{ MODKEY|ShiftMask,             XK_a,      spawn,          {.v = calcmd } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = mailcmd } },
	/* media and backlight */
        { 0,                            0x1008ff13,spawn,          {.v = volup } },
        { 0,                            0x1008ff11,spawn,          {.v = voldown } },
        { 0,                            0x1008ff12,spawn,          {.v = volmute } },
        { 0,                            0x1008ff02,spawn,          {.v = brup } },
        { 0,                            0x1008ff03,spawn,          {.v = brdown } },
        { 0,                            0x1008ff41,spawn,          {.v = showdate } },
        { 0,                            0x1008ff16,spawn,          {.v = mediaprev } },
        { 0,                            0x1008ff17,spawn,          {.v = medianext } },
        { 0,                            0x1008ff14,spawn,          {.v = mediatoggle } },
	/* window manager functions */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkWinTitle,          0,              Button3,        killclient,     {0} },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = mailcmd } },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = calcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

