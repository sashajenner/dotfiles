/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=15" };
static const char dmenufont[]       = "monospace:size=15";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_red[]         = "#770000";
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, col_cyan,  col_red },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
static const char *sptermcmd[] = { "st", "-n", "spterm", "-t", "scratchpad", "-g", "120x34", NULL };
static const char *spcalccmd[] = { "st", "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
static const char *sptodocmd[] = { "st", "-n", "sptodo", "-g", "80x30", "vim", "/home/en0cs/.todo", NULL };
static const char *spnotescmd[] = { "st", "-n", "spnotes", "-g", "80x30", "vim", "/home/en0cs/.notepad", NULL };
static const char *spcalendarcmd[] = { "st", "-n", "spcalendar", "-g", "80x30", "calcurse", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",       sptermcmd},
	{"spcalc",       spcalccmd},
    {"sptodo",       sptodocmd},
    {"spnotes",      spnotescmd},
	{"spcalendar",   spcalendarcmd},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class      instance       title             tags mask     isfloating   isterminal noswallow monitor */
    { "st",       "st-256color", "st",             0,            0,           1,         0,        -1 },
    { NULL,       NULL,          "Event Tester",   0,            0,           0,         1,        -1 },
	{ NULL,		  "spterm",	     NULL,		       SPTAG(0),	 1,		      1,         0,        -1 },
	{ NULL,		  "spcalc",      NULL,		       SPTAG(1),     1,		      0,	     0,        -1 },
	{ NULL,		  "sptodo",      NULL,		       SPTAG(2),     1,		      0,	     0,        -1 },
	{ NULL,		  "spnotes",     NULL,		       SPTAG(3),     1,		      0,	     0,        -1 },
	{ NULL,		  "spcalendar",  NULL,		       SPTAG(4),     1,		      0,	     0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "vanitygaps.c"

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[\\]",     dwindle },
    { "[@]",      spiral },
    { "[M]",      monocle },
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "TTT",      bstack },
    { ":::",      gaplessgrid },
    { "HHH",      grid },
    { "|M|",      centeredmaster },
    { ">M>",      centeredfloatingmaster },
    { NULL,       NULL },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *webcmd[]  = { "qutebrowser", NULL };
static const char *lockcmd[] = { "slock", NULL };
static const char *musiccmd[] = { "st", "ncmpcpp", NULL };
static const char *brightness_up_cmd[] = { "sudo", "/home/en0cs/.local/bin/bright-control", "up", NULL };
static const char *brightness_down_cmd[] = { "sudo", "/home/en0cs/.local/bin/bright-control", "down", NULL };
static const char *brightness_max_cmd[] = { "sudo", "/home/en0cs/.local/bin/bright-control", "max", NULL };
static const char *brightness_min_cmd[] = { "sudo", "/home/en0cs/.local/bin/bright-control", "min", NULL };
static const char *surfcamcmd[] = { "mpv", "--fs", "https://www.coastalwatch.com/surf-cams-surf-reports/nsw/bondi-beach" };
static const char *mountcmd[] = { "sudo", "/home/en0cs/.local/bin/dmenu-mount", NULL };
static const char *umountcmd[] = { "sudo", "/home/en0cs/.local/bin/dmenu-umount", NULL };
static const char *torrentcmd[] = { "st", "-e", "stig", NULL };
static const char *notescmd[] = { "st", "vim", "/home/en0cs/Documents/notes", NULL };

static Key keys[] = {
    /* modifier             key             function        argument */
    { MODKEY,               XK_p,           spawn,          {.v = dmenucmd } },
    { MODKEY,               XK_w,           spawn,          {.v = webcmd } },
    { MODKEY|ShiftMask,     XK_Return,      spawn,          {.v = termcmd } },
	{ MODKEY,            	XK_m,           spawn,          {.v = musiccmd } },
    { MODKEY,               XK_Up,          spawn,          {.v = brightness_up_cmd } },
    { MODKEY,               XK_Down,        spawn,          {.v = brightness_down_cmd } },
    { MODKEY,               XK_Page_Up,     spawn,          {.v = brightness_max_cmd } },
    { MODKEY,               XK_Page_Down,   spawn,          {.v = brightness_min_cmd } },
    { MODKEY,               XK_s,           spawn,          {.v = surfcamcmd } },
    { MODKEY|ShiftMask,     XK_p,           spawn,          {.v = torrentcmd } },
    { MODKEY,               XK_v,           spawn,          SHCMD("dmenu-vpn && pkill -RTMIN+2 dwmblocks") },
    { MODKEY|ShiftMask,     XK_v,           spawn,          {.v = notescmd } },
    { 0,                    XF86XK_AudioMute, spawn,        SHCMD("pactl set-sink-mute alsa_output.pci-0000_00_1f.3.analog-stereo toggle && pkill -RTMIN+1 dwmblocks") },
    { 0,                    XF86XK_AudioLowerVolume, spawn, SHCMD("amixer -q set Master 2%- && pkill -RTMIN+1 dwmblocks") },
    { 0,                    XF86XK_AudioRaiseVolume, spawn, SHCMD("amixer -q set Master 2%+ && pkill -RTMIN+1 dwmblocks") },
	{ 0,			        XF86XK_AudioPlay, spawn,		SHCMD("mpc toggle") },
	{ 0,			        XF86XK_AudioPrev, spawn,        SHCMD("mpc prev") },
	{ 0,			        XF86XK_AudioNext, spawn,		SHCMD("mpc next") },
    { MODKEY|ShiftMask,     XK_n,           spawn,          SHCMD("night-mode toggle") },
    { MODKEY,               XK_u,           spawn,          {.v = mountcmd } },
    { MODKEY|ShiftMask,     XK_u,           spawn,          {.v = umountcmd } },
    { MODKEY,               XK_b,           togglebar,      {0} },
    { MODKEY,               XK_j,           focusstack,     {.i = +1 } },
    { MODKEY,               XK_k,           focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,     XK_j,           inplacerotate,  {.i = +1} },
    { MODKEY|ShiftMask,     XK_k,           inplacerotate,  {.i = -1} },
    { MODKEY|ShiftMask,     XK_h,           inplacerotate,  {.i = +2} },
    { MODKEY|ShiftMask,     XK_l,           inplacerotate,  {.i = -2} },
    { MODKEY|ShiftMask,     XK_i,           incnmaster,     {.i = +1 } },
    { MODKEY|ShiftMask,     XK_d,           incnmaster,     {.i = -1 } },
    { MODKEY,               XK_h,           setmfact,       {.f = -0.05} },
    { MODKEY,               XK_l,           setmfact,       {.f = +0.05} },
    { MODKEY,               XK_Return,      zoom,           {0} },
    { MODKEY,               XK_minus,       incrgaps,       {.i = -1 } },
    { MODKEY,               XK_equal,       incrgaps,       {.i = +1 } },
    { MODKEY|ShiftMask,     XK_minus,       togglegaps,     {0} },
    { MODKEY|ShiftMask,     XK_equal,       defaultgaps,    {0} },
    { MODKEY,               XK_Tab,         view,           {0} },
    { MODKEY|ShiftMask,     XK_c,           killclient,     {0} },
    { MODKEY,               XK_r,           setlayout,      {.v = &layouts[0]} },
    { MODKEY|ShiftMask,     XK_r,           setlayout,      {.v = &layouts[1]} },
    { MODKEY|ShiftMask,     XK_m,           setlayout,      {.v = &layouts[2]} },
    { MODKEY,               XK_t,           setlayout,      {.v = &layouts[3]} },
    { MODKEY|ShiftMask,     XK_f,           setlayout,      {.v = &layouts[4]} },
    { MODKEY|ShiftMask,     XK_t,           setlayout,      {.v = &layouts[5]} },
    { MODKEY,               XK_g,           setlayout,      {.v = &layouts[6]} },
    { MODKEY|ShiftMask,     XK_g,           setlayout,      {.v = &layouts[7]} },
    { MODKEY,               XK_y,           setlayout,      {.v = &layouts[8]} },
    { MODKEY|ShiftMask,     XK_y,           setlayout,      {.v = &layouts[9]} },
	{ MODKEY,               XK_f,           fullscreen,     {0} },
    { MODKEY,               XK_space,       setlayout,      {0} },
    { MODKEY|ShiftMask,     XK_space,       togglefloating, {0} },
	{ MODKEY,               XK_i,           togglesticky,   {0} },
    { MODKEY,               XK_0,           view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,     XK_0,           tag,            {.ui = ~0 } },
    { MODKEY,               XK_comma,       focusmon,       {.i = -1 } },
    { MODKEY,               XK_period,      focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,     XK_comma,       tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,     XK_period,      tagmon,         {.i = +1 } },
	{ MODKEY,            	XK_o,           togglescratch,  {.ui = 0 } },
	{ MODKEY,            	XK_x,           togglescratch,  {.ui = 1 } },
	{ MODKEY,            	XK_d,           togglescratch,  {.ui = 2 } },
	{ MODKEY,            	XK_n,           togglescratch,  {.ui = 3 } },
	{ MODKEY,            	XK_z,           togglescratch,  {.ui = 4 } },
    TAGKEYS(                XK_1,                           0)
    TAGKEYS(                XK_2,                           1)
    TAGKEYS(                XK_3,                           2)
    TAGKEYS(                XK_4,                           3)
    TAGKEYS(                XK_5,                           4)
    TAGKEYS(                XK_6,                           5)
    TAGKEYS(                XK_7,                           6)
    TAGKEYS(                XK_8,                           7)
    TAGKEYS(                XK_9,                           8)
    { MODKEY|ShiftMask,     XK_q,           quit,           {0} },
    { MODKEY,               XK_Escape,      spawn,          {.v = lockcmd } },
	{ 0,			        XK_Print,       spawn,		    SHCMD("gnome-screenshot") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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
