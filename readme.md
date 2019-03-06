
# Building Flash Apps with TI Flash Studio and Sierra 68k C Compiler

The purpose of this repository is to provide comprehensive information on how to
set up TI Flash Studio and/or the Sierra 68k C Compiler and how to get started
building FlashApps for TI 68k calculators (TI-89 (Titanium), TI-92 Plus and
TI Voyage 200).

## Overview
The TI Flash Studio IDE itself only works on Windows XP, so if you want to use
the IDE then you need to run it in a virtual machine or on an older PC. The
reason for this is that the IDE uses the discontinued Microsoft Java Virtual
Machine.

However all the underlying build tools (compiler, assembler, linker, ...) don't
have this dependency, which means they can be used on newer Windows versions
like 7 or 10, and probably even on Linux (with Wine).

You can also run the build tools in the cloud (AppVeyor cloud in the example).
This is also the best way to get started with minimal effort. Take a look at the
"AppVeyor cloud build" section if you want to use this.

Feel free to send me an email (daniel_eisele@gmx.de) if you have any questions.

## Files and checksums
These are all the files used in this document. There are two versions of TI
Flash Studio, a newer version (FlashStudio1.1.43.exe) and an older version
(TIFlashStudio.exe/fsinst_1.1.34.exe). I use the newer version, but I don't
think that it has any relevant benefits over the older one.

The two PDF files are very important, you won't get very far without them...

