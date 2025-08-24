# CI/CD Workflows Documentation

## Overview

This document describes the CI/CD workflows implemented for the NekiraECS project.

## Workflows

### 1. CI Workflow (`ci.yml`)

**Triggers:**
- Push to `main` or `develop` branches
- Pull requests to `main` or `develop` branches

**Features:**
- Multi-platform builds: Linux (Ubuntu), Windows, macOS
- Multi-compiler support: GCC 13, Clang 15, MSVC 2022
- Automated CMake configuration and build
- Test execution (when tests are available)
- Installation verification
- Build artifact upload

**Matrix Strategy:**
```yaml
- Ubuntu + GCC 13
- Ubuntu + Clang 15
- Windows + MSVC
- macOS + Clang
```

### 2. Code Quality Workflow (`code-quality.yml`)

**Triggers:**
- Push to `main` or `develop` branches
- Pull requests to `main` or `develop` branches

**Features:**
- **Format Check**: Uses clang-format to ensure consistent code style
- **Static Analysis**: Uses clang-tidy for code quality analysis
- **Security Scan**: Integrates GitHub CodeQL for security vulnerability detection

### 3. Release Workflow (`release.yml`)

**Triggers:**
- Push of version tags (e.g., `v1.0.0`)

**Features:**
- Multi-platform release builds
- Automatic changelog generation
- GitHub Release creation
- Release artifact packaging (.tar.gz for Linux/macOS, .zip for Windows)

### 4. Documentation Workflow (`documentation.yml`)

**Triggers:**
- Push to `main` branch
- Pull requests to `main` branch

**Features:**
- Documentation completeness check
- License verification
- Doxygen documentation generation (when Doxyfile exists)
- Documentation artifact upload

### 5. Dependencies Workflow (`dependencies.yml`)

**Triggers:**
- Weekly schedule (Sundays)
- Manual trigger (`workflow_dispatch`)

**Features:**
- CMake version requirement verification
- C++20 compiler support validation
- Project structure analysis
- Security pattern scanning

## Status Badges

The following badges are available in the README files:

- ![CI](https://img.shields.io/github/actions/workflow/status/TokiraNeo/NekiraECS/ci.yml?branch=main&style=flat-square&label=CI&color=%2300d4aa)
- ![Code Quality](https://img.shields.io/github/actions/workflow/status/TokiraNeo/NekiraECS/code-quality.yml?branch=main&style=flat-square&label=Code%20Quality&color=%23ff6b6b)
- ![Documentation](https://img.shields.io/github/actions/workflow/status/TokiraNeo/NekiraECS/documentation.yml?branch=main&style=flat-square&label=Docs&color=%234ecdc4)
- ![Release](https://img.shields.io/github/v/release/TokiraNeo/NekiraECS?style=flat-square&color=%23f7b801)

## Configuration Files

### Code Quality
- `.clang-format`: Code formatting rules
- `.clang-tidy`: Static analysis rules

### Build System
- `CMakeLists.txt`: Main build configuration
- `cmake/`: CMake configuration templates

### Documentation
- `CONTRIBUTING.md`: Development workflow and contribution guidelines
- `README.MD`: Main project documentation (Chinese)
- `Documents/README/README.EN.MD`: English documentation
- `Documents/README/README.CN.MD`: Chinese documentation

## Development Workflow

1. **Fork and Clone**: Fork the repository and clone your fork
2. **Create Branch**: Create a feature branch for your changes
3. **Develop**: Make your changes following the code style guidelines
4. **Test Locally**: Build and test your changes locally
5. **Format Code**: Run clang-format on your changes
6. **Submit PR**: Create a pull request to the main repository
7. **CI Validation**: All CI workflows must pass before merge
8. **Review**: Code review by maintainers
9. **Merge**: Changes are merged to the main branch

## Release Process

1. **Tag Creation**: Create and push a version tag (e.g., `git tag v1.0.0 && git push origin v1.0.0`)
2. **Automatic Build**: Release workflow triggers automatically
3. **Artifact Generation**: Multi-platform artifacts are built
4. **Release Creation**: GitHub release is created with changelog and artifacts

## Maintenance

- **Weekly Dependency Check**: Automated weekly scan for dependency issues
- **Security Monitoring**: Continuous security scanning with CodeQL
- **Documentation Updates**: Automatic documentation generation on main branch updates