/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 12;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 12;       /* vert inner gap between windows */
static const unsigned int gappoh    = 12;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 12;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "spleen:size=12" };
static const char color_black[] = "#000000";
static const char color_white[] = "#AAAAAA";
static const char color_green[] = "#295340";

static const char *colors[][3] = {
  /*               fg         bg         border   */
  [SchemeNorm] = { color_white, color_black, color_black },
  [SchemeSel] = { color_white, color_green, color_green },
};


/* tagging */
static const char *tags[] = { "[1]", "[2]", "[3]", "[4]", "[5]", "[6]", "[7]", "[8]", "[9]" };

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

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[d]",     dwindle },
	{ "[D]",      deck },
	{ "[B]",      bstack },
	{ "[b]",      bstackhoriz },
	{ "[#]",      grid },
	{ "[n]",      nrowgrid },
	{ "[H]",      horizgrid },
	{ "[g]",      gaplessgrid },
	{ "[m]",      centeredmaster },
	{ "[~]",      centeredfloatingmaster },
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
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
#define TERMINAL "xterm"

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };
static const char *filemanagercmd[]  = { TERMINAL, "-e", "vifm", NULL };
static const char *browsercmd[]  = { "firefox", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,             					XK_space,  spawn,          {.v = termcmd } },
	{ MODKEY,             					XK_f, 	 	 spawn,          {.v = filemanagercmd } },
	{ MODKEY,             					XK_w, 	 	 spawn,          {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_l,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_h,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.02} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.02} },
	{ MODKEY|ShiftMask,             XK_k,      setcfact,       {.f = +0.02} },
	{ MODKEY|ShiftMask,             XK_j,      setcfact,       {.f = -0.02} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ Mod4Mask,              				XK_h,      incrgaps,       {.i = +1 } },
	{ Mod4Mask,    									XK_l,      incrgaps,       {.i = -1 } },
	{ Mod4Mask,              				XK_k,      incrigaps,      {.i = +1 } },
	{ Mod4Mask,    									XK_j,      incrigaps,      {.i = -1 } },
	{ Mod4Mask,              				XK_o,      incrogaps,      {.i = +1 } },
	{ Mod4Mask|ShiftMask,    				XK_o,      incrogaps,      {.i = -1 } },
	{ Mod4Mask,              				XK_6,      incrihgaps,     {.i = +1 } },
	{ Mod4Mask|ShiftMask,    				XK_6,      incrihgaps,     {.i = -1 } },
	{ Mod4Mask,              				XK_7,      incrivgaps,     {.i = +1 } },
	{ Mod4Mask|ShiftMask,    				XK_7,      incrivgaps,     {.i = -1 } },
	{ Mod4Mask,              				XK_8,      incrohgaps,     {.i = +1 } },
	{ Mod4Mask|ShiftMask,    				XK_8,      incrohgaps,     {.i = -1 } },
	{ Mod4Mask,              				XK_9,      incrovgaps,     {.i = +1 } },
	{ Mod4Mask|ShiftMask,    				XK_9,      incrovgaps,     {.i = -1 } },
	{ Mod4Mask,              				XK_0,      togglegaps,     {0} },
	{ Mod4Mask|ShiftMask,    				XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_r,  		 setlayout,      {0} },
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
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

