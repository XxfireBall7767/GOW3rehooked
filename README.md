<h1 align="center">GOW3rehooked</h1>

<p align="center"><i>“Your pawn has failed you, Gaia. Perhaps you should have chosen the other one!”</i></p>

![Title menu with the added Continue, Rehooked, Help and Controls, and Quit Game entries](assets/screenshots/title-menu.png)

GOW3rehooked lets you play God of War III Remastered on Windows and Linux PCs. The same developer who created the original GOW3 build for shadPS4 made it with a lot of love, care and obsession for performance.

No game code or assets are included. You need your own copy of the game.

<p align="center">
  <br>
  <a href="https://github.com/cuesta4/GOW3rehooked/releases/latest">
    <img src="assets/download-button.svg" alt="Download latest release" width="286" height="58">
  </a>
  <br><br>
</p>

> [!IMPORTANT]
> GOW3rehooked is independent from shadPS4. Please don't take questions or bug reports about it to the shadPS4 developers. Use the [Issues](../../issues) page of this repository.

## Requirements

| Component | Requirement |
| --- | --- |
| Operating system | Windows 10 or 11, or Linux x86-64 |
| Intel CPU | 4th-generation Core (Haswell) or newer for the standard build. |
| AMD CPU | Ryzen 1000 or newer for the standard build. |
| AMD GPU | Radeon RX 5300 (RDNA 1) or newer. |
| NVIDIA GPU | GeForce GTX 950 or newer. |
| Intel GPU | Untested. |
| Memory | 16 GB of RAM recommended |
| Game | God of War III Remastered, European (CUSA01715) or American (CUSA01623) release, updated to version 1.02 |

The standard build requires an x86-64-v3 CPU (including AVX2, BMI1/2, FMA, F16C, LZCNT and MOVBE). Six cores or more are recommended.

