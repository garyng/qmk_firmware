# `garyng/qmk_firmware`

My personal fork of [`qmk_firmware`](https://github.com/qmk/qmk_firmware) with some additional features.

> `master` is kept updated using [`wei/pull`](https://github.com/wei/pull).

# Additional Features

> Most of the features here are used with [`garyng/ahk-utilities`](https://github.com/garyng/ahk-utilities).

## HidGeneric

Extends [Hasu USB-USB Converter](https://geekhack.org/index.php?topic=69169.0)'s firmware to allow user to implement their own HID report parser. This is used for recognizing media keys on keyboards since they are ignored by the original firmware of the converter.

> Thanks to [@fauxpark](https://github.com/fauxpark) on QMK Discord server and [hasu@tmk](https://github.com/tmk) for helping!

## Wrapping Key

A key that acts like a layer switching key, but instead of switching layers, it will switch the "wrapping key", `wk`. A wrapping key is a key that wraps all other keys. For example, if you pressed `kc`, it will wrap it and send `<wk down> <kc1> <kc2> <wk up>` instead.

## Tap Auto Mod

This is a combination of QMK's [Tap Dance](https://beta.docs.qmk.fm/using-qmk/software-features/feature_tap_dance) and [Auto Shift](https://beta.docs.qmk.fm/using-qmk/software-features/feature_auto_shift) with a much simplified implementation.

Depends on the configuration, it will send different `<mod>` with the original `<kc>` based on how many times you tapped the key. For example, tap twice to send `Ctrl + <kc>` and tap thrice to send `Alt + <kc>`.

---

# Quantum Mechanical Keyboard Firmware

[![Current Version](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Build Status](https://travis-ci.org/qmk/qmk_firmware.svg?branch=master)](https://travis-ci.org/qmk/qmk_firmware)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![Docs Status](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub contributors](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

This is a keyboard firmware based on the [tmk\_keyboard firmware](https://github.com/tmk/tmk_keyboard) with some useful features for Atmel AVR and ARM controllers, and more specifically, the [OLKB product line](https://olkb.com), the [ErgoDox EZ](https://ergodox-ez.com) keyboard, and the [Clueboard product line](https://clueboard.co).

## Documentation

* [See the official documentation on docs.qmk.fm](https://docs.qmk.fm)

The docs are powered by [Docsify](https://docsify.js.org/) and hosted on [GitHub](/docs/). They are also viewable offline; see [Previewing the Documentation](https://docs.qmk.fm/#/contributing?id=previewing-the-documentation) for more details.

You can request changes by making a fork and opening a [pull request](https://github.com/qmk/qmk_firmware/pulls), or by clicking the "Edit this page" link at the bottom of any page.

## Supported Keyboards

* [Planck](/keyboards/planck/)
* [Preonic](/keyboards/preonic/)
* [ErgoDox EZ](/keyboards/ergodox_ez/)
* [Clueboard](/keyboards/clueboard/)
* [Cluepad](/keyboards/clueboard/17/)
* [Atreus](/keyboards/atreus/)

The project also includes community support for [lots of other keyboards](/keyboards/).

## Maintainers

QMK is developed and maintained by Jack Humbert of OLKB with contributions from the community, and of course, [Hasu](https://github.com/tmk). The OLKB product firmwares are maintained by [Jack Humbert](https://github.com/jackhumbert), the Ergodox EZ by [ZSA Technology Labs](https://github.com/zsa), the Clueboard by [Zach White](https://github.com/skullydazed), and the Atreus by [Phil Hagelberg](https://github.com/technomancy).

## Official Website

[qmk.fm](https://qmk.fm) is the official website of QMK, where you can find links to this page, the documentation, and the keyboards supported by QMK.
