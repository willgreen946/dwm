/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "terminus:size=8" };
static const char black[]            = "#000000";
static const char green[]            = "#33ff66";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { green, black, black},
	[SchemeSel]  = { green, black,  green},
};

/* tagging */
static const char *tags[] = { "[1]", "[2]", "[3]", "[4]", "[5]", "[6]", "[7]", "[8]"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle },
	{ "[D]",      deck },
	{ "[T]",      tile }, 
};

/* key definitions */
#define MODKEY Mod1Mask
#define SUPKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
#define TERM "xterm"

static const char *termcmd[]  = { TERM, "-e", "tmux", NULL };
static const char *vifm[] = { TERM, "-e", "vifm", NULL };
static const char *browser[]  = { "qutebrowser", "/home/will/Documents/Bookmarks/bookmarks.html", NULL };
static const char *alterm[] = { "xterm", "-e", "/bin/ksh", NULL };
static const char *gvim[]  =  { "gvim", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,	                XK_space,  spawn,          {.v = termcmd } },
	{ MODKEY,			XK_q,	   spawn,	   {.v = browser } },
	{ MODKEY,			XK_f,	   spawn,	   {.v = vifm } },
	{ MODKEY,			XK_g,	   spawn,	   {.v = gvim } },
	{ SUPKEY,			XK_space,  spawn,	   {.v = alterm } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_l,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_h,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.02} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.02} },
	{ MODKEY|ShiftMask,             XK_k,      setcfact,       {.f = +0.02} },
	{ MODKEY|ShiftMask,             XK_j,      setcfact,       {.f = -0.02} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_d,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	{ MODKEY|ShiftMask,             XK_Escape,quit,           {0} },
};
