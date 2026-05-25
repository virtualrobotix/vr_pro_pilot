# Coding Standards

- C++17.
- No dynamic allocation in safety-critical path.
- Explicit bounds checks for index access.
- Every safety-critical function should include `@req` tag in comment.
- Build must remain deterministic for identical input tree.
- Follow MISRA-oriented subset; static analysis in CI.
