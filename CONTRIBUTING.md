# Contributing to WebCC

First off, thanks for taking the time to contribute! 🎉

The following is a set of guidelines for contributing to WebCC. These are mostly guidelines, not rules. Use your best judgment, and feel free to propose changes to this document in a pull request.

## Code of Conduct

This project and everyone participating in it is governed by the [WebCC Code of Conduct](CODE_OF_CONDUCT.md). By participating, you are expected to uphold this code.

## How Can I Contribute?

### Reporting Bugs

This section guides you through submitting a bug report for WebCC. Following these guidelines helps maintainers and the community understand your report, reproduce the behavior, and find related reports.

- **Use a clear and descriptive title** for the issue to identify the problem.
- **Describe the exact steps to reproduce the problem** in as many details as possible.
- **Provide specific examples** to demonstrate the steps.
- **Describe the behavior you observed** after following the steps and point out what exactly is the problem with that behavior.
- **Explain which behavior you expected to see instead** and why.

### Suggesting Enhancements

This section guides you through submitting an enhancement suggestion for WebCC, including completely new features and minor improvements to existing functionality.

- **Use a clear and descriptive title** for the issue to identify the suggestion.
- **Provide a step-by-step description of the suggested enhancement** in as many details as possible.
- **Explain why this enhancement would be useful** to most WebCC users.

### Pull Requests

- Fill in the required template
- Do not include issue numbers in the PR title
- Include screenshots and animated GIFs in your pull request whenever possible.
- Follow the C++ style of the existing codebase.
- Make sure your code builds and works by running `./test_examples.sh`.

## Style Guide

- We use C++20.
- Indentation is 4 spaces.
- Keep headers minimal.
- Prefer `webcc::handle` for resource management.

## Development Setup

1.  Clone the repo.
2.  Run `./build.sh` to bootstrap the compiler.
3.  Make your changes.
4.  Run `./build.sh` again to rebuild with your changes.
5.  Test with `./test_examples.sh`.
