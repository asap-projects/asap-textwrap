# Changelog

All notable changes to this project will be documented in this file. See [standard-version](https://github.com/conventional-changelog/standard-version) for commit guidelines.

## [1.1.0](http://github.com/abdes/asap/compare/v1.0.6...v1.1.0) (2023-04-15)

### ⚠ BREAKING CHANGES

* replacing spaces is no longer a feature of the text wrapper. The reason is
  that it can be achieved with the other features in a very simple way:
  * tab expansion can be used to replace tabs
  * '\r' and '\f' are completely ignored by default and do not contribute to the
    produced tokens
  * '\n' and '\v' are line breaks and should not be replaced as they are
    critical to the proper text wrapping

### Features

* add several usage examples of the wrapper ([7438ca1](http://github.com/abdes/asap/commit/7438ca147e2d64d39d42aa555b15764af35b0d4c))
* add the `version-info` tool to print the project info ([cb228e8](http://github.com/abdes/asap/commit/cb228e8af73fbf063371e4c597f757bf5e9a4b75))
* enhance configure logs with project/module nesting hierarchy ([f6c13f2](http://github.com/abdes/asap/commit/f6c13f2a08c89cac57fb2f0dd857c8f382e50e7b))
* implement robust project-wide formatting ([afcaebe](http://github.com/abdes/asap/commit/afcaebe544fc03684ae2f85d8507b1f4571d989b))
* increase ccache hit rate ([a22a912](http://github.com/abdes/asap/commit/a22a91226060851fe9fc7e5bc0e51973df94d95c))
* more robust handling of contract checking mode ([304e9ae](http://github.com/abdes/asap/commit/304e9aee1e8fb265be78163578c45ae22569e52b))
* option to control the use of ccache, default is OFF ([49a17a9](http://github.com/abdes/asap/commit/49a17a99026ae7e59d14297d01ed2f8d10c78762))
* upgrade CPM to 0.38.1 ([b333b38](http://github.com/abdes/asap/commit/b333b3858c204fa2151171f0ac494853089ffa37))

### Bug Fixes

* '\r' and '\f' should be totally ignored ([90c833e](http://github.com/abdes/asap/commit/90c833eb86b5ca806f4458be321f4c0ed5a78986))
* [#13](http://github.com/abdes/asap/issues/13) move "caexcludepath" to dev-windows and exclude CPM cache ([0571714](http://github.com/abdes/asap/commit/0571714e9436bfec26d6450b5bc37f2a5f478a55))
* [#14](http://github.com/abdes/asap/issues/14) upgrade CPM to 0.35.6 ([695414b](http://github.com/abdes/asap/commit/695414b8e66d4d42d7ef3aaef3c6a4b8399d16c2))
* [#16](http://github.com/abdes/asap/issues/16) use CMAKE_CURRENT_SOURCE_DIR instead of CMAKE_SOURCE_DIR for cmake includes ([4ac6928](http://github.com/abdes/asap/commit/4ac6928fc2a0bf806bbcaa3bea898b5ff018a164))
* [#17](http://github.com/abdes/asap/issues/17) git should not be required ([2c76104](http://github.com/abdes/asap/commit/2c761046d0801f643aa0215d34f2795ff0093dfc))
* [#18](http://github.com/abdes/asap/issues/18) enforce end of line to LF ([943ae47](http://github.com/abdes/asap/commit/943ae479e09de999c324a9cfe3bbf8d688d255a3))
* [#19](http://github.com/abdes/asap/issues/19) use generator expressions instead of CMAKE_BUILD_TYPE ([857d299](http://github.com/abdes/asap/commit/857d2997d4ec6c879036e10234b8baf907e91089))
* [#20](http://github.com/abdes/asap/issues/20) local install should use CMAKE_INSTALL_PREFIX to set variables ([2e1f1d4](http://github.com/abdes/asap/commit/2e1f1d49baff64dbf47dbbda234886ad2dfdbf1c))
* [#20](http://github.com/abdes/asap/issues/20) use CMAKE_INSTALL_PREFIX to set variables ([2fffd96](http://github.com/abdes/asap/commit/2fffd96392114993bbb72e3f614725f867d61ab1))
* always add code coverage 'all' targets ([d7309a0](http://github.com/abdes/asap/commit/d7309a0806e11a46c73b700f12bccb424c62839b))
* **build:** [#21](http://github.com/abdes/asap/issues/21) target option `WARNING` not propagated properly ([432cdaf](http://github.com/abdes/asap/commit/432cdaff1e5c8775d0d5c533dd0abe5eac229bd7))
* contract mode definition should only be added when not testing asap_contract ([c6d5e34](http://github.com/abdes/asap/commit/c6d5e342e7a74236bb1b006be1e0d6bfe956a51a))
* enable profiling for test coverage for MSVC ([7348d0a](http://github.com/abdes/asap/commit/7348d0a36b05b2f2e9c517e5b981f2c218bd511e)), closes [#22](http://github.com/abdes/asap/issues/22)
* generated `version.h` should follow project naming ([329bcdf](http://github.com/abdes/asap/commit/329bcdfc8cb9ba4782d0cbf4b3f21ad677307644))
* install master project generated header files ([3c5c162](http://github.com/abdes/asap/commit/3c5c1628b3c920e52200f7e14ecde2346b78a6f4))
* pkgconfig file uses wrong paths ([b4ca0ce](http://github.com/abdes/asap/commit/b4ca0ceb11cc379c11bf15135ba558d8555cc772))
* properly handle edge case of text terminated with new line and a space ([132b253](http://github.com/abdes/asap/commit/132b25379ce8f51f9aea0383ebeb4b8b8793e246))
* properly handle new lines and white spaces ([c6cf3d0](http://github.com/abdes/asap/commit/c6cf3d009ea4fc5c6fe5cbaa2501c67f8ea6b042))
* restore test setup deleted by mistake ([cec7b9d](http://github.com/abdes/asap/commit/cec7b9d92481d1480c54610892cbfd954b9e0068))
* several bugs related to white space trimming ([a162fec](http://github.com/abdes/asap/commit/a162fec0241be5fbd09d573fcbb2e43c141340ae))
* sub-projects with tests fail due to coverage all target not being setup early enough ([400b2cc](http://github.com/abdes/asap/commit/400b2ccc120bd4f2c4d70f48fd3f94ce7a3f6de0))
* top level install not working properly ([4ac4a31](http://github.com/abdes/asap/commit/4ac4a31001a2ab73764e3d9fe3f279b1e7b25aee))
* use cmake-format extension default behavior ([a5d5c5e](http://github.com/abdes/asap/commit/a5d5c5eae39e4d3d0094c00848cfe777d331a219))
* use correct path for the version include file ([7997b68](http://github.com/abdes/asap/commit/7997b68eeef236e6940b0ba168c79dbdd21b34ad))
* version-info test was added even when ASAP_BUILD_TESTS is OFF ([b566e7b](http://github.com/abdes/asap/commit/b566e7b555ffb40f8ab1eea43d9a965c5724ccf1))
* wrong variable used for target name ([4ecd2bb](http://github.com/abdes/asap/commit/4ecd2bbfa896547e77cdbf7ba1c535f80125eef4))
* wrong variable used of target name ([04b5343](http://github.com/abdes/asap/commit/04b5343ae541bd6d4f5ae1c1fa2eb85b93e0b5a3))

* remove workspace replacement ([3a67087](http://github.com/abdes/asap/commit/3a670877435ef0c2cf9e68f03d2c2d608a2306a9))

### Documentation

* add documentation for usage scenarios ([a9dcb30](http://github.com/abdes/asap/commit/a9dcb30569218609f854c4d181456bf98ab8ec7e))
* add example output from version-info tool ([3a5515e](http://github.com/abdes/asap/commit/3a5515e74b0b0e5c06ba7e4500f7572a3bc4450f))
* configure project folders for esbonio extension ([3adbff4](http://github.com/abdes/asap/commit/3adbff481b90e7c8398752e6c3489ed5b12f91c9))
* document the use of `ccache` for compiler caching ([fe07e72](http://github.com/abdes/asap/commit/fe07e72ecd4eccd562bae06d31cf87723374bf46))
* improve class documentation ([e1c2d3d](http://github.com/abdes/asap/commit/e1c2d3d0f5666193f4ecaae9d50ad72d10926924))
* refactor the documentation and enhance it ([51772fb](http://github.com/abdes/asap/commit/51772fbef0a8a4de41be99c38e95cfc6d4a430de))
* update after new formatting system ([082e513](http://github.com/abdes/asap/commit/082e5134fd7d1cd03cc06218e10d5cf978b22409))
* update sphinx theme option to new name ([a78e49a](http://github.com/abdes/asap/commit/a78e49a78c868473a724d0357eeaee37a5a75201))
* update url for executable books logo ([8b4dd17](http://github.com/abdes/asap/commit/8b4dd1739bfbfe057437bd3e96b5b29adf98fd1a))

## [1.0.5](http://github.com/abdes/asap/compare/v1.0.4...v1.0.5) (2022-08-11)

Merge features/updates/fixes from upstream [asap](http://github.com/abdes/asap).

## [1.0.4](http://github.com/abdes/asap/compare/v1.0.3...v1.0.4) (2022-03-15)

* refactor build to use CPM for cmake dependencies and speedup build with ccache.

## [1.0.3](http://github.com/abdes/asap/compare/v1.0.2...v1.0.3) (2022-03-15)

### Features

* initial commit ([eb814d3](http://github.com/abdes/asap/commit/eb814d363952ea3ef6e78f2a99fb6005d70858c8))

### Bug Fixes

* include <cstring> for strlen ([7f99c0f](http://github.com/abdes/asap/commit/7f99c0fe9079f5ce29429c1cc3c5d7c4f30cd699))
* only add sanitizers if building tests ([193a437](http://github.com/abdes/asap/commit/193a437c9a86a90fb2746bab47d2c03fe49a22be))
* some parts of the module were not installed ([5f45bcb](http://github.com/abdes/asap/commit/5f45bcb6a550deff0a1bea9beb20f3abd81cbe97))
* update required dependencies ([4b3f9d9](http://github.com/abdes/asap/commit/4b3f9d9a17c5649fa477cacbd69324420c62b447))

## [1.0.2](http://github.com/abdes/asap/compare/v1.0.1...v1.0.2) (2022-03-06)

### Bug Fixes

* define asap_top_level_install as empty when project install should be skipped ([6cee399](http://github.com/abdes/asap/commit/6cee3997462b47b9c3fc382e2c65fd05ceddcff2))
* update required dependencies in pkg-config file ([127eea5](http://github.com/abdes/asap/commit/127eea5d8d87ba66d90861ed6a0ac9eb7668b428))

## [1.0.1](http://github.com/abdes/asap/compare/v1.0.0...v1.0.1) (2022-03-06)

chore: remove stale directory from old version

## 1.0.0 (2022-03-06)

This is a major refactoring of the `asap` family of projects and as such,
introduces several breaking changes from the old model of `asap` projects.

This is a C++ library to format text in columns with a maximum width. When a
line of text is longer than its column's maximum width, the text is
automatically wrapped. A number of other features are also supported, such as
adding an initial indent, indenting all lines, etc... Refer to the API
documentation for more details.
