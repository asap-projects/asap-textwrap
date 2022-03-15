# Changelog

All notable changes to this project will be documented in this file. See [standard-version](https://github.com/conventional-changelog/standard-version) for commit guidelines.

## [1.0.3](http://github.com/abdes/asap/compare/v1.0.2...v1.0.3) (2022-03-15)

### Features

- initial commit ([eb814d3](http://github.com/abdes/asap/commit/eb814d363952ea3ef6e78f2a99fb6005d70858c8))

### Bug Fixes

- include <cstring> for strlen ([7f99c0f](http://github.com/abdes/asap/commit/7f99c0fe9079f5ce29429c1cc3c5d7c4f30cd699))
- only add sanitizers if building tests ([193a437](http://github.com/abdes/asap/commit/193a437c9a86a90fb2746bab47d2c03fe49a22be))
- some parts of the module were not installed ([5f45bcb](http://github.com/abdes/asap/commit/5f45bcb6a550deff0a1bea9beb20f3abd81cbe97))
- update required dependencies ([4b3f9d9](http://github.com/abdes/asap/commit/4b3f9d9a17c5649fa477cacbd69324420c62b447))

## [1.0.2](http://github.com/abdes/asap/compare/v1.0.1...v1.0.2) (2022-03-06)

### Bug Fixes

- define asap_top_level_install as empty when project install should be skipped ([6cee399](http://github.com/abdes/asap/commit/6cee3997462b47b9c3fc382e2c65fd05ceddcff2))
- update required dependencies in pkg-config file ([127eea5](http://github.com/abdes/asap/commit/127eea5d8d87ba66d90861ed6a0ac9eb7668b428))

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
