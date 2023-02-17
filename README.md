# memconsume
Kernel Module to consume (upon `insmod`) and release (upon `rmmod`) memory

### Building
`make`

### Running
`insmod memconsume.ko`
or
`insmod memconsume.ko num_ptrs=<n> alloc_size=<m>`

### Cleanup
`rmmod memconsume.ko`
