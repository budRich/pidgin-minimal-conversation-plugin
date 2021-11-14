# Pidgin minimal conversation

This plugin hides the extratitle thing and the menu-bar
in pidgins conversation windows.

## Compiling and installing the plugin

Install pre-requisite `pidgin-devel` and `libpurple-devel` packages. On Ubuntu:

	sudo apt-get build-dep pidgin
	sudo apt-get install pidgin-dev libpurple-dev

Compiling the plugin

	make

Installing the plugin to `~/.purple/plugins/`

	make install

Enable plugin *Minimal Conversation* from Pidgin plugins list.

## credits

i based this plugin on [pidgin-leftify-tabs-plugin] by nablaa.

[pidgin-leftify-tabs-plugin]: https://github.com/nablaa/pidgin-leftify-tabs-plugin
