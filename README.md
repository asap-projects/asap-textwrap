# C++ text wrapper and column formatter

<div align="center">

-+- Build Status -+-

[![Build status - master][build-status-master-badge]][build-matrix]

-+-

[![Latest release][release-badge]][latest-release]
[![Commits][last-commit-badge]][commits]
[![Linux][linux-badge]][latest-release]
[![Windows][windows-badge]][latest-release]
[![Mac OS][macos-badge]][latest-release]
[![License][license-badge]][license]
[![CII Best Practices][openssf-badge]][openssf-project]

</div>

<p align="center">
  <a href="#project-documentation">Project Documentation</a> •
  <a href="#getting-started">Getting Started</a> •
  <a href="#Contributing">Contributing</a> •
  <a href="#credits">Credits</a> •
</p>

This C++ library simplifies the task of formatting text in fixed width columns
and indenting it properly. Often, applications that needs to pretty print text
or display data in tabular format end up doing the alignment, indentation and
wrapping of each line manually by hardcoding spaces, tabs and line breaks or by
just assuming that display width is unlimited (which is not true).

With this library, wrapping long lines of text while maintaining indentation
requirements and proper line breaks management is straightforward.

Here is a simple example: the following text unwrapped would be presented as a
single very long line:

> There were doors all round the hall, but they were all locked; and when Alice
> had been all the way down one side and up the other, trying every door, she
> walked sadly down the middle, wondering how she was ever to get out again.

But when wrapped at `50` characters per line, it will display nicely within the
limited available width:

```text
There were doors all round the hall, but they were all
locked; and when Alice had been all the way down one
side and up the other, trying every door, she walked
sadly down the middle, wondering how she was ever to
get out again.
```

And the code to get that done is as simple as:

```c++
  const auto *passage = "There were doors all round the hall, but they ...";
  const TextWrapper wrapper =
      asap::wrap::MakeWrapper().Width(50).TrimLines();

  std::cout << wrapper.Fill(passage).value_or("error") << std::endl;
```

The capabilities of the library go much further with the following additional
features:

- **Indentation** using any prefix string, which can be different for the first
  line of each paragraph.
- **Tab expansion**, where each `tab` character is expanded to a replacement
  string (can be spaces or anything else).
- **Space replacement**, where each spacing character (including `<SPACE>`,
  `\t`, `\f`, `\r`) is replaced by a single space (' ').
- **Space collapsing**, where multiple consecutive spacing characters are
  replaced with a single space (' ').
- **Line trimming**, where spaces at the start or end of a line are eliminated.
- **Breaking on hyphens**, where compound words will be broken into separate
  chunks right after hyphens, as it is customary in English.

## Project Documentation

