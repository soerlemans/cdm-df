# cdm-df - cdm with doom fire animation
This project is a C rewrite of cdm adding functionalities to make it look and perform better.
The program itself is literally a dialogue that has animations and its own config.

## General info
Its written in C and uses the following libraries/headers:
* ncurses.h
* menu.h
* libconfig.h
(These libraries/headers are often already installed on a ton of distros)

## Installation
As of now you can install it by building the project with ``` make install clean ``` this will install the program with its default config.
The program gets installed to ``` /usr/local/bin  ```, the default config gets installed to ``` /etc/cdm-df/ ```.

If you want you can copy ``` cdm-df.sh ``` from the ``` scripts ``` directory in the project to ``` /etc/profile.d/ ``` so it launches upon login.
In this script you can specify on which tty's you want it to run.

## Usage
You can specify the commands and names in the config file in the following config locations:
* ~/.config/cdm-df/config
* /etc/cdm-df/config

The program just outputs the option you picked to ``` stdout  ``` so you can do this:
``` cdm-df | sh ```
This will run the command you select in the menu and sh will interpret the text as a command, an advantage of this is that you can grab cdm and just replace the dialogue command with cdm-df.
(cdm is just a bunch of bash scripts)

## How the program looks


