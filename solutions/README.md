# Building with Nix

## Prerequisites

Install Nix package manager:
```bash
# Linux/macOS
curl -L https://nixos.org/nix/install | sh

# Enable flakes (optional, for modern Nix)
mkdir -p ~/.config/nix
echo "experimental-features = nix-command flakes" >> ~/.config/nix/nix.conf
```

## Building Tasks

### Build all flake tasks:
```bash
nix build
```

This builds all tasks in the repository. Results appear in `./result/` symlinks.

### Build specific task:
```bash
nix build .#task_6_01
```

This builds folder task_6_01 in the repository. Results appear in `./result/` symlink.

## Warning
task_6_02 requires specific features (modules), so to build it just do:
```bash
cd task_6_02 && nix build
```
