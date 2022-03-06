# Changelog

All notable changes to this project will be documented in this file. See [standard-version](https://github.com/conventional-changelog/standard-version) for commit guidelines.

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
