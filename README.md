# -EZinjector-Reborn-0r1g1nal-
The original version of ezinjector reborn with minor improvements in the system and the addition of new unused functions written in C++.
## Getting started
### Prerequisites
Microsoft Visual Studio 2019 (preferably latest version i.e. 16.2.5), platform toolset v142 and Windows SDK 10.0 are required in order to compile EZinjector Reborn. If you don't have ones, you can download VS (Windows SDK is installed during Visual Studio Setup).
### Compiling from source
When you have equiped a copy of source code, next step is opening EZinjector Reborn.sln in Microsoft Visual Studio 2019.

Then change build configuration to Release | x86 and simply press Build solution.

If everything went right you should receive EZinjector Reborn.exe file.
## How it works
The injector receives information about the CS: GO game window and searches for it until it is found.

Then he starts looking for the game client, and after the client he looks for the engine.

After all the operations, you can enter the name of the dll file that we want to inject into the game.
## See also
