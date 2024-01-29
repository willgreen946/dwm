/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 0; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int startwithgaps[] = {
  1
}; /* 1 means gaps are used by default, this can be customized for each tag */
static const unsigned int gappx[]
    = { 10 }; /* default gap between windows in pixels, this can be customized
                 for each tag */

static unsigned int baralpha = 0xd0;
static unsigned int borderalpha = OPAQUE;
static const int showbar = 1; /* 0 means no bar */
static const int topbar = 1;  /* 0 means bottom bar */
static const char *fonts[] = { "spleen:size=10", "FontAwesome" };
static const char color_black[] = "#000000";
static const char color_white[] = "#AAAAAA";
static const char *colors[][3] = {
  /*               fg         bg         border   */
  [SchemeNorm] = { color_white, color_black, color_black },
  [SchemeSel] = { color_black, color_white, color_white },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
  /* xprop(1):
   *	WM_CLASS(STRING) = instance, class
   *	WM_NAME(STRING) = title
   */
  /* class      instance    title       tags mask     isfloating   monitor */
  { "Gimp", NULL, NULL, 0, 1, -1 },
  { "Firefox", NULL, NULL, 1 << 8, 0, -1 },
  { "qutebrowser", NULL, NULL, 1 << 8, 0, -1 },
  { "libreoffice", NULL, NULL, 1 << 7, 0, -1 },
};

/* layout(s) */
static const float mfact = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints
    = 0; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen
    = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
  /* symbol     arrange function */
  { "[]=", tile },
  { "[M]", monocle }, /* first entry is default */
  { "><>", NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask /* Super/Windows key */
#define TAGKEYS(KEY, TAG)                                                     \
  { MODKEY, KEY, view, { .ui = 1 << TAG } },                                  \
      { MODKEY | ControlMask, KEY, toggleview, { .ui = 1 << TAG } },          \
      { MODKEY | ShiftMask, KEY, tag, { .ui = 1 << TAG } },                   \
      { MODKEY | ControlMask | ShiftMask,                                     \
        KEY,                                                                  \
        toggletag,                                                            \
        { .ui = 1 << TAG } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                            \
  {                                                                           \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                      \
  }
#define TERMINAL "st"

/* commands */
static const char *spawn_terminal[] = { TERMINAL, NULL };
static const char *spawn_filemanager[] = { TERMINAL, "-e", "vifm", NULL };
static const char *spawn_office[] = { "libreoffice", NULL };
static const char *spawn_browser[] = { "qutebrowser", NULL };

#if defined(__OpenBSD__)
static const char *volume_up[] = { "sndioctl", "output.level=+0.1", NULL };
static const char *volume_down[] = { "sndioctl", "output.level=-0.1", NULL };
static const char *volume_mute[] = { "sndioctl", "output.mute", NULL };
#endif /* __OpenBSD__ */

#if defined(__linux__)
static const char *volume_up[] = { "amixer", "set", "Master", "10%-", NULL };
static const char *volume_down[] = { "amixer", "set", "Master", "10%+", NULL };
static const char *volume_mute[]
    = { "amixer", "set", "Master", "toggle", NULL };
#endif /* __linux__ */

#include <X11/XF86keysym.h>

static const Key keys[] = {
  /* modifier                     key        function        argument */
  { 0, XF86XK_AudioLowerVolume, spawn, { .v = volume_down } },
  { 0, XF86XK_AudioRaiseVolume, spawn, { .v = volume_up } },
  { 0, XF86XK_AudioMute, spawn, { .v = volume_mute } },
  { MODKEY | ShiftMask, XK_Return, spawn, { .v = spawn_terminal } },
  { MODKEY, XK_f, spawn, { .v = spawn_filemanager } },
  { MODKEY, XK_w, spawn, { .v = spawn_browser } },
  { MODKEY, XK_o, spawn, { .v = spawn_office } },
  { MODKEY | ShiftMask, XK_b, togglebar, { 0 } },
  { MODKEY, XK_j, focusstack, { .i = +1 } },
  { MODKEY, XK_k, focusstack, { .i = -1 } },
  { MODKEY, XK_i, incnmaster, { .i = +1 } },
  { MODKEY, XK_d, incnmaster, { .i = -1 } },
  { MODKEY | ShiftMask, XK_h, setmfact, { .f = -0.02 } },
  { MODKEY | ShiftMask, XK_l, setmfact, { .f = +0.02 } },
  { MODKEY | ShiftMask, XK_k, setcfact, { .f = +0.02 } },
  { MODKEY | ShiftMask, XK_j, setcfact, { .f = -0.02 } },
  { MODKEY, XK_Return, zoom, { 0 } },
  { MODKEY, XK_Tab, view, { 0 } },
  { MODKEY | ShiftMask, XK_c, killclient, { 0 } },
  { MODKEY, XK_t, setlayout, { .v = &layouts[0] } },
  { MODKEY, XK_m, setlayout, { .v = &layouts[1] } },
  { MODKEY, XK_space, setlayout, { 0 } },
  { MODKEY | ShiftMask, XK_space, togglefloating, { 0 } },
  { MODKEY, XK_0, view, { .ui = ~0 } },
  { MODKEY | ShiftMask, XK_0, tag, { .ui = ~0 } },
  { MODKEY, XK_comma, focusmon, { .i = -1 } },
  { MODKEY, XK_period, focusmon, { .i = +1 } },
  { MODKEY | ShiftMask, XK_comma, tagmon, { .i = -1 } },
  { MODKEY | ShiftMask, XK_period, tagmon, { .i = +1 } },
  { MODKEY, XK_minus, setgaps, { .i = -1 } },
  { MODKEY, XK_equal, setgaps, { .i = +1 } },
  { MODKEY | ShiftMask, XK_minus, setgaps, { .i = GAP_RESET } },
  { MODKEY | ShiftMask, XK_equal, setgaps, { .i = GAP_TOGGLE } },
  TAGKEYS (XK_1, 0) TAGKEYS (XK_2, 1) TAGKEYS (XK_3, 2) TAGKEYS (XK_4, 3)
      TAGKEYS (XK_5, 4) TAGKEYS (XK_6, 5) TAGKEYS (XK_7, 6) TAGKEYS (XK_8, 7)
          TAGKEYS (XK_9, 8){ MODKEY | ShiftMask, XK_q, quit, { 0 } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
  /* click                event mask      button          function argument
   */
  { ClkLtSymbol, 0, Button1, setlayout, { 0 } },
  { ClkLtSymbol, 0, Button3, setlayout, { .v = &layouts[2] } },
  { ClkWinTitle, 0, Button2, zoom, { 0 } },
  { ClkClientWin, MODKEY, Button1, movemouse, { 0 } },
  { ClkClientWin, MODKEY, Button2, togglefloating, { 0 } },
  { ClkClientWin, MODKEY, Button3, resizemouse, { 0 } },
  { ClkTagBar, 0, Button1, view, { 0 } },
  { ClkTagBar, 0, Button3, toggleview, { 0 } },
  { ClkTagBar, MODKEY, Button1, tag, { 0 } },
  { ClkTagBar, MODKEY, Button3, toggletag, { 0 } },
};
