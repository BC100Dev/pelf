# PELF - Packaged ELF Exec Format
PELF is the answer to the hell of how we always had to run native Linux apps. Windows OS made
a good job with packaging resources and managing libraries, since that OS gives the ability
to just run and expect it to work. Linux, on the other hand, makes things a bit more difficult.
Missing symbol? Glibc too new and refuses to work? Outdated libraries? Those are the pain-points
of running apps on Linux. Sure, we already have Flatpak, Snap and AppImages doing our job for
this case already, but they always have something. Flatpak and Snap contains a package manager.
AppImages are just disk images within a Linux executable. What about that we just want an
executable format that just works out of the box?

That's where I decided to come in. Forget those hacks and dependency chaos. PELF allows you to
package resources, libraries and executable(s) into one giant PELF binary. Yes, AppImage allows
you to do that, but like I said, those files deliver content that eventually gets mounted.
I decided to avoid that point with PELF, where mounting becomes obsolete (not necessarily by the
App Runtime itself), but the executable manages to just run flawlessly.

## Why PELF?
I already said most of the things, but let me reiterate. We, as Linux users, already suffered
enough with:
- "Works on my machine" syndrome
- Distros with broken or missing libraries (especially with outdated ones)
- Half-assed packaging tools that need root or spam your system
- Flatpak, Snap and AppImage making things simpler, but bringing more cons to its place

With PELF, I decided to cut all that, and integrate these following ones:
- **One file** runs all
- **No installation** ever needed, unless configured or coded by the developer
- **No system packages**, where nothing gets left behind
- **No mounting needed** by FUSE or whatever

## PELF content
For this format, I decided to include these following things that could be included, although
this may take into change, as development goes on (I just started development on it btw):
- **Native ELF**: The standard x86_64/ARM64 ELF at the start, launches anywhere
- **Resource section**: Embedded location for all the necessary assets, icons, configurations
  and translations, accessed at runtime via `libPELF` (see its section for information),
  located at `::resources/`
- **Library section**: All necessary `.so` files are packaged in its own section, packed and
  referenced using `RPATH` / `RUNPATH` abilities that the Library Loader understands, located
  at `::libs/`
- **Manifest**: Human and machine-readable manifests, packaged right with `::app_manifest`

---

## libPELF
With the use of `libPELF`, you can interact with your own PELF binary itself, when you 
decide to package the resources along the way. Instead of cluttering everything, with the
library, instead of trying to figure out the section, you can use the library to fetch the
necessary resource right at Runtime itself.

...

Yeah, I don't have many ideas, except that you can load in assets at runtime.

---

## WIP
Please note that as of 28-09-2025, I have created this repository, and all of this may go
with the structure being constantly changed, even without updating the README itself (I'm
lazy, I know). Do not expect any releases anytime soon, as C++ development tends to be slow,
but when you start using it, the performance will go brrr.