So if can't get any of the files, then please contact me (daniel_eisele@gmx.de).
Also if you want to host these files (I don't want to do it for legal reasons),
please let me know.

| File name                                                                                                                                              | SHA256 checksum                                                  |
|--------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------|
| [FlashStudio1.1.43.exe](https://cchsindy.org/bird/TTT/FlashStudio1.1.43.exe)                                                                           | 7852ADD8B12BB1E138F7F3C1E8FB1AF127CEA00F1D0A15D1F4583FB96216DEC0 |
| [TIFlashStudio.exe](https://web.archive.org/web/20130712132409/http://isa.umh.es/calc/TI/TI89-92SDK/TIFlashStudio.exe) (also called fsinst_1.1.34.exe) | 93DE72CD174A947A351790EBF240FD0444C27F129CE35BF5B7E8DE54E42331B9 |
| [msjavx86.exe](http://java-virtual-machine.net/download.html)                                                                                          | 03E38318FA34AD2AEFF00517AE6D72E05588509E1C549D9147029483D08CF2B5 |
| [e_wise.arj](https://kannegieser.net/veit/programm/e_wise.arj)                                                                                         | A2FC915847EE397A7B28C346B50852EE3BB477B5AEC41384DD47742220B2A0DD |
| [sdk8992pguide.pdf](https://web.archive.org/web/20130712132251/http://isa.umh.es/calc/TI/TI89-92SDK/sdk8992pguide.pdf)                                 | 5ECE362291188E03025291B1421A1B62E9FD28609907C12F793DC158DCEFC19F |
| [sdk8992pcompiler.pdf](https://web.archive.org/web/20130712132305/http://isa.umh.es/calc/TI/TI89-92SDK/sdk8992pcompiler.pdf)                           | 51B842428C8D76A243F2C6A0510349737B2ABA0ECF815E166E9368E650CC7D9C |

## IDE (Windows XP only)
Before installing TI Flash Studio you first have to install the Microsoft Java
Virtual Machine (msjavx86.exe).

After that you can run the TI Flash Studio installer (FlashStudio1.1.43.exe or
fsinst_1.1.34.exe). I personally use the newer one (FlashStudio1.1.43.exe), but
I don't think that the new version has any relevant benefits, so it shouldn't
matter which one you use.

After the installation is finished add the directory
"C:\\\<programs\>\\\<shared files\>\\TI Shared\\TI Flash Studio" to your PATH
variable to get some debugger features working. Replace \<programs\> and
\<Shared Files\> with the actual folder names.

To be able to later use your FlashApps on a real calculator, they must be signed
with a cryptographic key. To achieve that, you have to replace the content of
the default key file (sdk-92p.key, located in the program folder of TI Flash
Studio) with the new key.

The TI-92 Plus Flash application key looks like this:

    0101
    406104CDFAD955D41F1ECCB9B622007FE8BC75E8B28DA178334755FEF27C564D47B04FD82498C163B762991C68CF64E29236BC41A4C1BCB9793B6EE965407C74BC
    40E17C4AA4C942CC57282E9B911E7B39352A2D8D4EC15398366C971FF7D2D92FB18D35D60A78C086CCE0F08F0F4CC36F676A4604E529DD72C95C11AED2F48D6D37

For more information on the TI keys and how TI Flash Studio stores them take a
look at the "Keys" section at the end of this document.

As the default project template is buggy an messed up, replace it with the new
one from this repository. You can find the default template folder in the
program folder of TI Flash Studio.

When you've got everything set up, launch TI Flash Studio, click
"File -> New Project.." and select "TI-92 Plus - Flash Application" (select this
for both TI-92 Plus and TI Voyage 200 Flash Apps). After that click the "Build"
button in the toolbar. Once the build is finished you can click the 
"View Simulator" button and try out the new FlashApp in the simulator.

By default TI Flash Studio will produce debug builds. You can change this by
selecting "Project -> Build Configuration -> Release". The resulting binary
which you can finally send to your real calculator is the *.9xk file located in
the folder "sdk-92p" in your project folder.

If you get strange errors related to file names or see file names with some part
of the ending cut off, then you have to reduce the file name length. This can be
done by using the 8.3 file/directory names, which is the default when you open
the .fsp project file directly from the explorer. More info about 8.3 file names
here: https://en.wikipedia.org/wiki/8.3_filename

## Build tools (compiler, ...) without IDE (works on Windows 7 and newer)
The only part of TI Flash Studio that requires Windows XP is the IDE itself.
However all the underlying build tools (compiler, assembler, linker, ...) don't
have this dependency, which means they can be used on newer Windows versions
like 7 or 10, and probably even on Linux (with Wine).

To be able to use these build tools you need extract them from the installer.
The TI Flash Studio installer is a WISE installer, so we can use the tool
[E_WISE](https://kannegieser.net/veit/programm/index_e.htm) to unpack it.

Once you've extracted the build tools there's only one problem left: the
resource compiler (rc32.exe) returns with the exit code -65536, even if the
compilation was successful. If you don't care about the exit code then this
isn't a problem, but most build systems (make, ...) will abort the build if a
command returns a non-zero exit code. Luckily this can be prevented by patching
a single byte in rc32.exe. Replace the byte `hex 66` at offset `hex 11C1` with
the byte `hex 90`. `hex 66` is an x86 instruction prefix which switches a
command from 32 bit to 16 bit. The command in question is `XOR EAX EAX` which
should set the return value in the EAX register to zero, but because of the
instruction prefix only the lower 16 bits of the EAX register are cleared, while
the upper 16 bits stay at `hex FFFF`. So the solution for this problem is to
just replace the instruction prefix with a nop instruction (`hex 90`).

The following list contains the steps needed to set up the build tools:
1. extract the archive e_wise.arj (for example with 7zip)
2. run `E_WISE_W.EXE FlashStudio1.1.43.exe FlashStudio` to extract all the files
   from FlashStudio1.1.43.exe
3. run `00000000.BAT` in the generated folder, this gives the extracted files
   their correct names
4. copy the contents of the extracted SIERRALOC folder to "C:\sierra\"
   (destination can be any folder you like, in this example and in the AppVeyor
   script I use "C:\\sierra\\")
5. copy the extracted TI68kTool.dll (from the MAINDIR folder) to
   "C:\\sierra\\bin\\"
6. replace the byte `hex 66` at offset `hex 11C1` in the file
   "C:\\sierra\\bin\\rc32.exe" with `hex 90`
7. create the folder "C:\\sierra\\keys\\"
8. create the file "C:\\sierra\\keys\\sdk-92p.key" with this content (more
   information on this is in the section "Keys" at the end of the document):
   ```
   0101
   406104CDFAD955D41F1ECCB9B622007FE8BC75E8B28DA178334755FEF27C564D47B04FD82498C163B762991C68CF64E29236BC41A4C1BCB9793B6EE965407C74BC
   40E17C4AA4C942CC57282E9B911E7B39352A2D8D4EC15398366C971FF7D2D92FB18D35D60A78C086CCE0F08F0F4CC36F676A4604E529DD72C95C11AED2F48D6D37
   ```

After you've finished the previous steps you can start compiling your FlashApps
with the following steps (with the specific CMD commands you can build the
temperature converter example project in this repository):
1. `cd` into the project directory (`cd temperature_converter_example`)
2. run the preprocessor on the resource file 
   (`C:\sierra\bin\com68.exe -E -Q -I.\ -I C:\sierra\include interface.r interface.i`)
3. run the resource compiler (`C:\sierra\bin\rc32.exe -mn interface.r`)
4. run the C compiler
   (`C:\sierra\bin\com68.exe -D_92 -q -Q -l -Oc1f0l3m1p1r2x1 -Xbef3IL -I C:\sierra\include temperature_converter.c temperature_converter.s_`)
5. run the F line call optimizer (`C:\sierra\bin\fline.exe temperature_converter.s_ temperature_converter.s`)
6. run the assembler..
   1. ...on the F line optimized compiler output
      (`C:\sierra\bin\asm68.exe -Q temperature_converter.s -o temperature_converter.o`)
   2. ...on the resource compiler output
      (`C:\sierra\bin\asm68.exe -Q interface.s -o interface.o`)
7. run the linker to link all object files
   (`C:\sierra\bin\link68.exe -Q -r -L"C:\sierra\lib" -o temperature_converter.out temperature_converter.o interface.o -lams SECTIONS{GROUP:{.text:{}.const:{}.data:{}.bss:{}}}`)
8. run sdkpc.exe to sign and generate the final *.9xk file, the last parameter
   is the internal application name which may not be longer than 8 characters
   (`C:\sierra\bin\sdkpc.exe -O3 -s C:\sierra\keys\sdk-92p.key 92 temperature_converter.out TempConv`)

After the build completed successfully you will get the *.9xk file which you can
send to your calculator.

If you've tried this with Wine on Linux, please let me know if it worked, so I
can add this information to this file. It should probably work, but I haven't
tried it so far.

## AppVeyor cloud build
As the extracted and patched build tools now work on modern operating systems,
you can set up continous integration / cloud build. To do that I basically
turned the previous section into a small script which can setup the compiler and
build the project on the AppVeyor cloud infrastucture.

The AppVeyor CMD script isn't really pretty but... mmh... but... at least it
works. The code which patches the binary is especially ugly because Windows
doesn't have a built in patch command. Patching is currently done by splicing
rc32.exe with 7zip into several parts, replacing one part and stitching them
back together afterwards.

So if you want to build FlashApps with minmal effort, just fork this GitHub
repository, setup AppVeyor with your GitHub account and the example project (a
temperature unit converter) will be built on the AppVeyor servers. The compiled
binary (the *.9xk file) will be exported as an AppVeyor artifact, which you can
download on the AppVeyor web interface. Once everything works you can modify the
source code and create your own FlashApp.

As you can see here, you can also add a nice badge to your repository, which
indicates the build status of your project:

[![Build status](https://ci.appveyor.com/api/projects/status/0a2j9tfnx6l5ilf8/branch/master?svg=true)](https://ci.appveyor.com/project/deisele/flashapp-build-guide/branch/master)

## SDK Documentation
The documentation for the 68k calculator SDK is split up into two files:
* sdk8992pguide.pdf (developer guide for TIOS)
* sdk8992pcompiler.pdf (compiler manual)

The documentation is relativly good overall and contains almost everything a
developer needs to know about TIOS, but I also noticed a few small flaws. For
example some of the code samples are a bit sloppy (bad PRNG code, ...), so don't
just blindly copy something.

## Tips for developing FlashApps
* look at other open source FlashApps to see how they're done, for example:
  * Command Post Plus
  * Blocks on the Rocks
* use Command Post Plus to test your FlashApp for memory leaks or to see how
  your FlashApp behaves in low memory situations etc.
* always test on a simulator (for example TiEmu), otherwise you could crash your
  calculator and lose all your files or if you have a memory leak, you would
  only be able to get your leaked memory back by resetting your calculator
* references to local variables cost much less memory than references to global
  variables, so if you often have to access global variables it's more memory
  efficient to access them via a local pointer

## Keys
To be able to later use your FlashApps on a real calculator, they must be signed
with a cryptographic key from TI. As all TI keys are cracked, you can sign the
FlashApp yourself. You can get the keys here:
https://brandonw.net/calculators/keys/

The default key of TI Flash Studio is stored in the file sdk-92p.key which is
located in the program folder of TI Flash Studio.

The first line in the key file is the key id.

The second line is value n of the key (bytes in reverse order) with a 40 in
front of it.

The third line is value d of the key (bytes in reverse order) with a 40 in
front of it.

For the TI-92 Plus Flash application signing key the file looks like this:

    0101
    406104CDFAD955D41F1ECCB9B622007FE8BC75E8B28DA178334755FEF27C564D47B04FD82498C163B762991C68CF64E29236BC41A4C1BCB9793B6EE965407C74BC
    40E17C4AA4C942CC57282E9B911E7B39352A2D8D4EC15398366C971FF7D2D92FB18D35D60A78C086CCE0F08F0F4CC36F676A4604E529DD72C95C11AED2F48D6D37
