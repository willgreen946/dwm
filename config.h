/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "terminus:size=8" };
static const char gray[]        = "#262626";
static const char green[]       = "#33ff66";
static const char black[]	= "#000000";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { green, black, black },
	[SchemeSel]  = { green, black,  green  },
};

/* scratch pads */
typedef struct {
	const char *name;
	const void *cmd;
}Sp;

/* tagging */
static const char *tags[] = { "[1]", "[2]", "[3]", "[4]", "[5]", "[6]", "[7]", "[8]" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ NULL,  "spterm",       NULL,       SPTAG(0),       1,           -1 },
	{ NULL,  "spwb",	 NULL,	     SPTAG(1),	     1,		  -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[D]",      deck },
	{ "[T]",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[B]",      bstack },
	{ "[H]",      bstackhoriz },
};

/* key definitions */
#define MODKEY Mod1Mask
#define SUPKEY Mod4Mask
#define TAGKEYS(CHAIN,KEY,TAG) \
	{ MODKEY,                       CHAIN,    KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             CHAIN,    KEY,      tag,            {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
//#define TERM "st"
#define TERM "xterm"
#define TOP "htop"
#define VIM "vim"
#define FM "noice"
#define BROWSER "qutebrowser"
#define BOOKMARKS "/home/will/Documents/Bookmarks/bookmarks.html"
#define HOMEPAGE "https://searx.be"

const char *spterm[] = { "st", "-n", "spterm", "-g", "120x34", NULL };
const char *spwb[] = { "st", "-n", "spwb", "-g", "120x34", "-e", "w3m", "https://searx.org", NULL };

static Sp scratchpads[] = {
	/* name, cmd */
	{"spterm", spterm},
	{"spwb", spwb},
};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,	                -1,        XK_space,  spawn,          {.v = (const char *[]){ TERM, NULL}}},
	{ ControlMask,		        -1,        XK_space,  togglescratch,  {.ui = 0}},
	{ ControlMask,			-1,        XK_b,      togglescratch,  {.ui = 1}},
	{ MODKEY,			-1,        XK_t,      spawn,	   {.v = (const char *[]){ TERM, "-e", TOP, NULL}}},
	{ MODKEY,			-1,        XK_f,      spawn,	   {.v = (const char *[]){ TERM, "-e", FM, NULL}}},
	{ MODKEY,			XK_w,      XK_b,      spawn,	   {.v = (const char *[]){ BROWSER, BOOKMARKS, NULL}}},
        { MODKEY,                       XK_w,      XK_s,      spawn,       {.v = (const char *[]){ BROWSER, "https://searx.org", NULL}}},
        { MODKEY,                       XK_w,      XK_w,      spawn,       {.v = (const char *[]){ BROWSER, "https://wiby.me", NULL}}},
	{ MODKEY,			XK_v,      XK_v,      spawn,	   {.v = (const char *[]){ TERM, "-e", VIM, NULL}}},
        { MODKEY,                       XK_v,      XK_i,      spawn,       {.v = (const char *[]){ TERM, "-e", "vi", NULL}}},
        { MODKEY,                       XK_v,      XK_t,      spawn,       {.v = (const char *[]){ TERM, "-e", "vi", "/home/will/TODO", NULL}}},
        { MODKEY,                       XK_v,      XK_f,      spawn,       {.v = (const char *[]){ TERM, "-e", "vifm", NULL}}},
	{ MODKEY,			XK_b,      XK_b,      spawn,	   {.v = (const char *[]){ TERM, "-e", "w3m", HOMEPAGE, NULL}}},
        { MODKEY,                       XK_b,      XK_s,      spawn,       {.v = (const char *[]){ TERM, "-e", "w3m", "https://searx.org", NULL}}}, 
        { MODKEY,                       XK_b,      XK_w,      spawn,       {.v = (const char *[]){ TERM, "-e", "w3m", "https://wiby.me", NULL}}},
	{ MODKEY,                       -1,        XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       -1,        XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       -1,        XK_l,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       -1,        XK_h,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       -1,        XK_Return, zoom,           {0} },
	{ MODKEY|ShiftMask,             -1,        XK_h,      setmfact,       {.f = -0.02} },
	{ MODKEY|ShiftMask,             -1,        XK_l,      setmfact,       {.f = +0.02} },
	{ MODKEY|ShiftMask,             -1,        XK_k,      setcfact,       {.f = +0.02} },
	{ MODKEY|ShiftMask,             -1,        XK_j,      setcfact,       {.f = -0.02} },
	{ MODKEY|ShiftMask,             -1,        XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             -1,        XK_d,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             -1,        XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             -1,        XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             -1,        XK_b,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             -1,        XK_p,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_semicolon,      XK_b,      togglebar,      {0} },
	{ MODKEY,			XK_semicolon,      XK_j,      spawn,	   {.v = (const char *[]){ "sndioctl", "output.level=-0.1", NULL}}},
	{ MODKEY,			XK_semicolon,      XK_k,      spawn,	   {.v = (const char *[]){ "sndioctl", "output.level=+0.1", NULL}}},
	{ MODKEY,			XK_semicolon,      XK_h,      spawn,	   {.v = (const char*[]){ "xbacklight", "-inc", "-10", NULL}}},
	{ MODKEY,			XK_semicolon,      XK_l,      spawn,	   {.v = (const char*[]){ "xbacklight", "-inc", "+10", NULL}}},
	TAGKEYS(                        -1,        XK_1,                      0)
	TAGKEYS(                        -1,        XK_2,                      1)
	TAGKEYS(                        -1,        XK_3,                      2)
	TAGKEYS(                        -1,        XK_4,                      3)
	TAGKEYS(                        -1,        XK_5,                      4)
	TAGKEYS(                        -1,        XK_6,                      5)
	TAGKEYS(                        -1,        XK_7,                      6)
	TAGKEYS(                        -1,        XK_8,                      7)
	{ MODKEY,             XK_semicolon,        XK_Escape,      quit,           {0} },
};
