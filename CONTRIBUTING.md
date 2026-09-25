# Contributing to the Exercism RISC-V track

Thank you for helping to improve the track.
Every contribution, whether an exercise, a bug fix or a change to the docs, starts with a conversation on the [forum][forum].

## Start on the forum

- **Search the [forum][forum] first**, together with the repository's [issues][gh-issues] and [pull requests][gh-pulls], to check that nobody is already working on the same thing.
- If nobody is, [open a topic][forum-new-topic] describing what you would like to do and, for an exercise, how you intend to design it.
- **Wait for agreement from the maintainers before writing code.**
  Agreeing on the design up front avoids duplicated effort and pull requests that cannot be merged.
- When you open the pull request, link to the forum topic in its description.


## Set up your machine

- Install `zig`, `make` and `qemu-riscv32` as described in [docs/INSTALLATION.md][installation].
- Install the contributor tools, `git`, `jq`, `curl`, Python 3, `clang-format` and `pre-commit`, with the command for your distribution in [docs/CONTRIBUTOR_TOOLS.md][contributor-tools].
- Then, from the repository root:

```shell
bin/fetch-configlet
bin/configlet info
pre-commit install
pre-commit run --all-files
```

`bin/configlet info` fetches the problem specifications into configlet's cache, which the test generator reads, so it must run once, online, before generating tests.
The repository uses [pre-commit][pre-commit] to run the same checks locally that CI runs on every pull request: trailing whitespace and end-of-file fixes, YAML validity, `clang-format` on the C test files, `ruff` on the Python generators, `shellcheck` on the scripts in `bin/`, and a check that every exercise's `Makefile` and `vendor/` directory match the copies in `templates/`.
`pre-commit install` makes git run those checks before every commit, and `pre-commit run --all-files` runs them once over the whole repository, downloading the hook tools on first use.
When a hook rewrites a file, such as `clang-format` or the whitespace fixers, the commit is refused; review the change, `git add` it and commit again.

## Adding a practice exercise

The track's exercises come from the shared [problem specifications][problem-specifications], and their tests are generated from the canonical data there.

### 1. Agree the design on the forum

Choose an exercise from the problem specifications that the track does not have yet.
Propose the C prototype of each function the tests will call, for example `extern int leap_year(long year);`.
The prototype is the contract every student writes against, so it is the main thing to settle before any code is written.

### 2. Scaffold the exercise

Scaffold the exercise as described in the [Add a Practice Exercise docs][add-practice]:

```shell
bin/add-practice-exercise -a <your-github-username> -d <difficulty> <exercise-slug>
```

The difficulty runs from 1 (easiest) to 10 (hardest).
The script uses [configlet][configlet], Exercism's track tooling, to create the exercise's documentation, its `.meta/config.json`, its `.meta/tests.toml` and its entry in the track's `config.json`, then copies in the shared `Makefile` and `vendor/` directory and creates an empty generator module for you.
It ends by printing the remaining steps.

### 3. Write the test generator

Each exercise has a small Python module in `generators/exercises/<exercise_slug>.py` that turns the canonical data into a [Unity][unity] test file.
It defines two things:

- `FUNC_PROTO`, the header of the test file: the `#include "vendor/unity.h"` line, any `#define`s the tests need, and the prototypes agreed on the forum.
- `gen_func_body(prop, inp, expected)`, which returns the C statements for one test case.
  `prop` is the canonical property name in snake case, `inp` is the case's `input` object and `expected` is its `expected` value.

Look at `generators/exercises/leap.py` for the simplest possible module, `hamming.py` for a case with an error value, and `affine_cipher.py` for the optional `extra_cases()` hook that adds tests not present in the canonical data.
A module may also define `describe(case)` to control test names.

If some canonical cases do not suit the exercise, mark them with `include = false` in `.meta/tests.toml`; see the [tests.toml docs][tests-toml].
Then generate the test file:

```shell
generators/generate <exercise-slug>
```

This reads the canonical data from the copy of the problem specifications that `bin/configlet info` fetched, writes `exercises/practice/<exercise-slug>/<exercise_slug>_test.c` and formats it with `clang-format`.
The first test is enabled and every later one is marked `TEST_IGNORE();`, which the students remove one at a time.

### 4. Write the example solution and the stub

- `.meta/example.S` is the solution that proves the exercise can be solved.
  It must pass every test.
- `<exercise_slug>.S` is the stub the student starts from.
  It declares the same global labels as the example, with a body of just `ret`, so that the tests compile and fail.

Look at an existing exercise such as `exercises/practice/leap` for the conventions: `.text` and `.globl` at the top, the C prototype repeated in a `/* */` comment above each function, and local labels starting with a dot.

### 5. Verify

Check that the example solution passes the tests:

```shell
bin/verify-exercises <exercise-slug>
```

This needs `zig`, `make` and `qemu-riscv32` installed, as described in [docs/INSTALLATION.md][installation].
If you would rather not install them, the same check can run inside the track's test runner image, which needs only Docker:

```shell
bin/verify-exercises-in-docker <exercise-slug>
```

Omit the slug to verify every exercise.
Finally, check that the exercise's files and configuration are valid:

```shell
bin/configlet lint
bin/configlet fmt
```

### 6. Open the pull request

Open one pull request per exercise and link to the forum topic in its description.
The [Test workflow][ci-test] runs `bin/verify-exercises` on every pull request, the Configlet workflow runs `configlet lint`, and the Pre-commit workflow runs the same hooks as `pre-commit run --all-files`.
If the exercise's instructions need to differ from the problem specifications, add a `.docs/instructions.append.md` file rather than editing `instructions.md`; see the [instructions.append.md docs][instructions-append].

## Reporting a bug

- Search the [forum][forum] to check whether it has already been reported.
- If not, [open a topic][forum-new-topic] with a clear title, the exercise concerned, what you expected and what happened, and a code sample when possible.

## Fixing a bug or changing the track

- Make sure the bug or change has been [discussed on the forum][forum] and that there is agreement on whether and how to address it.
- Make the change and open a pull request that describes the problem and the solution, with a link to the forum topic.
- Before submitting, read the [Contributors Pull Request Guide][pr-guide] and the [Pull Request Guide][pr-community].

[forum]: https://forum.exercism.org/c/programming/risc-v
[forum-new-topic]: https://forum.exercism.org/new-topic?category=risc-v
[gh-issues]: https://github.com/exercism/risc-v/issues
[gh-pulls]: https://github.com/exercism/risc-v/pulls
[problem-specifications]: https://github.com/exercism/problem-specifications/tree/main/exercises
[configlet]: https://exercism.org/docs/building/configlet
[add-practice]: https://exercism.org/docs/building/tracks/practice-exercises/add
[unity]: https://www.throwtheswitch.org/unity
[tests-toml]: https://exercism.org/docs/building/tracks/practice-exercises#h-file-meta-tests-toml
[instructions-append]: https://exercism.org/docs/building/tracks/practice-exercises#h-file-docs-instructions-append-md
[installation]: docs/INSTALLATION.md
[contributor-tools]: docs/CONTRIBUTOR_TOOLS.md
[pre-commit]: https://pre-commit.com/
[ci-test]: https://github.com/exercism/risc-v/actions/workflows/test.yml
[pr-guide]: https://exercism.org/docs/building/github/contributors-pull-request-guide
[pr-community]: https://exercism.org/docs/community/good-member/pull-requests
