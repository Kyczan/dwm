# dwm - dynamic window manager

This repo is a fork of [dwm](https://dwm.suckless.org) - an extremely fast, small, and dynamic window manager for X.

## Requirements

In order to build dwm you need the `Xlib` header files.

This fork is dependent on [KODO repo](https://github.com/Kyczan/kodo) (my dotfiles repo).

## Installation

```sh
make && sudo make install
```

## Running dwm

Add the following line to your .xinitrc to start dwm using startx:

```sh
exec dwm
```

In order to display status info in the bar, you can do something like this in your .xinitrc:

```sh
while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
do
    sleep 1
done &
exec dwm
```

Quite nice status bar can be found in [KODO repo](https://github.com/Kyczan/kodo) (my dotfiles repo). Just look into `bin/bin/set-dwm-status-bar` file.

## Configuration

The configuration of dwm is done by creating a custom config.h and (re)compiling the source code.

My keybindings (need to setup [KODO](https://github.com/Kyczan/kodo) to make them work):

- `MODKEY` - `WIN`
- `MODKEY + d` - spawn `rofi` in `dmenu` mode with all instaled programs
- `MODKEY + Enter` - spawn `st` terminal (see my [fork](https://github.com/Kyczan/st) of `st`)
- `MODKEY + i` - show list of glyphicons
- `MODKEY + p` - show power menu (lock, restart dwm statusbar, suspend, reboot, power off)
- `MODKEY + u` - run system and programs updates
- `MODKEY + n` - run network manager
- `MODKEY + w` - show current weather in `dunst` notification
- `ALT + TAB` - switch active progrms iside tag
- bunch of multimedia keys (vol up/down, etc.)

## Patches

Following [patches](https://dwm.suckless.org/patches/) are already applied:

- modified [activetagindicatorbar](https://dwm.suckless.org/patches/activetagindicatorbar/) - bar above tag instead of square dot
- [notitle](https://dwm.suckless.org/patches/notitle/) - remove title
- [pertag](https://dwm.suckless.org/patches/pertag/) - keep layout per tag
- [ru gaps](https://dwm.suckless.org/patches/ru_gaps/) - gaps between tiles
- [status2d](https://dwm.suckless.org/patches/status2d/) - enable colors in status bar
- [systray](https://dwm.suckless.org/patches/systray/) - enable systray

To apply another patch use following command:

```sh
git apply -3 --ignore-whitespace /path/to/patch.diff
```

But be careful. When patch modifies `config.def.h` copy these changes to `config.h` and reset state of first file:

```sh
git reset HEAD config.def.h
git checkout -- config.def.h
```

Then repeat [installation](#installation) process.

## Sync with original dwm

Add `upstream` to original repo:

```sh
git remote add upstream git://git.suckless.org/dwm
```

Every time you want to sync type:

```sh
git fetch upstream
git checkout master
git merge upstream/master
```

This brings your `master` branch into sync with the upstream repository, without losing your local changes.
For reference check this [github article](https://help.github.com/articles/syncing-a-fork/)

Then repeat [installation](#installation) process.
