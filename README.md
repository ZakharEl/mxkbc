# NAME

mxkbc - modular X key bind client - client for mxkbd to add, list, remove, and set keybinds and keybind modes

# EXAMPLES

Adding keybind modes

![Adding keybind modes](media/add-keybind-modes.gif)

Setting the selected mode

![Setting the selected mode](media/set-selected-mode.gif)

Adding keybinds

![Adding keybinds](media/add-keybinds.gif)

Removing a keybind

![Removing a keybind](media/remove-keybind.gif)

Listing keybinds

![Listing keybinds](media/list-all-keybinds.gif)

Listing keybind descriptions

![Listing keybind descriptions](media/list-all-keybind-descriptions.gif)

Listing all modes

![Listing all modes](media/list-all-keybind-modes.gif)

Setting a mode description

![Setting a mode description](media/set-keybind-mode-description.gif)

Removing a mode

![Removing a mode](media/remove-mode.gif)

# SYNOPSIS

**mxkbc** [*MXKBC_OPTIONS*] *OPERATION MODE_OPTION OPERATION_ARGS*

**mxkbc** [*MXKBC_OPTIONS*] *OPERATION* k\|keybind [*MODE_OPTION*] *OPERATION_ARGS*

# DESCRIPTION

**mxkbc** is a client for **mxkbd**. This client is where one configures **mxkbd** through **mxkbd**'s arguments. **mxkbd** must first be started before using **mxkbc**.

# INSTALLATION

Open a terminal and run
```sh
git clone https://github.com/ZakharEl/mxkbc
```
. Then **cd** into the clone directory and run
```sh
sudo make install
```

# MXKBC_OPTIONS

**-s** *SOCKET_FILE_PATH*
change the file that is to be used to communicated with **mxkbd** to *SOCKET_FILE_PATH*.

# OPERATIONS

*OPERATION* is performed on keybinds if k or keybind is specified immediately after *OPERATION*. Otherwise it is performed on modes. Valid values for *OPERATION* are as follows:

**l**,**list**

> **list** out property of mode(s) or keybind(s) to standard output.

**a**,**add**

> **add** a mode or keybind.

**r**,**remove**

> **remove** a mode or keybind.

**s**,**set**

> **set** property of a mode or keybind.

# MODE_OPTION

*MODE_OPTION* specifies the mode to act on - defaults to the selected mode (the mode indicated by the mode option *-s*). It is obligatory if *OPERATION* is not performed on keybinds. Otherwise it is only necessary if the mode to operate the keybind *OPERATION* on is not the mode set to be the selected mode. Valid values for the MODE_OPTION are the following:

**-g**  
*OPERATION* is performed on the mode set to be the grabbed mode

**-d**  
*OPERATION* is performed on the mode set to be the default mode

**-s**  
*OPERATION* is performed on the mode set to be the selected mode

**-a**  
This is only applicable to the **list** operation when done **on modes**. This will list out the value of *PROPERTY* of for each and every mode (see below). With the **list** operation **on keybinds** this is a **list arg** (see below).

**-m** *MODE_NAME*

for *OPERATIONS* on keybinds and...

**m**\|**mode** *MODE_NAME*

for *OPERATIONS* on modes

> *OPERATION* is performed on the mode that has *MODE_NAME* as its name (mode.name == *MODE_NAME*). Furthermore take note that this is the only acceptable *MODE_OPTION* for the **add** operation when done **on** a **mode**.

# add args

## on mode

[*DESCRIPTION*]

Take note that the only acceptable *MODE_OPTION* is

**m**\|**mode** *MODE_NAME*

(thus full form

**mxkbc** add m\|mode *MODE_NAME* [*DESCRIPTION*]

).

## on keybind

*SEQ FILE_OR_COMMAND* [*DESCRIPTION*]

# remove args

## on mode

No *OPERATION_ARGS* are available. Only *MODE_OPTION* is applicable.

## on keybind

*SEQ*

# set args

## on mode

**-g**\|**-s**\|**-d**

*PROPERTY VALUE*

## on keybind

*SEQ PROPERTY VALUE*

# list args

## on mode(s)

[*PROPERTY*]

## on keybind(s)

**-a** [*PROPERTY*]

*SEQ* [*PROPERTY*]

# OPERATION_ARGS

**SEQ**

> key sequence to trigger execution of *FILE_OR_COMMAND*. Keys are seperated by +.

**FILE_OR_COMMAND**

> file or command to execute upon pressing all the keys in *SEQ* in the order specified. If *FILE_OR_COMMAND* is set to - (*FILE_OR_COMMAND* == "-") then *FILE_OR_COMMAND* is set to the content of standard input. Furthermore if standard input is not available it will be set in a manner similar to the **cat** command.

**PROPERTY**

> property of keybind or mode to **set** to *VALUE* or **list**. Valid values are the following:
>
> **d**,**description**
>
> > Description of what a keybind or mode does or is for.
>
> **c**,**command**
>
> > The command executed when the keys within *SEQ* are all pressed as specified. Only relevant for *OPERATIONS* performed **on keybind(s)**.
>
> **n**,**name**
>
> > The name of the mode of the current *OPERATION*. Only relevant for *OPERATIONS* performed **on mode(s)**. If a *PROPERTY* is not specified for the **list** operation then this will be the property whose *VALUE* is displayed.
>
> **s**,**seq**
>
> > The sequence of keys that need be pressed to trigger *FILE_OR_COMMAND*. Only relevant for *OPERATIONS* performed **on keybind(s)**. If a *PROPERTY* is not specified for the **list** operation then this will be the property whose *VALUE* is displayed.

**VALUE**

> Value to set property of a keybind or mode specified by *PROPERTY* to.

**DESCRIPTION**

> Description of what a keybind or mode does or is for.

**-g**

> Only applicable with the set operation when done **on** a **mode**. Set the grabbed mode to this *OPERATION*'s mode. Not to be confused with *MODE_OPTION*'s **-g **option.

**-s**

> Only applicable with the set operation when done **on** a **mode**. Set the selected mode to this *OPERATION*'s mode. Not to be confused with *MODE_OPTION*'s **-s **option.

**-d**

> Only applicable with the set operation when done **on** a **mode**. Set the default mode to this *OPERATION*'s mode. Not to be confused with *MODE_OPTION*'s **-d **option.

**-a**

> This is only applicable to the **list** operation when done **on keybinds**. This will list out the value of *PROPERTY* of for each and every keybind of the **list** operation. With the **list** operation **on modes** this is a *MODE_OPTION* (see above).

# AUTHORS

Written by Zachary Schlitt \<ztschlitt@gmail.com>

# LICENSE

GPL 3.0
