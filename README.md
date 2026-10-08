# Advent of Code 2025

C solutions for days 1-3 and an unfinished day 4. Programs read their example and input files relative to the repository root.

## Reproduce verification

Install [mise](https://mise.jdx.dev/), Python 3 and GNU Make. From this directory:

```sh
mise trust
mise install
mise run verify-completed
mise exec -- make run-day01
```

`mise.toml` pins [Clang 23.1.3](https://github.com/llvm/llvm-project/releases/tag/llvmorg-23.1.3) and sets `CC=clang`. The Makefile uses C23, retaining the existing statement-expression extensions supported by Clang and GCC. There are no external source dependencies.

`mise run verify-completed` rebuilds days 1-3, runs their examples and inputs, compares complete transcripts, and explicitly reports the excluded unfinished day. `mise run verify` attempts every source and returns nonzero because day 4 cannot compile. `mise exec -- make all` likewise attempts all four days and fails on day 4. No placeholder answers or snapshots exist for it. Fixture hashes detect missing or changed inputs.

## Baseline and changes

The source baseline is commit `9a704130ff5a9944cc5b12c4714826bb2322b6d0`. It selected unpinned GCC with GNU99. BBoomer's GCC 16.2.1 built and ran days 1-3. The original `make all` failed before compiling anything because `all` depended on `01`, `02`, `03` and `04` instead of the `dayNN` targets. Compiling day 4 directly failed at its unfinished `s32` declaration.

The Makefile now selects the pinned Clang through mise, honors explicit compiler overrides, uses C23, fixes the aggregate target names, and tracks shared headers. Completed days give exactly the same examples and real-input outputs as the baseline. No original unit tests existed; the recorded output checks are regression tests rather than independent proofs.

Day 4 still has its original unfinished algorithm and mistakenly names day 3's input files. Completing a missing puzzle solution was outside this toolchain migration, so both issues remain visible rather than inventing an answer.
