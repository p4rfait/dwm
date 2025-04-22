/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=9:antialias=true:autohint=true" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=9:antialias=true:autohint=true";

/* Rose Pine colorscheme */
static const char col_base[]          = "#191724";
// static const char col_surface[]       = "#1f1d2e";
static const char col_overlay[]       = "#26233a";
// static const char col_muted[]         = "#6e6a86";
static const char col_subtle[]        = "#908caa";
static const char col_text[]          = "#e0def4";
// static const char col_love[]          = "#eb6f92";
// static const char col_gold[]          = "#f6c177";
static const char col_rose[]          = "#ebbcba";
// static const char col_pine[]          = "#31748f";
// static const char col_foam[]          = "#9ccfd8";
// static const char col_iris[]          = "#c4a7e7";
// static const char col_highlightlow[]  = "#21202e";
static const char col_highlightmed[]  = "#403d52";
// static const char col_highlighthigh[] = "#524f67";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_subtle, col_base, col_highlightmed },
	[SchemeSel]  = { col_text, col_overlay, col_rose  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	// { "Gimp",     NULL,       NULL,       0,            1,           -1 },
	// { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "", NULL, NULL, 0, 0, -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]          = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_base, "-nf", col_subtle, "-sb", col_overlay, "-sf", col_text, NULL };
static const char *termcmd[]           = { "st", NULL };
static const char *audiomute[]         = { "/usr/bin/wpctl", "set-mute", "@DEFAULT_SINK@", "toggle", NULL };
static const char *audiolowervolume[]  = { "/usr/bin/wpctl", "set-volume", "@DEFAULT_SINK@", "5%-", NULL };
static const char *audioraisevolume[]  = { "/usr/bin/wpctl", "set-volume", "-l", "1", "@DEFAULT_SINK@", "5%+", NULL };
static const char *audiomicmute[]      = { "/usr/bin/wpctl", "set-mute", "@DEFAULT_AUDIO_SOURCE@", "toggle", NULL };
static const char *monbrightnessdown[] = { "/usr/bin/light", "-U", "5", NULL };
static const char *monbrightnessup[]   = { "/usr/bin/light", "-A", "5", NULL };
static const char *audioplay[]         = { "/usr/bin/playerctl", "play-pause", NULL };
static const char *audiostop[]         = { "/usr/bin/playerctl", "stop", NULL };
static const char *audioprev[]         = { "/usr/bin/playerctl", "previous", NULL };
static const char *audionext[]         = { "/usr/bin/playerctl", "next", NULL };

static const Key keys[] = {
	/* modifier                     key                       function        argument */
	{ MODKEY,                       XK_p,                     spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,                spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,                     togglebar,      {0} },
	{ MODKEY,                       XK_j,                     focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                     incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                     incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                     setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                     setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,                zoom,           {0} },
	{ MODKEY,                       XK_Tab,                   view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,                     killclient,     {0} },
	{ MODKEY,                       XK_t,                     setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                     setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                     setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,                 setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                 togglefloating, {0} },
	{ MODKEY,                       XK_0,                     view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                     tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                 focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                 tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                                     0)
	TAGKEYS(                        XK_2,                                     1)
	TAGKEYS(                        XK_3,                                     2)
	TAGKEYS(                        XK_4,                                     3)
	TAGKEYS(                        XK_5,                                     4)
	TAGKEYS(                        XK_6,                                     5)
	TAGKEYS(                        XK_7,                                     6)
	TAGKEYS(                        XK_8,                                     7)
	TAGKEYS(                        XK_9,                                     8)
	{ MODKEY|ShiftMask,             XK_q,                     quit,           {0} },
	{ 0,                            XF86XK_AudioMute,         spawn,          {.v = audiomute } },
	{ 0,                            XF86XK_AudioLowerVolume,  spawn,          {.v = audiolowervolume } },
	{ 0,                            XF86XK_AudioRaiseVolume,  spawn,          {.v = audioraisevolume } },
	{ 0,                            XF86XK_AudioMicMute,      spawn,          {.v = audiomicmute } },
	{ 0,                            XF86XK_MonBrightnessDown, spawn,          {.v = monbrightnessdown } },
	{ 0,                            XF86XK_MonBrightnessUp,   spawn,          {.v = monbrightnessup } },
	{ 0,                            XF86XK_AudioPlay,         spawn,          {.v = audioplay } },
	{ 0,                            XF86XK_AudioStop,         spawn,          {.v = audiostop } },
  { 0,                            XF86XK_AudioPrev,         spawn,          {.v = audioprev } },
  { 0,                            XF86XK_AudioNext,         spawn,          {.v = audionext } },
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

