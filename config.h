/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 20;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     	/* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#282A36";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#f8f8f2";
static const char col_gray4[]       = "#f8f8f2";
static const char col_cyan[]        = "#44475a";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "  ", "  ", "  ", "  ", "  ", "  " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      				instance    title       tags mask     isfloating   monitor */
	{ "Vivaldi-stable",  	NULL,       NULL,       1 << 0,       0,           -1 },
	{ "VSCodium",  				NULL,       NULL,       1 << 2,       0,           -1 },
	{ "Google-chrome", 		"crx_haiffjcadagjlijoggckpgfnoeiflnem", 
																		NULL, 			1 << 3, 	  	0,           -1 },
	{ "TelegramDesktop",  NULL,       NULL,       1 << 4,       0,           -1 },
	{ "Spotify",  				NULL,       NULL,       1 << 5,       0,           -1 },
	{ "st-256color",  		"sthacli",  NULL,       0,       			1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol   arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
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
static const char *dmenucmd[] = { "rofi", "-modi", "drun", "-show", "drun", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *iconscmd[]  = { "dmenu-icons", NULL };
static const char *powercmd[]  = { "dmenu-power", NULL };
static const char *updatecmd[]  = { "run-updates", NULL };
static const char *networkcmd[]  = { "nm-connection-editor", NULL };
static const char *weathercmd[]  = { "dunst-weather", NULL };
static const char *vivaldicmd[]  = { "vivaldi-stable", NULL };
static const char *citrixcmd[]  = { "google-chrome-stable", "--app-id=haiffjcadagjlijoggckpgfnoeiflnem", NULL };
// static const char *sthaclicmd[]  = { "run-sthacli", NULL };
static const char *haclidmenucmd[]  = { "ha-cli-dmenu", NULL };
static const char *teilercmd[]  = { "teiler", NULL };
// volume control:
static const char *volupcmd[]  = { "pactl", "set-sink-volume",  "@DEFAULT_SINK@", "+5%", NULL };
static const char *voldowncmd[]  = { "pactl", "set-sink-volume",  "@DEFAULT_SINK@", "-5%", NULL };
static const char *voltogglecmd[]  = { "pactl", "set-sink-mute",  "@DEFAULT_SINK@", "toggle", NULL };
// brightnes control:
static const char *brightupcmd[]  = { "xbacklight", "-inc",  "20", NULL };
static const char *brightdowncmd[]  = { "xbacklight", "-dec",  "20", NULL };
// audio control:
static const char *audionextcmd[]  = { "playerctl", "next", NULL };
static const char *audioprevcmd[]  = { "playerctl", "previous", NULL };
static const char *audioplaypausecmd[]  = { "playerctl", "play-pause", NULL };
// touchpad control:
static const char *touchpadcmd[]  = { "touchpad-toggle", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             					XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,             					XK_i,	   	 spawn,          {.v = iconscmd } },
	{ MODKEY,             					XK_p,	   	 spawn,          {.v = powercmd } },
	{ MODKEY,             					XK_u,	   	 spawn,          {.v = updatecmd } },
	{ MODKEY,             					XK_n,	   	 spawn,          {.v = networkcmd } },
	{ MODKEY,             					XK_w,	   	 spawn,          {.v = weathercmd } },
	{ MODKEY,             					XK_s,	   	 spawn,          {.v = haclidmenucmd } },
	{ MODKEY,             					XK_v,	   	 spawn,          {.v = vivaldicmd } },
	{ MODKEY,             					XK_c,	   	 spawn,          {.v = citrixcmd } },
	{ 0,         			 							XK_Print,  spawn,          {.v = teilercmd } },
	{ 0,         XF86XK_AudioRaiseVolume,	   	 spawn,          {.v = volupcmd } },
	{ 0,         XF86XK_AudioLowerVolume,	   	 spawn,          {.v = voldowncmd } },
	{ 0,           			XF86XK_AudioMute,	   	 spawn,          {.v = voltogglecmd } },
	{ 0,          XF86XK_MonBrightnessUp,	   	 spawn,          {.v = brightupcmd } },
	{ 0,        XF86XK_MonBrightnessDown,	   	 spawn,          {.v = brightdowncmd } },
	{ 0,          			XF86XK_AudioNext,	   	 spawn,          {.v = audionextcmd } },
	{ 0,          			XF86XK_AudioPrev,	   	 spawn,          {.v = audioprevcmd } },
	{ 0,          			XF86XK_AudioPlay,	   	 spawn,          {.v = audioplaypausecmd } },
	{ 0,          	   XF86XK_AudioPause,	   	 spawn,          {.v = audioplaypausecmd } },
	{ 0,           XF86XK_TouchpadToggle,	   	 spawn,          {.v = touchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ Mod1Mask,                     XK_Tab,    focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_j,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,             					XK_space,  zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_Tab,    view,           {0} },
	{ MODKEY,             					XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_Return, setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
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
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

