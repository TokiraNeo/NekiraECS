# Contributing to NekiraECS

## Development Workflow

### Prerequisites
- C++20 compatible compiler (GCC 13+, Clang 15+, MSVC 2022)
- CMake 3.20 or later
- Git

### Setting up the Development Environment

1. Clone the repository:
```bash
git clone https://github.com/TokiraNeo/NekiraECS.git
cd NekiraECS
```

2. Create a build directory:
```bash
mkdir build
cd build
```

3. Configure and build:
```bash
cmake ..
cmake --build .
```

### Code Style

This project uses clang-format for consistent code formatting. Before submitting any changes:

1. Install clang-format:
```bash
# Ubuntu/Debian
sudo apt-get install clang-format

# macOS
brew install clang-format

# Windows (via vcpkg)
vcpkg install clang-format
```

2. Format your code:
```bash
find include source -name "*.hpp" -o -name "*.cpp" | xargs clang-format -i
```

### Testing

Currently, the project is in early development and test infrastructure is being established. Please ensure your code:
- Compiles without warnings
- Follows the existing code patterns
- Includes appropriate documentation

### Pull Request Process

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/your-feature-name`
3. Make your changes
4. Ensure code is properly formatted
5. Commit your changes: `git commit -m "Add your feature"`
6. Push to your fork: `git push origin feature/your-feature-name`
7. Open a Pull Request

### CI/CD Pipeline

All pull requests will automatically run through our CI/CD pipeline which includes:
- Multi-platform builds (Linux, Windows, macOS)
- Code formatting checks
- Static analysis
- Security scanning

Make sure all checks pass before your PR can be merged.

### Issues and Feature Requests

- Use GitHub Issues to report bugs or request features
- Provide detailed descriptions and reproduction steps for bugs
- For feature requests, explain the use case and expected behavior

### Code of Conduct

- Be respectful and constructive in all interactions
- Follow the existing code style and patterns
- Write clear commit messages
- Test your changes thoroughly