# xv6-Shared-Memory

An xv6-riscv fork that adds shared-memory primitives and a simple shared-memory
request queue used by a crypto service. The kernel exposes system calls to map
pages from one process into another, and a small queue allows user-space crypto
clients to hand off work to a dedicated server process.

## Features

- **Shared memory syscalls**: `map_shared_pages` and `unmap_shared_pages` map
  pages from a source process into a destination process and remove them when
  done.
- **Shared-memory request queue**: a fixed-size queue in the kernel for passing
  `(src_pid, dst_pid, src_va, size)` requests between processes.
- **Crypto service scaffolding**: a crypto client (`crypto_cli`) and a server
  stub (`crypto_srv`) wired to the shared-memory queue for experimentation.

## Requirements

- RISC-V cross toolchain (`riscv64-unknown-elf-` or `riscv64-linux-gnu-`)
- QEMU (riscv64 system emulator)

## Build and run

```bash
make qemu
```

Clean build artifacts:

```bash
make clean
```

## Shared memory interface

The kernel exports two syscalls to user space:

- `map_shared_pages(src_pid, dst_pid, src_va, size)`
  - Maps `size` bytes starting at `src_va` from `src_pid` into `dst_pid`.
  - Returns the destination virtual address in the target process or `-1` on
    error.
- `unmap_shared_pages(dst_pid, dst_va, size)`
  - Unmaps a previously shared region from the destination process.

Example usage can be found in `user/shmem_test1.c` and `user/shmem_test2.c`.

## Crypto service flow

1. `crypto_cli` prepares a `crypto_op` payload and submits it with `crypto_op()`.
2. The kernel records a shared-memory request and wakes the crypto server.
3. `crypto_srv` (started early in boot) can take the request, map the shared
   pages, and perform the operation.

`crypto_srv` is currently a stub, so it is intended as a starting point for
implementing the server logic.

## User programs of interest

Within the xv6 shell, try:

```text
shmem_test1
shmem_test2
crypto_cli
```

These illustrate the shared-memory calls and the crypto client/server workflow.
