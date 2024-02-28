/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 25;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int baralpha = 0x0D;
static const unsigned int borderalpha = OPAQUE;

static const unsigned int alphas[][3]      = {
  /*               fg      bg        border*/
  [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

#if defined(__FreeBSD__)
static const char *fonts[]          = { "terminus:bold:size=10", "FontAwesome:size=10" };
#endif /* __FreeBSD__ */

#if defined(__linux__) || defined(__NetBSD__) || defined(__OpenBSD__)
static const char *fonts[]          = { "mono:size=10", "FontAwesome" };
#endif /* __linux__ & __NetBSD__ & __OpenBSD__ */

static const char col_black[]       = "#000000";
static const char col_white[]       = "#FFFFFF";
static const char col_grey[]        = "#AAAAAA";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_black,  col_black },
	[SchemeSel]  = { col_white, col_black,  col_white  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "librewolf",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "firefox",    NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "\uf0c9",      tile },    /* first entry is default */
	{ "\uf0c2",      NULL },    /* no layout function means floating behavior */
	{ "\uf04d",      monocle },
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
#define TERMINAL "st"

#if defined(__NetBSD__)
static const char *volume_up[]   = { "mixerctl", "-w", "outputs.master+=10", NULL };
static const char *volume_down[] = { "mixerctl", "-w", "outputs.master-=10", NULL };
static const char *volume_mute[] = { "mixerctl", "-w", "outputs.mute", NULL };
static const char *brightness_up[] = { "intel_backlight", "incr", NULL };
static const char *brightness_down[] = { "intel_backlight", "decr", NULL };
#endif /* __NetBSD__ */

#if defined(__OpenBSD__)
static const char *volume_up[]   = { "sndioctl", "output.level=+0.1", NULL };
static const char *volume_down[] = { "sndioctl", "output.level=-0.1", NULL };
static const char *volume_mute[] = { "sndioctl", "output.mute", NULL };
static const char *brightness_up[] = { "xbacklight", "-inc", "5" NULL };
static const char *brightness_down[] = { "xbacklight", "-dec", "5" NULL };
#endif /* __OpenBSD__ */

#if defined(__linux__)
static const char *volume_up[]   = { "amixer", "set", "Master", "10%-", NULL };
static const char *volume_down[] = { "amixer", "set", "Master", "10%+", NULL };
static const char *volume_mute[] = { "amixer", "set", "Master", "toggle", NULL };
#endif /* __linux__ */

#if defined(__FreeBSD__)
static const char *volume_up[]     = { "mixer", "vol=+0.1", NULL };
static const char *volume_down[]   = { "mixer", "vol=-0.1", NULL };
static const char *volume_mute[]   = { "mixer", NULL }; // TODO
static const char *brightness_up[] = { "intel_backlight", "incr", NULL };
static const char *brightness_down[] = { "intel_backlight", "decr", NULL };
#endif /* __FreeBSD__ */

#include <X11/XF86keysym.h>

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };
static const char *browser[]  = { "librewolf", NULL };
static const char *office[]   = { "libreoffice", NULL };
static const char *vifm[]     = { TERMINAL, "-e", "vifm", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
  { 0,                     XF86XK_AudioLowerVolume,  spawn,  { .v = volume_down } },
  { 0,                     XF86XK_AudioRaiseVolume,  spawn,  { .v = volume_up } },
  { 0,                     XF86XK_AudioMute,         spawn,  { .v = volume_mute } },
	{ 0,                     XF86XK_MonBrightnessUp,   spawn,  { .v = brightness_up } },
	{ 0,                     XF86XK_MonBrightnessDown, spawn,  { .v = brightness_down } },
	{ MODKEY,                       XK_F1,     spawn,          { .v = brightness_down   } },
	{ MODKEY,                       XK_F2,     spawn,          { .v = brightness_up } },
	{ MODKEY,                       XK_F12,    spawn,          { .v = volume_up   } },
	{ MODKEY,                       XK_F11,    spawn,          { .v = volume_down } },
	{ MODKEY,                       XK_t,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = browser } },
	{ MODKEY,                       XK_f,      spawn,          {.v = vifm    } },
	{ MODKEY,                       XK_o,      spawn,          {.v = office  } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_l,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_h,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      setcfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_k,      setcfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
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

