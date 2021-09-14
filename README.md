# VobSub2SRT

VobSub2SRT is a simple command line program to convert `.idx` / `.sub` subtitles into `.srt` text subtitles by using OCR.
It is based on code from the [MPlayer project](http://www.mplayerhq.hu) - a really really great movie player.
Some minor parts are copied from [ffmpeg/avutil](http://ffmpeg.org/) headers.
[Tesseract](http://code.google.com/p/tesseract-ocr/) is used as OCR software.

VobSub2Srt is released under the GPL3+ license.
The MPlayer code included is GPL2+ licensed.

The quality of the OCR depends on the text in the subtitles.
Currently the code inverts and makes the images black and white only.
Filters and scaling options are being looked at to improve the OCR.
Mistakes in the `.srt` files can be corrected with a text editor or a special subtitle editor.

## Building

Tesseract and must be installed to build, the data files for the languages you want to use should also be installed.
VobSub2Srt uses cmake so it must be installed to properly build the project.
A recent version of gcc or clang will also be necessary to compile the project.

On a Debian based system the following should install everything needed to build.

``` bash
sudo apt-get install libtiff5-dev libtesseract-dev tesseract-ocr-eng build-essential cmake pkg-config
```

Once all of the build requirements have been satisfied VobSub2Srt can be built using the following.

``` bash
./configure
make -j4
```

To install the project on the current system run the following command.

``` bash
sudo make install
```

The program will be installed to `/usr/local/bin`.

To uninstall VobSub2Srt run the following command.

``` bash
sudo make uninstall
``` 

## Usage

VobSub2Srt converts subtitles in VobSub (`.idx` / `.sub`) format into subtitles in SubRip (`.srt`) format.
VobSub subtitles consist of two or three files called `Filename.idx`, `Filename.sub`, and an optional `Filename.ifo`.
To convert subtitles simply call:

``` bash
vobsub2srt Filename
```

with `Filename` being the file name of the subtitle files *WITHOUT* the extension (`.idx` / `.sub`).
VobSub2Srt writes the converted subtitles to a file called `Filename.srt`.

If a subtitle file contains more than one language use the `--lang` parameter to set the correct language.
Use the `--langlist` parameter to find out about the languages in the file.
For some languages the tesseract language needs to be manually set (e.g., chi_tra/chi_sim for traditional or simplified chinese characters).
Use the `--tesseract-lang` parameter to manually set the tesseract language, in most cases this should be autodetected.

To dump the subtitles as images (e.g. to check for correct OCR) pass the `--dump-images` parameter.

Use `--help` or read the manpage to get more information about the options of VobSub2Srt.