The experimental AVX1 build may work on some CPUs older than 4th-generation Intel Core or AMD Ryzen 1000. The same GPU requirements apply. Feel free to [report any issues](#reporting-bugs).

Use a current graphics driver for your card. The renderer requires Vulkan 1.3 with shader objects, depth clip control, push descriptors, conditional rendering, sparse buffer residency and min/max sampler filtering. Radeon also needs `VK_KHR_maintenance5`. Windows capability reports are available for the [Radeon RX 5300](https://vulkan.gpuinfo.org/displayreport.php?id=53293), [Radeon RX 5500 XT](https://vulkan.gpuinfo.org/displayreport.php?id=45797) and [GeForce GTX 950](https://vulkan.gpuinfo.org/displayreport.php?id=47069).

The game has to be in a folder that contains `eboot.bin`, `sce_module` and `sce_sys`. A game that is still packaged in a single file has to be extracted first. Only version 1.02 works, because GOW3rehooked modifies the game at exact locations of that version's executable.

## Installation

Only use the AVX1 build if your CPU doesn't meet the requirements for the standard build.

### Windows

1. Download `GOW3rehooked-Windows-x86_64.zip` (standard) or `GOW3rehooked-Windows-x86_64-AVX1.zip` (AVX1) from the [Releases](../../releases/latest) page.
2. Extract the ZIP into the game folder, next to `eboot.bin`:

   ```text
   God of War III\
   ├── eboot.bin
   ├── sce_module\
   ├── sce_sys\
   ├── EXEC\ ...
   ├── gow3.exe
   ├── gow3_debug.exe
   ├── gow3.dll
   ├── licenses\
   └── _rehooked_\      the shader recipes; everything else is created on first launch
   ```

3. Run `gow3.exe`. The first few launches may show the [shader preparation screen](#shaders-prepared-in-advance).
4. Choose your settings under Rehooked in the title menu.

Windows releases check for updates at startup. Choose **Yes** to install the same CPU variant and reopen the game, or **No** to skip that release. To see the offer again, delete `_rehooked_/settings/skipped-release.txt`. Updates keep your existing `gow3.exe` and `gow3_debug.exe` and replace the runtime they start. The previous runtime is saved as `gow3.update.old`. Release ZIPs also contain a `gow3_update.exe`, which lets v0.1.5 and v0.1.6 install them; the game deletes it when it starts.

When installing another Windows build manually over one that already has `gow3.dll`, keep the two existing launchers and extract the new runtime and the other files.

### Linux

1. Download `GOW3rehooked-Linux-x86_64.zip` (standard) or `GOW3rehooked-Linux-x86_64-AVX1.zip` (AVX1) from the [Releases](../../releases/latest) page.
2. Extract the ZIP into the game folder, next to `eboot.bin`.
3. Run `./gow3.AppImage`.

On startup, release AppImages offer to install the latest version for your CPU variant. Choose **Yes** to update both AppImages and restart, or **No** to skip that release. The previous game AppImage is kept as `gow3.AppImage.old`. To see a skipped release again, delete `_rehooked_/settings/skipped-release.txt` from the game folder.

If your extractor dropped the executable bits, run `chmod +x gow3*.AppImage`. On systems without FUSE, run `APPIMAGE_EXTRACT_AND_RUN=1 ./gow3.AppImage`. For [diagnostics](#reporting-bugs), use `./gow3_debug.AppImage` with the same prefix if needed.

For a source build, use Clang and LLD, a C++23 standard library such as libstdc++ 14, CMake, Ninja, NASM, Vulkan headers 1.4.328 or newer, `glslc`, shaderc, glslang, SPIRV-Tools, and libunwind. The [workflow](.github/workflows/windows.yml) lists the Ubuntu 24.04 packages. Run `bash build-fast.sh --release`, then `build-fast/Linux/Release/bin/gow3 --game-dir /path/to/game`. Add `--ivy-bridge` to build for AVX1.

The game stores its settings, saves and diagnostics in `_rehooked_`:

| Path | Contents |
| --- | --- |
| `settings/config.cfg` | Your settings. Delete it to return to the defaults. |
| `saves/` | Your saves |
| `shader_cache/` | Translated shaders, and the shader recipes from the ZIP, which grow as you play |
| `gow3.log` | A log, which grows with every launch |
| `gow3-<date>-<time>.zip` | Diagnostics of one session run with the debug launcher, split into `.part1.zip`, `.part2.zip` and so on past 24 MB, see [Reporting bugs](#reporting-bugs) |

To update, extract the new ZIP over the old files and let it replace them. Your settings, saves and translated shaders are not in the ZIP and stay as they are. To uninstall, delete the two executables and `licenses`, and `_rehooked_` as well if you don't want to keep your saves.

## Performance

Performance is the main goal of the project. Both screenshots show the same scene on a Ryzen 5 5600 with an RTX 3060. At 4K the graphics card sets the frame rate. At 480p it no longer does, so the second number shows what the processor can deliver.

<table>
  <tr>
    <td width="50%"><img src="assets/screenshots/performance-4k.png" alt="4K gameplay running at 150 FPS"></td>
    <td width="50%"><img src="assets/screenshots/performance-480p.png" alt="480p gameplay running at 403 FPS"></td>
  </tr>
  <tr>
    <td align="center">4K: 150 FPS, 6.5 ms</td>
    <td align="center">480p: 403 FPS, 2.6 ms</td>
  </tr>
</table>

## Features

### Resolution and frame rate

The game can render at 480p, 720p, 1080p (the PS4 original), 1440p, 1800p or 4K. The higher, the heavier. The frame rate can be 30, 40, 60, 120, 240 or 480 FPS, with deltatime.

### Image quality

The game's default is 2x MSAA, trilinear texture filtering. You can go up to 4x MSAA or turn it off for better performance. CMAA2 can be used to soften the image. For textures, you can use 4x to 16x anisotropic filtering in place of the original trilinear.

When the game's resolution and your monitor's differ, the image needs to be resized. You can use bilinear scaling (faster) or FSR 1/Lanczos 2 (better).

### Shaders prepared in advance

A shader is a small program the graphics card runs to draw a surface or an effect. The game's shaders were written for the PS4's GPU, so each one has to be translated before your graphics card can run it. Emulators usually translate a shader the first time the game needs it, in the middle of gameplay, and that pause is the familiar shader stutter.

GOW3rehooked translates the game's shaders before gameplay instead, behind a progress screen at startup. This mode is called AOT (ahead of time) and is the default. The work is spread over up to four launches, so the first one isn't a long wait, and the results are saved for the next launches. The ZIP brings recipes for every shader variant met in a complete playthrough, and the first launch prepares all of them before the rest.

JIT (just in time) translates a shader when the game first needs it. With AOT it stays active as a safety net for any shader the preparation didn't catch, so nothing goes missing. It can also be used alone, with no preparation screen. Holding Esc, Circle (PlayStation controllers) or B (other gamepads) on the preparation screen skips it, and the game then restarts once with JIT alone.

Both modes are described under [Settings](#settings).

<p align="center"><img src="assets/screenshots/shader-preparation.png" alt="Shader preparation screen with a progress bar and a hold-to-skip prompt" width="80%"></p>

### Controls

You can play with a gamepad or with keyboard and mouse, and remap both from a screen inside the game. The added screens show PlayStation symbols for a DualShock 3, DualShock 4 or DualSense, and Xbox-style buttons for other gamepads.

### Menus and saves

Continue appears above New Game once you have a save and directly loads the latest. The game originally has 32 manual save slots. GOW3rehooked raises that to 64. The save and load screens let you duplicate or delete saves. Open Save Folder opens the selected save in your file manager.

Rehooked holds every setting in the game's own menu style, feel free to tinker. Help and Controls has an explanation of each setting and allows you to remap the controls.

The opening logos can be skipped, and so can any video or cutscene, by pressing Cross.

<table>
  <tr>
    <td width="50%"><img src="assets/screenshots/load-game.png" alt="Load Game screen with thumbnails, details of the selected save and the Open Save Folder prompt"></td>
    <td width="50%"><img src="assets/screenshots/save-game.png" alt="Save Game screen with Create a New Save selected"></td>
  </tr>
  <tr>
    <td align="center">Load Game</td>
    <td align="center">Save Game</td>
  </tr>
  <tr>
    <td width="50%"><img src="assets/screenshots/controls.png" alt="Controls screen with Xbox-style gamepad prompts and keyboard and mouse bindings"></td>
    <td width="50%"><img src="assets/screenshots/help.png" alt="Help screen explaining the Resolution setting"></td>
  </tr>
  <tr>
    <td align="center">Controls</td>
    <td align="center">Help</td>
  </tr>
</table>

### Surround audio

The game automatically detects stereo, 5.1 and 7.1 from the opened SDL playback device. No manual audio setting is required. Unknown or unsupported channel counts fall back to stereo, and stereo devices retain the existing downmix. The layout is detected when an audio port opens; restart the game after changing the host speaker configuration.

tested the Windows build on a 7.1 surround system and confirmed that each speaker receives a distinct audio channel as expected, including center-channel dialogue and separate front/rear positional audio. The standalone channel-selection test covers 2, 6 and 8 channels and unsupported/unknown counts; it does not test physical speaker routing. Run it from the repository root with `c++ -std=c++17 -Isrc tests/test_auto_surround.cpp -o test_auto_surround`, then run the resulting executable.

## Settings

Defaults are in bold.

### Display

| Option | Choices | What it does |
| --- | --- | --- |
| Resolution | 480p, 720p, **1080p**, 1440p, 1800p, 4K | The resolution the game renders at. 1080p is the original. Higher looks sharper and needs more GPU power and video memory. |
| Frame Rate | 30, 40, **60**, 120, 240, 480 FPS | The game keeps its normal speed at every rate. Higher rates need more CPU and GPU power. 40 FPS suits a 120 Hz or 240 Hz display, or VRR. |
| Display Mode | Windowed, **Borderless**, Exclusive | Windowed: a resizable window. Borderless: full screen at the desktop's resolution and refresh rate. Exclusive: full screen, switching the display to the game's resolution and frame rate, or the closest it supports. |
| VRR | **Off**, On | For G-SYNC and FreeSync displays. The display runs at its highest refresh rate and follows the game, so drops below the selected FPS stay smooth. Full screen only. |
| VSync | **FIFO**, Mailbox, Off | FIFO: no tearing, more input lag. Mailbox: no tearing, less lag, more GPU work. Off: least lag, may tear. |
| NVIDIA Reflex | **Off**, On | Lowers input lag when the GPU is the limit, at a small cost in FPS and frame pacing. Requires a compatible NVIDIA GPU and driver. |

### Graphics

| Option | Choices | What it does |
| --- | --- | --- |
| MSAA | Off, **2x**, 4x | Smooths jagged edges. 2x is the original. 4x is smoother and needs more GPU power and video memory. |
| Texture Filtering | **Trilinear**, 4x, 8x, 16x | Trilinear is the original. 4x to 16x anisotropic keeps textures sharp at steep angles, at a small GPU cost. |
| Post Effects | **Off**, CMAA2 | CMAA2 smooths jagged edges after the image is drawn, at a small GPU cost. |
| Scaler | **Bilinear**, FSR 1 / Lanczos 2 | How the image is resized to your display. Bilinear is the fastest. FSR 1 (enlarging) and Lanczos 2 (shrinking) keep more detail. |

### Other

| Option | Choices | What it does |
| --- | --- | --- |
| Skip Opening Logos | **Off**, On | Starts the game at the title menu. |
| Skip Videos with X | Off, **On** | Press Cross to skip any video or cutscene. |
| Shader Mechanism | JIT, **AOT** | AOT prepares the shaders before you play, so stutter is rare. JIT translates each shader when it first appears, which can stutter. |
| Shader Recompilation | Sync, **Async** | How shaders are translated during gameplay. Async: no stutter, but an object can appear a moment late. Sync: nothing appears late, but a hitch is possible. |
| Lazy AOT | Off, **On** | On: the first shader preparation is split over up to four launches. Off: it is done in one. |

<table>
  <tr>
    <td width="33%"><img src="assets/screenshots/settings-display.png" alt="Display settings page"></td>
    <td width="33%"><img src="assets/screenshots/settings-graphics.png" alt="Graphics settings page"></td>
    <td width="33%"><img src="assets/screenshots/settings-other.png" alt="Other settings page"></td>
  </tr>
  <tr>
    <td align="center">Display</td>
    <td align="center">Graphics</td>
    <td align="center">Other</td>
  </tr>
</table>

## Troubleshooting

- “EBOOT.BIN NOT FOUND” at startup means the launcher did not find the game folder. Put `gow3.exe` or `gow3.AppImage` next to `eboot.bin`.
- “YOUR GAME IS COMPRESSED” means the folder holds a packaged game. Extract it first.
- “YOUR GAME IS NOT VERSION 1.02” means the game needs its 1.02 update, or is not the European (CUSA01715) or American (CUSA01623) release.
- If the game crashed before reaching the title menu, the next launch offers to reset your settings. Answer Yes if the crashes began after you changed one.
- To reset the settings by hand, delete `_rehooked_/settings/config.cfg`.

## Reporting bugs

Report problems on the [Issues](../../issues) page, after checking that yours isn't already there. The bug report form requires `gow3.log`, and a report that also comes with the debug dump is much easier to act on.

1. Start the game with `gow3_debug.exe` on Windows or `gow3_debug.AppImage` on Linux. The game runs slower with diagnostics turned on.
2. Reproduce the problem. If it is visual, press F9 while it is on screen. The game pauses for a moment while it records that frame, and **SAVING DEBUG DUMP** shows in the bottom-left corner. Wait until it says **DEBUG DUMP SAVED** before you close the game, or the dump loses that frame's images.
3. Quit from the title menu, or close the window.
4. Open `_rehooked_` and find `gow3.log` and the newest `gow3-<date>-<time>.zip`, or all its `.part1.zip`, `.part2.zip`… files when the dump is larger than 24 MB (a crash may leave only `gow3.log`).
5. Open an issue with those files attached, and describe:
   - what happened and what you expected;
   - where in the game it happens (a save from `_rehooked_/saves` made just before the problem helps);
   - your settings;
   - your CPU, GPU, driver version and operating system version.

If you are asked for a more detailed capture, set `GOW3_DEBUG=2` before running the debug launcher. It is slower than the default debug mode.

```powershell
$env:GOW3_DEBUG = "2"; & "C:\your\game\path\gow3_debug.exe"
```

```sh
GOW3_DEBUG=2 ./gow3_debug.AppImage
```

## Credits

- The [shadPS4](https://github.com/shadps4-emu/shadPS4) team, for the PS4 kernel, system library and loader work the system layer is built on.
- kvicken, for the original resolution patches, extended here.
- Third-party components: [SDL3](https://github.com/libsdl-org/SDL), [Dear ImGui](https://github.com/ocornut/imgui), [FFmpeg](https://ffmpeg.org), [AMD FidelityFX Super Resolution 1](https://github.com/GPUOpen-Effects/FidelityFX-FSR), [Intel CMAA2](https://github.com/GameTechDev/CMAA2), [shaderc](https://github.com/google/shaderc) with [glslang](https://github.com/KhronosGroup/glslang) and [SPIRV-Tools](https://github.com/KhronosGroup/SPIRV-Tools), [Zydis](https://github.com/zyantific/zydis), [Xbyak](https://github.com/herumi/xbyak), [xxHash](https://github.com/Cyan4973/xxHash), [Zstandard](https://github.com/facebook/zstd), [fmt](https://github.com/fmtlib/fmt), [magic_enum](https://github.com/Neargye/magic_enum), [stb](https://github.com/nothings/stb), [LibAtrac9](https://github.com/Thealexbarney/LibAtrac9) and the [Cinzel](https://github.com/NDISCOVER/Cinzel) typeface.

## License

GOW3rehooked is licensed under the GNU General Public License v2.0 or later. Third-party components keep their own licenses, and their texts are in [`licenses/`](licenses). The release ZIP carries the same folder, with each component's copyright notice in `THIRD-PARTY-NOTICES.txt`.

God of War is a trademark of Sony Interactive Entertainment. This project is not affiliated with or endorsed by Sony Interactive Entertainment or Santa Monica Studio.

The software is provided as is, without warranty of any kind. There is no roadmap, and no commitment to fix bugs, add features or release updates.
