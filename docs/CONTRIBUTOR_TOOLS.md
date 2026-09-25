# Tools for contributors

Students need only the tools in [INSTALLATION.md](INSTALLATION.md).
Contributors need a few more, because the track's scripts use them:

- `git`, to clone the repository and open pull requests.
- `jq`, used by `bin/verify-exercises` and `bin/add-practice-exercise`.
- `curl`, used by `bin/fetch-configlet`.
- Python 3.11 or later, for the test generator.
- `clang-format`, which the test generator runs on the files it writes.
- `pre-commit`, which runs the repository's checks before each commit.

Install them with the command for your distribution, then follow the steps under "Once installed".

## Debian / Ubuntu

```shell
sudo apt install git jq curl clang-format pre-commit
```

## Fedora

```shell
sudo dnf install git jq curl pre-commit clang-tools-extra diffutils
```

## Arch Linux

```shell
sudo pacman -S git jq curl pre-commit clang diffutils
```

## openSUSE Tumbleweed

```shell
sudo zypper install git jq curl python3-pre-commit clang-tools diffutils
```

## Once installed

From the repository root:

```shell
bin/fetch-configlet
bin/configlet info
pre-commit install
pre-commit run --all-files
```

The first command downloads configlet into `bin/`.
The second fetches a copy of the problem specifications into configlet's cache; the test generator reads from that cache, so this needs to run once, online, before the generator will work.
The third makes git run the repository's checks before every commit, and the last runs them once over the whole repository, downloading the hook tools on first use.

To confirm everything works, verify an existing exercise and regenerate its tests:

```shell
bin/verify-exercises leap
generators/generate leap
git status
```

The first prints `leap: PASS`, and the regenerated test file is identical to the committed one, so `git status` shows no change.
