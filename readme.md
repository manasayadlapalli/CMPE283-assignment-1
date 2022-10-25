
# CMPE 283 Assignment-1:
## Team Members:
1. Shubadha Paithankar(SJSU ID: 016013283), 
2. Sai Manasa Yadlapalli (SJSU ID: 015999659)

## 3 Development Environment:
  1. Lenovo Ideapad Slimpro 14 laptop with Intel 11th Gen Intel(R) Core(TM) i5-11300H processor that supports VMX, VT-x,EPT and VT-d.
  2. Bare metal OS is Windows 11 with credential/device guard & virtualization based security disabled as per: https://kb.vmware.com/s/article/2146361
  3. Hypervisor is VMWare Workstation player 16.2
  4. Guest OS is Ubuntu 22.04

## Kernel-module development steps:
  1. Ubuntu 22.04 kernel version: 5.15.0-52-generic
  2. Installed kernel headers with: sudo apt-get install build-essential linux-headers-`uname -r`
  
MSR- A model-specific register (MSR) is any of various control registers in the x86 instruction set used for debugging, program execution tracing, computer performance monitoring, and toggling certain CPU features.

## Assignment Output Steps:

<img width="628" alt="Screen Shot 2022-10-25 at 3 56 08 PM" src="https://user-images.githubusercontent.com/99461999/197897398-8098d199-1986-46dd-8321-dd00ac5a7c6e.png">

<img width="627" alt="Screen Shot 2022-10-25 at 3 57 26 PM" src="https://user-images.githubusercontent.com/99461999/197897505-e05de32c-3515-403a-8b24-00fa2ae91893.png">

### Refrances: 
1. https://www.youtube.com/watch?v=4tgluSJDA_E
2. http://retis.sssup.it/luca/KernelProgramming/Slides/modules_intro.pdf