We have detailed guides for setting up an efficient development environment, the
development process, project structure, etc. Take a look at the available guides
[here](https://abdes.github.io/asap/asap_master/html/).

In addition to that, specific documentation for the command line parser, its
usage and APIs, are provided in the project GitHub Pages site
[here](https://asap-projects.github.io/asap-textwrap/asap_textwrap_master/html/).

## Getting Started

It is strongly recommended that you take some time to browse the project
documentation to familiarize yourself with its structure and development
workflows.

Make sure you have a C++ compiler with C++-17 capabilities at least. Gnu, Clang
and MSVC all can do that with a recent version.

```bash
git clone --recurse-submodules -j4 https://github.com/asap-projects/asap-textwrap.git
```

```bash
mkdir _build && cd _build && cmake .. && cmake --build .
```

or just use one of the predefined `CMake` presets. Detailed instructions are in
the project documentation, and many useful commands are listed
[here](https://abdes.github.io/asap/asap_master/html/getting-started/useful-commands.html).

## CMake configurable build options

```cmake
# Project options
option(BUILD_SHARED_LIBS        "Build shared instead of static libraries."              ON)
option(ASAP_BUILD_TESTS         "Build tests."                                           OFF)
option(ASAP_BUILD_EXAMPLES      "Build examples."                                        OFF)
option(ASAP_WITH_GOOGLE_ASAN    "Instrument code with address sanitizer"                 OFF)
option(ASAP_WITH_GOOGLE_UBSAN   "Instrument code with undefined behavior sanitizer"      OFF)
option(ASAP_WITH_GOOGLE_TSAN    "Instrument code with thread sanitizer"                  OFF)
option(ASAP_WITH_VALGRIND       "Builds targets with valgrind profilers added"           OFF)
```

## Contributing

If you would like to contribute code you can do so through GitHub by forking the
repository and sending a pull request. When submitting code, please make every
effort to follow existing conventions and style in order to keep the code as
readable as possible.

By contributing your code, you agree to license your contribution under the
terms of the BSD-3-Clause or a more permissive license. All files are released
with the BSD-3-Clause license.

Read the [developer guides](https://abdes.github.io/asap/asap_master/html/).

### Submitting a PR

- For every PR there should be an accompanying issue which the PR solves
- The PR itself should only contain code which is the solution for the given
  issue
- If you are a first time contributor check if there is a suitable issue for you

## Getting updates from upstream [`asap`](https://github.com/abdes/asap)

In order to pull and merge updates from the upstream project, make sure to add
it to the repo's remotes and disable pulling/merging tags from the upstream. We
want tags to be limited to those made in this repo, not in the upstream.

```bash
git remote add upstream https://github.com/abdes/asap.git
git config remote.upstream.tagopt --no-tags
```

## Credits

- The multitude of other open-source projects used to implement this project or
  to get inspiration - credits in the source code or the documentation as
  appropriate

[build-matrix]: https://github.com/asap-projects/asap-textwrap/actions/workflows/cmake-build.yml?branch=master
[build-status-master-badge]: https://github.com/asap-projects/asap-textwrap/actions/workflows/cmake-build.yml/badge.svg?branch=master
[cleanup-thumb]: https://asciinema.org/a/JOXq0l9CLZMolNcGhOnc84tNO.svg
[cleanup-video]: https://asciinema.org/a/JOXq0l9CLZMolNcGhOnc84tNO?autoplay=1
[commits]: https://github.com/asap-projects/asap-textwrap/commits
[customize-thumb]: https://cdn.loom.com/sessions/thumbnails/bedff4e1532441a6af6497653e52cede-with-play.gif
[customize-video]: https://www.loom.com/embed/bedff4e1532441a6af6497653e52cede
[from-template-thumb]: https://cdn.loom.com/sessions/thumbnails/087f217b73454728900baa8b1487f358-with-play.gif
[from-template-video]: https://www.loom.com/embed/087f217b73454728900baa8b1487f358
[hello-world-thumb]: https://cdn.loom.com/sessions/thumbnails/ff20f1771a6d448c8fd7b6e53e117c93-with-play.gif
[hello-world-video]: https://www.loom.com/embed/ff20f1771a6d448c8fd7b6e53e117c93
[last-commit-badge]: https://img.shields.io/github/last-commit/asap-projects/asap-textwrap
[latest-release]: https://github.com/asap-projects/asap-textwrap/releases/latest
[license-badge]: https://img.shields.io/github/license/asap-projects/asap-textwrap
[license]: https://opensource.org/licenses/BSD-3-Clause
[linux-badge]: https://img.shields.io/badge/OS-linux-blue
[macos-badge]: https://img.shields.io/badge/OS-macOS-blue
[openssf-badge]: https://bestpractices.coreinfrastructure.org/projects/5923/badge
[openssf-project]: https://bestpractices.coreinfrastructure.org/projects/5923
[project-docs-thumb]: https://cdn.loom.com/sessions/thumbnails/131bd53f1a004387b09bbeeb80a41f3e-with-play.gif
[project-docs-video]: https://www.loom.com/embed/131bd53f1a004387b09bbeeb80a41f3e
[project-docs]: https://abdes.github.io/asap/asap_master/html/index.html
[release-badge]: https://img.shields.io/github/v/release/asap-projects/asap-textwrap
[windows-badge]: https://img.shields.io/badge/OS-windows-blue
