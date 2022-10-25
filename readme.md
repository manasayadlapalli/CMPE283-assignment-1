Team Members:
Shubadha Paithankar   (SJSU ID: 016013283), Sai Manasa Yadlapalli (SJSU ID: 015999659)

Development Environment:
  1. Lenovo Ideapad Slimpro 14 laptop with Intel 11th Gen Intel(R) Core(TM) i5-11300H processor that supports VMX, VT-x,EPT and VT-d.
  2. Bare metal OS is Windows 11 with credential/device guard & virtualization based security disabled as per: https://kb.vmware.com/s/article/2146361
  3. Hypervisor is VMWare Workstation player 16.2
  4. Guest OS is Ubuntu 22.04

Kernel-module development steps:
  1. Ubuntu 22.04 kernel version: 5.15.0-52-generic
  2. Installed kernel headers with: sudo apt-get install build-essential linux-headers-`uname -r`

