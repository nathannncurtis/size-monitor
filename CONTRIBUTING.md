# Contributing

Bug reports and pull requests are welcome.

## Getting started

1. Fork the repo and clone it locally.
2. Build prerequisites: Visual Studio 2022 (Desktop C++ workload), CMake 3.25+, .NET 9 SDK.
3. Run `build.bat` to verify your environment before making changes.

## Pull requests

- Keep changes focused. One feature or fix per PR.
- The C++ engine targets `/W4 /WX` (zero warnings). The C# projects have nullable and implicit usings enabled.
- Match the existing code style. No auto-formatters that reformat unrelated lines.
- No AI attribution in commits.

## Reporting bugs

Open an issue with the path or volume type that triggers the problem, whether you are running elevated, and the Windows version.
